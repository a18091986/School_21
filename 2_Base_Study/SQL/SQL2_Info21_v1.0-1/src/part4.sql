--DROP TRIGGER IF EXISTS t_Friends ON Friends;
--
--DROP TRIGGER IF EXISTS t_Verter ON Verter;
--
--DROP TRIGGER IF EXISTS t_P2P ON P2P;
--
--DROP TRIGGER IF EXISTS t_Tasks ON Tasks;
--
--DROP TRIGGER IF EXISTS t_TransferredPoints ON TransferredPoints;
--
--DROP TRIGGER IF EXISTS t_XP ON XP;
--
--DROP FUNCTION IF EXISTS pair_friends();
--
--DROP FUNCTION IF EXISTS verter_check_is_allowed();
--
--DROP FUNCTION IF EXISTS one_p2p_check_started();
--
--DROP FUNCTION IF EXISTS check_parent_task();
--
--DROP PROCEDURE IF EXISTS p2p_add();
--
--DROP PROCEDURE IF EXISTS verter_add();
--
--DROP FUNCTION IF EXISTS XP_add();
--
--DROP TABLE IF EXISTS P2P;
--
--DROP TABLE IF EXISTS Verter;
--
--DROP TABLE IF EXISTS XP;
--
--DROP TABLE IF EXISTS Checks;
--
--DROP TABLE IF EXISTS Tasks;
--
--DROP TABLE IF EXISTS TransferredPoints;
--
--DROP TABLE IF EXISTS Friends;
--
--DROP TABLE IF EXISTS Recommendations;
--
--DROP TABLE IF EXISTS TimeTracking;
--
--DROP TABLE IF EXISTS Peers;
--
--DROP TYPE IF EXISTS CheckStatus;

-----tables creation-------
--Таблица Peers
--Ник пира
--День рождения

CREATE TABLE
    IF NOT EXISTS Peers (
        "Nickname" VARCHAR PRIMARY KEY NOT NULL,
        "Birthday" DATE NOT NULL
    );
CREATE TABLE
    IF NOT EXISTS Tasks (
        "Title" VARCHAR PRIMARY KEY NOT NULL UNIQUE,
        "ParentTask" VARCHAR DEFAULT 'NULL',
        "MaxXP" INT NOT NULL,
        CONSTRAINT fk_TasksParentTask_TasksTitle FOREIGN KEY ("ParentTask") REFERENCES Tasks("Title"),
        CONSTRAINT ch_ParentTask_not_eq_Title CHECK ("ParentTask" != "Title")
    );
   
CREATE TABLE
    IF NOT EXISTS Tasks_two (
        "Title" VARCHAR PRIMARY KEY NOT NULL UNIQUE,
        "ParentTask" VARCHAR DEFAULT 'NULL',
        "MaxXP" INT NOT NULL
    );

CREATE TYPE CheckStatus AS ENUM('Start', 'Success', 'Failure');

CREATE TABLE
    IF NOT EXISTS Checks (
        "ID" SERIAL PRIMARY KEY,
        "Peer" VARCHAR NOT NULL,
        "Task" VARCHAR NOT NULL,
        "Date" DATE NOT NULL DEFAULT CURRENT_DATE,
        CONSTRAINT fk_ChecksPeer_PeersNickname FOREIGN KEY ("Peer") REFERENCES Peers("Nickname"),
        CONSTRAINT fk_ChecksTask_TasksTitle FOREIGN KEY ("Task") REFERENCES Tasks("Title")
    );

CREATE TABLE
    IF NOT EXISTS P2P (
        "ID" SERIAL PRIMARY KEY,
        "Check" INT NOT NULL,
        "CheckingPeer" VARCHAR NOT NULL,
        "State" CheckStatus NOT NULL,
        "Time" TIME WITHOUT TIME ZONE NOT NULL DEFAULT CURRENT_TIME,
        CONSTRAINT fk_P2PCheck_ChecksID FOREIGN KEY ("Check") REFERENCES Checks("ID"),
        CONSTRAINT fk_P2PCheckingPeer_PeersNickname FOREIGN KEY ("CheckingPeer") REFERENCES Peers("Nickname") -- CONSTRAINT unique_CheckingPeer_CheckID_Status UNIQUE ("CheckingPeer", "Check", "State")
    );


CREATE TABLE
    IF NOT EXISTS Verter (
        "ID" SERIAL PRIMARY KEY,
        "Check" INT NOT NULL,
        "State" CheckStatus NOT NULL,
        "Time" TIME NOT NULL,
        CONSTRAINT fk_VerterCheck_ChecksID FOREIGN KEY ("Check") REFERENCES Checks("ID")
    );

--Таблица TransferredPoints
--ID
--Ник проверяющего пира
--Ник проверяемого пира
--Количество переданных пир поинтов за всё время
--(только от проверяемого к проверяющему)
--При каждой P2P проверке проверяемый пир передаёт один пир поинт проверяющему.
--Эта таблица содержит все пары проверяемый-проверяющий и
--кол-во переданных пир поинтов, то есть, другими словами,
--количество P2P проверок указанного проверяемого пира, данным проверяющим.

CREATE TABLE
    IF NOT EXISTS TransferredPoints (
        "ID" SERIAL PRIMARY KEY,
        "CheckingPeer" VARCHAR NOT NULL,
        "CheckedPeer" VARCHAR NOT NULL,
        "PointsAmount" INT NOT NULL DEFAULT 0,
        CONSTRAINT fk_TransferredPointsCheckingPeer_PeersNickname FOREIGN KEY ("CheckingPeer") REFERENCES Peers("Nickname"),
        CONSTRAINT fk_TransferredPointsCheckedPeer_PeersNickname FOREIGN KEY ("CheckedPeer") REFERENCES Peers("Nickname")
    );

--Таблица Friends
--ID
--Ник первого пира
--Ник второго пира
--Дружба взаимная, т.е. первый пир является другом второго,
--а второй -- другом первого.

CREATE TABLE
    IF NOT EXISTS Friends (
        "ID" SERIAL PRIMARY KEY,
        "Peer1" VARCHAR NOT NULL,
        "Peer2" VARCHAR NOT NULL,
        CONSTRAINT fk_FriendsPeer1_PeersNickname FOREIGN KEY ("Peer1") REFERENCES Peers("Nickname"),
        CONSTRAINT fk_FriendsPeer2_PeersNickname FOREIGN KEY ("Peer2") REFERENCES Peers("Nickname"),
        CONSTRAINT ch_peers_not_eq CHECK ("Peer1" != "Peer2")
    );

--Таблица Recommendations
--ID
--Ник пира
--Ник пира, к которому рекомендуют идти на проверку
--Каждому может понравиться, как проходила P2P проверка у того или иного пира.
--Пир, указанный в поле Peer, рекомендует проходить P2P проверку у пира из поля
--RecommendedPeer. Каждый пир может рекомендовать как ни одного,
--так и сразу несколько проверяющих.

CREATE TABLE
    IF NOT EXISTS Recommendations (
        "ID" SERIAL PRIMARY KEY,
        "Peer" VARCHAR NOT NULL,
        "RecommendedPeer" VARCHAR,
        CONSTRAINT fk_RecommendationsPeer_PeersNickname FOREIGN KEY ("Peer") REFERENCES Peers("Nickname"),
        CONSTRAINT fk_RecommendationsRecommendedPeer_PeersNickname FOREIGN KEY ("RecommendedPeer") REFERENCES Peers("Nickname"),
        CONSTRAINT ch_recomen_peers_not_eq CHECK ("Peer" != "RecommendedPeer")
    );

--Таблица XP
--ID
--ID проверки
--Количество полученного XP
--За каждую успешную проверку пир, выполнивший задание,
--получает какое-то количество XP, отображаемое в этой таблице.
--Количество XP не может превышать максимальное доступное для проверяемой задачи.
--Первое поле этой таблицы может ссылаться только на успешные проверки.

CREATE TABLE
    IF NOT EXISTS XP (
        "ID" SERIAL PRIMARY KEY,
        "Check" INT NOT NULL,
        "XPAmount" INT NOT NULL,
        CONSTRAINT fk_XPCheck_ChecksTask FOREIGN KEY ("Check") REFERENCES Checks("ID")
    );

--Таблица TimeTracking
--ID
--Ник пира
--Дата
--Время
--Состояние (1 - пришел, 2 - вышел)
--Данная таблица содержит информация о посещениях пирами кампуса.
--Когда пир входит в кампус, в таблицу добавляется запись с состоянием 1,
--когда покидает - с состоянием 2.
--
--В заданиях, относящихся к этой таблице,
--под действием "выходить" подразумеваются все покидания кампуса за день,
--кроме последнего. В течение одного дня должно быть
--одинаковое количество записей с состоянием 1 и состоянием 2 для каждого пира.

CREATE TABLE
    IF NOT EXISTS TimeTracking (
        "ID" SERIAL PRIMARY KEY,
        "Peer" VARCHAR NOT NULL,
        "Date" DATE NOT NULL DEFAULT current_date,
        "Time" TIME WITHOUT TIME ZONE NOT NULL DEFAULT current_time,
        "State" VARCHAR NOT NULL,
        CONSTRAINT fk_TimeTrackingPeer_PeersNickname FOREIGN KEY ("Peer") REFERENCES Peers("Nickname"),
        CONSTRAINT ch_TimeTrackingState check ("State" in ('1', '2'))
    );

CREATE OR REPLACE FUNCTION one_p2p_check_started() 
RETURNS TRIGGER AS 
	$$ BEGIN IF NEW . "State" = 'Start' THEN IF EXISTS ( SELECT * FROM P2P WHERE "Check" = NEW . "Check" AND "CheckingPeer" = New . "CheckingPeer" AND "State" = 'Start' ) THEN RETURN NULL;
	END IF;
	END IF;
	RETURN NEW;
	END;
	$$ LANGUAGE
plpgsql; 

CREATE OR REPLACE FUNCTION verter_check_is_allowed(
) RETURNS TRIGGER AS 
	$$ BEGIN IF NOT EXISTS ( select Checks . "ID" from Checks left join P2P on Checks . "ID" = P2P . "Check" WHERE "State" = 'Success' and Checks . "ID" = NEW . "Check" ) THEN RETURN NULL;
	END IF;
	RETURN NEW;
	END;
	$$ LANGUAGE
plpgsql; 

CREATE OR REPLACE FUNCTION pair_friends() RETURNS TRIGGER 
AS 
	$$ BEGIN IF NOT EXISTS ( SELECT "Peer1" , "Peer2" FROM Friends WHERE "Peer1" = NEW . "Peer2" AND "Peer2" = NEW . "Peer1" ) THEN INSERT INTO Friends ( "Peer1" , "Peer2" ) VALUES ( NEW . "Peer2" , NEW . "Peer1" ) ;
	RETURN NEW;
	ELSE RETURN NULL;
	END IF;
	END;
	$$ LANGUAGE
plpgsql; 

CREATE OR REPLACE TRIGGER 
	t_Friends
	AFTER
	INSERT ON Friends FOR EACH ROW
	EXECUTE FUNCTION pair_friends ()
; 

CREATE OR REPLACE PROCEDURE restore_from_csv(IN table_name VARCHAR, IN file_name VARCHAR, IN sep CHAR) AS 
$$ DECLARE dir text;
	BEGIN dir := '/tmp/CSV/';
	EXECUTE
	    FORMAT (
	        'COPY %s FROM ''%s'' DELIMITER ''%s'' CSV HEADER;', table_name, dir || file_name, sep);
	END;
$$ LANGUAGE plpgsql; 

CALL restore_from_csv('Peers', 'Peers.csv', ',');
CALL restore_from_csv('TimeTracking', 'TimeTracking.csv', ',');
CALL restore_from_csv('Recommendations', 'Recommendations.csv', ',');
CALL restore_from_csv('Friends', 'Friends.csv', ',');
CALL restore_from_csv('TransferredPoints', 'TransferredPoints.csv', ',');
CALL restore_from_csv('Tasks', 'Tasks.csv', ',');
CALL restore_from_csv('Checks', 'Checks.csv', ',');
CALL restore_from_csv('XP', 'XP.csv', ',');
CALL restore_from_csv('P2P', 'P2P.csv', ',');
CALL restore_from_csv('Verter', 'Verter.csv', ',');
	
-- SELECT * FROM P2P;
-- SELECT * FROM Verter;
-- SELECT * FROM XP;
-- SELECT * FROM Checks;
-- SELECT * FROM Tasks;
-- SELECT * FROM TransferredPoints;
-- SELECT * FROM Friends;
-- SELECT * FROM Recommendations;
-- SELECT * FROM TimeTracking;
-- SELECT * FROM Peers;

--1) Создать хранимую процедуру, которая, не уничтожая базу данных, 
--уничтожает все те таблицы текущей базы данных, 
--имена которых начинаются с фразы 'TableName'.
	
CREATE OR REPLACE PROCEDURE delete_tables_by_names(IN name_part text) AS $$
DECLARE
    table_name text;
BEGIN
  FOR table_name IN SELECT tablename FROM pg_tables WHERE schemaname = 'public' AND tablename LIKE name_part || '%'
  LOOP
    EXECUTE format('DROP TABLE IF EXISTS %I CASCADE', table_name);
  END LOOP;
END;
$$ LANGUAGE plpgsql;

CALL delete_tables_by_names('transf');


	
--2) Создать хранимую процедуру с выходным параметром, 
--которая выводит список имен и параметров всех скалярных SQL 
--функций пользователя в текущей базе данных. Имена функций без параметров не выводить. 
--Имена и список параметров должны выводиться в одну строку. 
--Выходной параметр возвращает количество найденных функций.
	
CREATE OR REPLACE PROCEDURE scalar_funcs_with_params(OUT counter integer) AS $$
  DECLARE
    record RECORD; --для итерации по результатам курсора
    fname VARCHAR = '';
    fparam VARCHAR = '';
  BEGIN
    counter = 0;
    RAISE NOTICE ' List of names and parameters of all scalar users SQL functions in the current database.';
    FOR record IN
        SELECT routines.routine_name, parameters.data_type
        FROM information_schema.routines
            LEFT JOIN information_schema.parameters ON routines.specific_name=parameters.specific_name
        WHERE routines.specific_schema NOT IN ('information_schema', 'pg_catalog') AND
              parameters.ordinal_position IS NOT NULL
        ORDER BY routines.routine_name, parameters.ordinal_position
    LOOP
        IF fname != record.routine_name
        THEN
            IF fname != ''
            THEN
                RAISE NOTICE '%(%)', fname, fparam;
            END IF;
            counter = counter + 1;
            fname = record.routine_name;
            fparam = record.data_type;
        ELSE
            fparam = fparam || ', ' || record.data_type;
        END IF;
    END LOOP;
    IF fname != ''
    THEN
        RAISE NOTICE '%(%)', fname, fparam;
    END IF;
  END
$$ LANGUAGE PLPGSQL;

DO $$
DECLARE counter int := 0;
BEGIN
  CALL scalar_funcs_with_params(counter);
  RAISE NOTICE 'counter = %', counter;
END;
$$;

	
--3) Создать хранимую процедуру с выходным параметром, которая уничтожает все 
--SQL DML триггеры в текущей базе данных. Выходной параметр возвращает количество уничтоженных триггеров.
	
CREATE OR REPLACE PROCEDURE delete_dml_trig(OUT cnt INTEGER)AS $$
DECLARE
    record RECORD;
BEGIN
    cnt := 0;
    FOR record IN
        SELECT trigger_name, event_object_table
        FROM information_schema.triggers
        WHERE trigger_catalog = current_database() AND trigger_schema = 'public'
          		AND event_manipulation IN ('INSERT', 'UPDATE', 'DELETE')
    LOOP
        EXECUTE format('DROP TRIGGER IF EXISTS %I ON %I CASCADE', record.trigger_name, record.event_object_table);
        cnt := cnt + 1;
    END LOOP;
    RAISE NOTICE 'count: %', cnt;
END
$$ LANGUAGE plpgsql;

DO $$
DECLARE
    counter INTEGER := 0;
BEGIN
    CALL delete_dml_trig(counter);
END;
$$;


--4) Создать хранимую процедуру с входным параметром, 
--которая выводит имена и описания типа объектов (только хранимых процедур и скалярных функций), 
--в тексте которых на языке SQL встречается строка, задаваемая параметром процедуры.

CREATE OR REPLACE PROCEDURE find_by_text(IN find TEXT) AS $$
DECLARE
  record RECORD;
BEGIN
  FOR record IN
    SELECT routine_name, routine_type, data_type, routine_body
    FROM information_schema.routines
    WHERE routines.routine_body = 'SQL'
    AND (routine_name LIKE '%' || find || '%' or routine_definition LIKE '%' || find || '%')
  LOOP
    RAISE NOTICE 'Name: %, Type: %, Return type: %, Body: %', record.routine_name, record.routine_type, record.data_type, record.routine_body;
  END LOOP;
END;
$$ LANGUAGE plpgsql;

CALL find_by_text('length');
CALL find_by_text('WTF');
