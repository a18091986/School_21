-- Active: 1704653475145@@192.168.2.160@5432@edu
-- 1) Написать функцию,
-- возвращающую таблицу TransferredPoints в более человекочитаемом виде Ник пира 1,
-- ник пира 2,
-- количество переданных пир поинтов.Количество отрицательное,
-- если пир 2 получил от пира 1 больше поинтов.

CREATE OR REPLACE FUNCTION points_transfer() RETURNS TABLE("Peer1" VARCHAR, "Peer2" VARCHAR, "PointsAmount" INT) AS $$
    BEGIN 
        RETURN QUERY (SELECT t3."Peer1", t3."Peer2", sum(t3."PointsAmount")::INT "PointsAmount" FROM
                ((SELECT t1."CheckingPeer" "Peer1", t1."CheckedPeer" "Peer2", t1."PointsAmount" FROM TransferredPoints t1 WHERE "CheckingPeer" > "CheckedPeer")
                UNION
                (SELECT t2."CheckedPeer", t2."CheckingPeer", -t2."PointsAmount" FROM TransferredPoints t2 WHERE "CheckedPeer" > "CheckingPeer" )) t3
                GROUP BY (t3."Peer1", t3."Peer2")
                ORDER BY 3 DESC);
	END;
$$ LANGUAGE plpgsql; 

SELECT * FROM points_transfer();

-- 2) Написать функцию,
-- которая возвращает таблицу вида: ник пользователя,
-- название проверенного задания,
-- кол - во полученного XP В таблицу включать только задания,
-- успешно прошедшие проверку (определять по таблице Checks).
-- Одна задача может быть успешно выполнена несколько раз.В таком случае в таблицу включать все успешные проверки.


CREATE OR REPLACE FUNCTION success_checks() RETURNS TABLE(Peer VARCHAR, Task VARCHAR, XP INT) AS $$ 
    BEGIN RETURN QUERY 
    (SELECT Checks."Peer", Checks."Task", XP."XPAmount" FROM Checks 
    LEFT JOIN P2P ON P2P."Check" = Checks."ID" 
    INNER JOIN XP ON XP."Check" = Checks."ID"
    LEFT JOIN Verter ON Verter."Check" = Checks."ID"
WHERE
    P2P."State" = 'Success' AND (Verter."State" = 'Success' OR Verter."State" IS NULL));
	END;
$$ language plpgsql; 

SELECT * FROM success_checks();

-- 3) Написать функцию,
-- определяющую пиров,
-- которые не выходили из кампуса в течение всего дня Параметры функции: день,
-- например 12.05.2022. Функция возвращает только список пиров.

CREATE OR REPLACE FUNCTION peers_not_walking(current_day Date DEFAULT CURRENT_DATE) RETURNS TABLE("Peer" VARCHAR) AS $$
    BEGIN 
        RETURN QUERY (SELECT t."Peer" FROM TimeTracking t WHERE "Date" = current_day GROUP by t."Peer" HAVING (count("State") = 2));
    END;
$$ LANGUAGE plpgsql;

SELECT * FROM peers_not_walking('2020-01-01');

-- 4) Посчитать изменение в количестве пир поинтов каждого пира по таблице TransferredPoints 
-- Результат вывести отсортированным по изменению числа поинтов.Формат вывода: ник пира,
-- изменение в количество пир поинтов

CREATE OR REPLACE FUNCTION points_change_v1() RETURNS TABLE("Peer" VARCHAR, "PointsChange" INTEGER) AS $$ 
    BEGIN 
        RETURN QUERY(SELECT t3."CheckingPeer" "Peer", SUM(t3.points_sum)::INT FROM
                    (SELECT t1."CheckingPeer", SUM(t1."PointsAmount") points_sum FROM TransferredPoints t1 GROUP BY "CheckingPeer"
                    UNION
                    SELECT t2."CheckedPeer", -SUM(t2."PointsAmount") FROM TransferredPoints t2 GROUP BY "CheckedPeer") t3
                    GROUP BY "CheckingPeer" ORDER BY 2 DESC, 1 ASC);
    END;
$$ LANGUAGE plpgsql;

SELECT * FROM points_change_v1();

-- 5) Посчитать изменение в количестве пир поинтов каждого пира по таблице,
-- возвращаемой первой функцией из Part 3 Результат вывести отсортированным по изменению числа поинтов.Формат вывода: ник пира,
-- изменение в количество пир поинтов



CREATE OR REPLACE FUNCTION points_change_v2() RETURNS TABLE("Peer" VARCHAR, "PointsChange" INTEGER) AS $$ 
    BEGIN 
        RETURN QUERY(SELECT t3."Peer1" "Peer", SUM(t3."PointsChange")::INT FROM
                    (SELECT t1."Peer1", Sum(t1."PointsAmount") "PointsChange" FROM points_transfer() t1 GROUP BY "Peer1"
                    UNION
                    SELECT t2."Peer2", -Sum(t2."PointsAmount") "PointsChange" FROM points_transfer() t2 GROUP BY "Peer2") t3
                    GROUP BY "Peer1" ORDER BY 2 DESC, 1 ASC);
    END;
$$ LANGUAGE plpgsql;

SELECT * FROM points_change_v2();

-- 6) Определить самое часто проверяемое задание за каждый день При одинаковом количестве проверок каких - то заданий в определенный день,
-- вывести их все.Формат вывода: день,
-- название задания

CREATE OR REPLACE FUNCTION most_often_task() RETURNS TABLE("Date" date, "Task" VARCHAR)  AS	$$ 
    BEGIN 
        RETURN QUERY 
            WITH t1 AS (SELECT Checks."Date" , Checks."Task" , COUNT(*) ch_cnt FROM Checks 
                        GROUP BY Checks."Task", Checks."Date" ORDER BY Checks."Date", ch_cnt), 
                 t2 AS (SELECT t1."Date" , MAX(ch_cnt) AS top_ch FROM t1 GROUP BY t1."Date")
            SELECT t2."Date", t1."Task" FROM t2 JOIN t1 ON t1."Date" = t2."Date" AND t1.ch_cnt = t2.top_ch;
	END;
$$ LANGUAGE plpgsql; 

SELECT * FROM most_often_task();



-- 7) Найти всех пиров,
-- выполнивших весь заданный блок задач и дату завершения последнего задания Параметры процедуры: название блока,
-- например "CPP".Результат вывести отсортированным по дате завершения.Формат вывода: ник пира,
-- дата завершения блока (т.е.последнего выполненного задания из этого блока)

CREATE OR REPLACE FUNCTION end_block(task VARCHAR) RETURNS TABLE("Peer" VARCHAR, "Date" date) AS $$ 
    DECLARE block_end VARCHAR;
	BEGIN SELECT "Title" INTO block_end FROM tasks WHERE "Title" SIMILAR TO CONCAT(task, '[0-9]_%' ) ORDER BY "Title" DESC LIMIT 1;
	RETURN QUERY 
        SELECT Peers."Nickname", Checks."Date"
	    FROM Peers
	        JOIN Checks ON Peers."Nickname" = Checks."Peer"
	        JOIN P2P on Checks."ID" = P2P."Check"
	        LEFT JOIN Verter ON Checks."ID" = Verter."Check"
	    WHERE
    	    P2P."State" = 'Success' AND (Verter."State" = 'Success' OR Verter."State" IS NULL) AND Checks."Task" = block_end;
	END;
$$ LANGUAGE plpgsql; 

SELECT * FROM end_block('C');

-- 8) Определить,
-- к какому пиру стоит идти на проверку каждому обучающемуся Определять нужно исходя из рекомендаций друзей пира,
-- т.е.нужно найти пира, проверяться у которого рекомендует наибольшее число друзей.Формат вывода: ник пира,
-- ник найденного проверяющего

CREATE OR REPLACE FUNCTION get_rec() RETURNS TABLE (peer VARCHAR,  recommendedpeer VARCHAR) AS $$
    BEGIN RETURN QUERY 
        WITH af AS (SELECT "Nickname",
                           (CASE WHEN "Nickname" = f."Peer1" THEN f."Peer2" ELSE f."Peer1" END) AS friends
                    FROM Peers p JOIN Friends f ON p."Nickname" = f."Peer1" OR p."Nickname" = f."Peer2"), 
             ar AS (SELECT "Nickname", COUNT(r."RecommendedPeer") AS count_rec, r."RecommendedPeer" 
                    FROM af a JOIN Recommendations r ON a.friends = r."Peer"
                    WHERE a."Nickname" != r."RecommendedPeer" GROUP BY "Nickname", r."RecommendedPeer"),
             gm AS (SELECT "Nickname", MAX(count_rec) AS max_count FROM ar GROUP BY "Nickname")
            SELECT  a."Nickname" AS Peer, a."RecommendedPeer" FROM ar a 
            JOIN gm g ON a."Nickname" = g."Nickname" AND a.count_rec = g.max_count 
            ORDER BY 1, 2;
END;
$$LANGUAGE plpgsql;

SELECT * FROM get_rec();

SELECT * FROM Friends;

SELECT * FROM Recommendations;

-- 9) Определить процент пиров,
-- которые: Приступили только к блоку 1 Приступили только к блоку 2 Приступили к обоим Не приступили ни к одному Пир считается приступившим к блоку,
-- если он проходил хоть одну проверку любого задания из этого блока (по таблице Checks)

-- Параметры процедуры: название блока 1,
-- например SQL,
-- название блока 2,
-- например A.Формат вывода: процент приступивших только к первому блоку,
-- процент приступивших только ко второму блоку,
-- процент приступивших к обоим,
-- процент не приступивших ни к одному

CREATE OR REPLACE FUNCTION block_completion_percentage ("block1" VARCHAR, "block2" VARCHAR) 
RETURNS TABLE("StartedBlock1" NUMERIC, "StartedBlock2" NUMERIC, "StartedBothBlocks" NUMERIC, "DidntStartAnyBlock" NUMERIC) AS $$ 
    DECLARE "block1_prefix" VARCHAR := "block1" || '%';
	        "block2_prefix" VARCHAR := "block2" || '%';
	        "all_peers" BIGINT;
	BEGIN all_peers := ( SELECT count ("Nickname") FROM Peers );
	RETURN QUERY
	WITH block1_users AS (
	        SELECT DISTINCT "Peer"
	        FROM Checks
	        WHERE
	            "Task" LIKE block1_prefix
	    ),
	    block2_users AS (
	        SELECT DISTINCT "Peer"
	        FROM Checks
	        WHERE
	            "Task" LIKE block2_prefix
	    ),
	    both_blocks_users AS (
	        SELECT "Peer"
	        FROM block1_users
	        INTERSECT
	        SELECT "Peer"
	        FROM
	            block2_users
	    ),
	    neither_block_users AS (
	        SELECT "Nickname" AS "Peer"
	        FROM Peers
	        EXCEPT (
	            SELECT "Peer"
	            FROM block1_users
	            UNION DISTINCT
	            SELECT "Peer"
	            FROM block2_users
	        )
	    )
	SELECT (
	        SELECT count ("Peer")
	        FROM
	            block1_users
	    ):: numeric / all_peers * 100, (
	        SELECT count ("Peer")
	        FROM
	            block2_users
	    ):: numeric / all_peers * 100, (
	        SELECT count ("Peer")
	        FROM
	            both_blocks_users
	    ):: numeric / all_peers * 100, (
	        SELECT count ("Peer")
	        FROM
	            neither_block_users
	    ):: numeric / all_peers * 100;
	END $$ LANGUAGE
plpgsql; 
--TESTS--
SELECT * FROM block_completion_percentage('A', 'B');

-- 10) Определить процент пиров,
-- которые когда - либо успешно проходили проверку в свой день рождения Также определите процент пиров,
-- которые хоть раз проваливали проверку в свой день рождения.Формат вывода: процент пиров,
-- успешно прошедших проверку в день рождения,
-- процент пиров,
-- проваливших проверку в день рождения

CREATE OR REPLACE FUNCTION s_f_pct() RETURNS TABLE(SuccessfulChecks INT, UnsuccessfulChecks INT) AS $$ 
    BEGIN RETURN QUERY 
        WITH counts AS 
            (SELECT 
            COUNT(Checks."Peer") FILTER (WHERE P2P."State" = 'Success' ) AS s, 
            COUNT(Checks."Peer") FILTER (WHERE P2P."State" = 'Failure' ) AS f 
            FROM Checks LEFT JOIN Peers ON Checks."Peer" = Peers."Nickname" JOIN P2P ON Checks."ID" = P2P."Check" 
            WHERE (EXTRACT (MONTH FROM Checks."Date" ) = EXTRACT  (MONTH FROM Peers."Birthday")) AND (EXTRACT (DAY FROM Checks."Date") = EXTRACT( DAY FROM Peers."Birthday" ))) 
        
        SELECT ( s::NUMERIC / NULLIF ( s + f , 0 )::NUMERIC * 100 )::INT "SuccessfulChecks" , 
               ( f::NUMERIC / NULLIF ( s + f , 0 )::NUMERIC * 100 )::INT "UnsuccessfulChecks" FROM counts;
    END 
$$ LANGUAGE plpgsql; 

SELECT * FROM s_f_pct();

-- 11) Определить всех пиров,
-- которые сдали заданные задания 1 и 2,
-- но не сдали задание 3 Параметры процедуры: названия заданий 1,
-- 2 и 3. Формат вывода: список пиров

CREATE OR REPLACE FUNCTION fnc_part3_task11(task1 VARCHAR
, task2 VARCHAR, task3 VARCHAR) RETURNS SETOF VARCHAR 
AS 
	$$ BEGIN RETURN QUERY WITH success AS ( SELECT "Peer" , count ( "Peer" ) FROM ( SELECT "Peer" , "Task" FROM ( ( SELECT * FROM checks JOIN XP ON checks . "ID" = XP . "Check" WHERE "Task" = task1 ) UNION ( SELECT * FROM checks JOIN XP ON checks . "ID" = XP . "Check" WHERE "Task" = task2 ) ) t1 GROUP BY "Peer" , "Task" ) t2 GROUP BY "Peer" HAVING count ( "Peer" ) = 2 ) ( SELECT "Peer" FROM success ) EXCEPT ( SELECT success . "Peer" FROM success JOIN checks ON checks . "Peer" = success . "Peer" JOIN XP ON checks . "ID" = XP . "Check" WHERE "Task" = task3 ) ;
	END;
	$$ LANGUAGE
plpgsql; 

SELECT * FROM fnc_part3_task11('B1_Task1', 'B1_Task2', 'A1_Task2');

-- 12) Используя рекурсивное обобщенное табличное выражение,
-- для каждой задачи вывести кол - во предшествующих ей задач То есть сколько задач нужно выполнить,
-- исходя из условий входа,
-- чтобы получить доступ к текущей.Формат вывода: название задачи,
-- количество предшествующих

CREATE OR REPLACE FUNCTION fnc_part3_task12() RETURNS 
TABLE("Task" VARCHAR, "PrevCount" INT) AS 
	$$ BEGIN RETURN QUERY WITH RECURSIVE parent AS ( SELECT ( SELECT "Title" FROM tasks WHERE "ParentTask" IS NULL ) AS Task , 0 AS PrevCount UNION ALL SELECT tasks . "Title" , PrevCount + 1 FROM parent JOIN tasks ON tasks . "ParentTask" = parent . Task ) SELECT * FROM parent;
	END;
	$$ LANGUAGE
plpgsql; 

SELECT * FROM fnc_part3_task12();

-- 13) Найти "удачные" для проверок дни.День считается "удачным",
-- если в нем есть хотя бы N идущих подряд успешных проверки Параметры процедуры: количество идущих подряд успешных проверок N.Временем проверки считать время начала P2P этапа.Под идущими подряд успешными проверками подразумеваются успешные проверки,
-- между которыми нет неуспешных.При этом кол - во опыта за каждую из этих проверок должно быть не меньше 80 % от максимального.Формат вывода: список дней

create or replace procedure prcdr_checks_lucky_days
(ref refcursor, N numeric) as 
	$$ begin open ref for with cte_previous_state as ( select * , lag ( resume , 1 , '-' ) over ( partition by checks_date order by checks_id ) as l from v_all_passing_checks1 ) , cte_successful_count as ( select checks_date , count ( * ) over ( partition by checks_date ) from cte_previous_state join Tasks on cte_previous_state . task = Tasks . Title join XP on cte_previous_state . checks_id = XP . "Check" where resume = 'S' and ( l = 'S' or l = '-' ) and XP . XPAmount > = Tasks . MaxXP * 0 . 8 ) select checks_date from ( select checks_date , count ( * ) from cte_successful_count group by checks_date ) as finale_count where count > ( N - 1 ) ;
	end;
	$$ language
plpgsql; 

select * from prcdr_checks_lucky_days(2)

CREATE OR REPLACE FUNCTION fnc_part3_task13(n int) 
RETURNS SETOF DATE AS 
	$$ DECLARE l RECORD;
	l2 RECORD;
	i INT := 0;
	 BEGIN FOR l IN SELECT "Date" FROM checks GROUP BY "Date" ORDER BY "Date" LOOP FOR l2 IN SELECT * FROM ( SELECT "Peer" , p2p . "State" , xp . "XPAmount" , tasks . "MaxXP" , p2p . "Time" , "Date" FROM checks JOIN p2p ON checks . "ID" = p2p . "Check" LEFT JOIN verter ON checks . "ID" = verter . "Check" JOIN tasks ON checks . "Task" = tasks . "Title" JOIN xp ON checks . "ID" = xp . "Check" WHERE p2p . "State" ! = 'Start' AND xp . "XPAmount" > = tasks . "MaxXP" * 0 . 8 AND ( verter . "State" = 'Success' OR verter . "State" IS NULL ) ORDER BY 6 , 5 ) AS tmp WHERE l . "Date" = tmp . "Date" LOOP IF l2 . "State" = 'Success' THEN i := i + 1;
	IF i = n THEN RETURN NEXT l2."Date";
	EXIT;
	END IF;
	ELSE i := 0;
	END IF;
	END LOOP;
	i := 0;
	END LOOP;
	END;
	$$ LANGUAGE
plpgsql; 

select * from fnc_part3_task13(1);

DROP PROCEDURE
    IF EXISTS successful_day(rc5 refcursor, streak integer);
CREATE OR REPLACE PROCEDURE successful_day(rc5 refcursor, streak integer) AS $$ 
    BEGIN 
        OPEN rc5 FOR WITH temp AS 
            (SELECT * FROM Checks 
                JOIN P2P ON Checks."ID" = P2P."Check" 
                LEFT JOIN Verter ON Checks."ID" = Verter."Check" 
                JOIN Tasks ON Tasks."Title" = Checks."Task" 
                JOIN XP ON Checks."ID" = XP."Check" 
            WHERE P2P."State" = 'Success' AND (Verter."State" = 'Success' OR Verter."State" IS NULL)) 
            SELECT "Date" FROM temp WHERE temp."MaxXP" * 0.8 <= temp."XPAmount" GROUP BY temp."Date" HAVING COUNT ("Date") >= streak;
	END;
$$ LANGUAGE plpgsql; 

BEGIN;
CALL successful_day('r', 1);
FETCH ALL IN "r";
END;

-- 14) Определить пира с наибольшим количеством XP Формат вывода: ник пира,
-- количество XP

CREATE OR REPLACE FUNCTION maxXP() RETURNS TABLE(Peer VARCHAR, XP INTEGER) AS $$ 
BEGIN RETURN QUERY
    (SELECT DISTINCT "Peer", SUM("XPAmount"):: INT "XP" FROM Checks JOIN XP ON Checks."ID" = XP."Check" GROUP BY "Peer" ORDER BY "XP" DESC LIMIT 1);
END;
$$ LANGUAGE plpgsql; 

SELECT * FROM maxXP();



-- 15) Определить пиров,
-- приходивших раньше заданного времени не менее N раз за всё время Параметры процедуры: время,
-- количество раз N.Формат вывода: список пиров

CREATE OR REPLACE FUNCTION coming_time_before(Came TIME, N INTEGER) RETURNS TABLE(Peer VARCHAR) AS $$ 
BEGIN RETURN QUERY
    (SELECT "Peer" FROM TimeTracking WHERE "State" = '1' AND "Time" < Came GROUP BY "Peer" HAVING COUNT ("Time") >= N ORDER BY 1);
END;
$$ LANGUAGE plpgsql; 

SELECT * FROM coming_time_before('12:00:00', 2);

-- 16) Определить пиров,
-- выходивших за последние N дней из кампуса больше M раз Параметры процедуры: количество дней N,
-- количество раз M.Формат вывода: список пиров

CREATE OR REPLACE FUNCTION go_away_count(N INTEGER, M INTEGER) RETURNS TABLE(Peer VARCHAR) AS $$ 
BEGIN RETURN QUERY
   SELECT DISTINCT "Peer" FROM 
        (SELECT "Peer", COUNT("Peer") OVER (PARTITION BY "Peer") FROM TimeTracking 
        WHERE ("Date" BETWEEN CURRENT_DATE - (concat(N, 'day') :: INTERVAL) AND CURRENT_DATE) AND "State" = '2') t
        WHERE count > M 
        ORDER BY "Peer";
END;
$$ LANGUAGE plpgsql; 

SELECT * FROM go_away_count(2000, 1);

-- 17) Определить для каждого месяца процент ранних входов Для каждого месяца посчитать,
-- сколько раз люди,
-- родившиеся в этот месяц,
-- приходили в кампус за всё время (будем называть это общим числом входов).
-- Для каждого месяца посчитать,cколько раз люди,родившиеся в этот месяц, приходили в кампус раньше 12: 00 за всё время (
--     будем называть это числом ранних входов).
-- Для каждого месяца посчитать процент ранних входов в кампус относительно общего числа входов.Формат вывода: месяц,
-- процент ранних входов

CREATE OR REPLACE FUNCTION early_come_pct() RETURNS TABLE("Month" TEXT, "EarlyEntries" NUMERIC) AS $$ 
    BEGIN RETURN QUERY 
    (WITH tmp AS 
            (SELECT date_trunc('month', TimeTracking."Date") AS "month" , COUNT (*) AS visits, COUNT (*) 
                FILTER (WHERE 
                    EXTRACT(hour FROM TimeTracking."Time" ) < 12) AS evisits FROM TimeTracking JOIN Peers ON TimeTracking."Peer" = Peers."Nickname" 
                    AND 
                    EXTRACT ("month" FROM Peers."Birthday") = EXTRACT("month" FROM TimeTracking."Date") WHERE TimeTracking."State" = '1' GROUP BY date_trunc('month' , TimeTracking."Date" )) 
    SELECT to_char(tmp.month , 'Month') AS "Month", 
           ROUND( 100.0 * tmp.evisits / tmp.visits, 2) AS "EarlyEntries" FROM tmp);
	END;
$$ LANGUAGE plpgsql; 

SELECT * FROM early_come_pct();