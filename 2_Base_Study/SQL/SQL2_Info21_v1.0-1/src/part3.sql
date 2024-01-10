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

select * from Friends;

select * from Recommendations;

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


-- 10) Определить процент пиров,
-- которые когда - либо успешно проходили проверку в свой день рождения Также определите процент пиров,
-- которые хоть раз проваливали проверку в свой день рождения.Формат вывода: процент пиров,
-- успешно прошедших проверку в день рождения,
-- процент пиров,
-- проваливших проверку в день рождения


-- 11) Определить всех пиров,
-- которые сдали заданные задания 1 и 2,
-- но не сдали задание 3 Параметры процедуры: названия заданий 1,
-- 2 и 3. Формат вывода: список пиров

-- 12) Используя рекурсивное обобщенное табличное выражение,
-- для каждой задачи вывести кол - во предшествующих ей задач То есть сколько задач нужно выполнить,
-- исходя из условий входа,
-- чтобы получить доступ к текущей.Формат вывода: название задачи,
-- количество предшествующих

-- 13) Найти "удачные" для проверок дни.День считается "удачным",
-- если в нем есть хотя бы N идущих подряд успешных проверки Параметры процедуры: количество идущих подряд успешных проверок N.Временем проверки считать время начала P2P этапа.Под идущими подряд успешными проверками подразумеваются успешные проверки,
-- между которыми нет неуспешных.При этом кол - во опыта за каждую из этих проверок должно быть не меньше 80 % от максимального.Формат вывода: список дней

-- 14) Определить пира с наибольшим количеством XP Формат вывода: ник пира,
-- количество XP

-- 15) Определить пиров,
-- приходивших раньше заданного времени не менее N раз за всё время Параметры процедуры: время,
-- количество раз N.Формат вывода: список пиров

-- 16) Определить пиров,
-- выходивших за последние N дней из кампуса больше M раз Параметры процедуры: количество дней N,
-- количество раз M.Формат вывода: список пиров

-- 17) Определить для каждого месяца процент ранних входов Для каждого месяца посчитать,
-- сколько раз люди,
-- родившиеся в этот месяц,
-- приходили в кампус за всё время (будем называть это общим числом входов).
-- Для каждого месяца посчитать,cколько раз люди,родившиеся в этот месяц, приходили в кампус раньше 12: 00 за всё время (
--     будем называть это числом ранних входов).
-- Для каждого месяца посчитать процент ранних входов в кампус относительно общего числа входов.Формат вывода: месяц,
-- процент ранних входов
