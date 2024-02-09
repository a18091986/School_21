DROP TRIGGER IF EXISTS t_Friends ON Friends;
DROP TRIGGER IF EXISTS t_Verter ON Verter;
DROP TRIGGER IF EXISTS t_P2P ON P2P;
DROP TRIGGER IF EXISTS t_Tasks ON Tasks;
DROP TRIGGER IF EXISTS t_TransferredPoints ON TransferredPoints;
DROP TRIGGER IF EXISTS t_XP ON XP;

DROP PROCEDURE IF EXISTS backup_to_csv;
DROP PROCEDURE IF EXISTS p2p_add;
DROP PROCEDURE IF EXISTS restore_from_csv;
DROP PROCEDURE IF EXISTS verter_add;
DROP FUNCTION IF EXISTS pair_friends();

DROP FUNCTION IF EXISTS verter_check_is_allowed();

DROP FUNCTION IF EXISTS one_p2p_check_started();

DROP FUNCTION IF EXISTS check_parent_task();

DROP PROCEDURE IF EXISTS p2p_add();

DROP PROCEDURE IF EXISTS verter_add();

DROP FUNCTION IF EXISTS XP_add();

DROP TABLE IF EXISTS P2P;

DROP TABLE IF EXISTS Verter;

DROP TABLE IF EXISTS XP;

DROP TABLE IF EXISTS Checks;

DROP TABLE IF EXISTS Tasks;

DROP TABLE IF EXISTS TransferredPoints;

DROP FUNCTION IF EXISTS trans_points_add();

DROP TABLE IF EXISTS Friends;

DROP TABLE IF EXISTS Recommendations;

DROP TABLE IF EXISTS TimeTracking;

DROP TABLE IF EXISTS Peers;

DROP TYPE IF EXISTS CheckStatus;

-----tables creation-------
--Таблица Peers
--Ник пира
--День рождения

CREATE TABLE
    IF NOT EXISTS Peers (
        "Nickname" VARCHAR PRIMARY KEY NOT NULL,
        "Birthday" DATE NOT NULL
    );

--Таблица Tasks
--Название задания
--Название задания, являющегося условием входа
--Максимальное количество XP

--Чтобы получить доступ к заданию, нужно выполнить задание, являющееся его условием входа.
--Для упрощения будем считать, что у каждого задания всего одно условие входа.
--В таблице должно быть одно задание, у которого нет условия входа (т.е. поле ParentTask равно null).

CREATE TABLE
    IF NOT EXISTS Tasks (
        "Title" VARCHAR PRIMARY KEY NOT NULL UNIQUE,
        "ParentTask" VARCHAR DEFAULT 'NULL',
        "MaxXP" INT NOT NULL,
        CONSTRAINT fk_TasksParentTask_TasksTitle FOREIGN KEY ("ParentTask") REFERENCES Tasks("Title"),
        CONSTRAINT ch_ParentTask_not_eq_Title CHECK ("ParentTask" != "Title")
    );

--Статус проверки
--Создать тип перечисления для статуса проверки, содержащий следующие значения:
--
--Start - начало проверки
--Success - успешное окончание проверки
--Failure - неудачное окончание проверки

CREATE TYPE CheckStatus AS ENUM('Start', 'Success', 'Failure');

--Таблица Checks
--ID
--Ник пира
--Название задания
--Дата проверки
--Описывает проверку задания в целом.
--Проверка обязательно включает в себя один этап P2P и, возможно, этап Verter.
--Для упрощения будем считать, что пир ту пир и автотесты,
--относящиеся к одной проверке, всегда происходят в один день.

--Проверка считается успешной, если соответствующий P2P этап успешен,
--а этап Verter успешен, либо отсутствует.
--Проверка считается неуспешной, хоть один из этапов неуспешен.
--То есть проверки, в которых ещё не завершился этап P2P,
--или этап P2P успешен, но ещё не завершился этап Verter,
--не относятся ни к успешным, ни к неуспешным.

CREATE TABLE
    IF NOT EXISTS Checks (
        "ID" SERIAL PRIMARY KEY,
        "Peer" VARCHAR NOT NULL,
        "Task" VARCHAR NOT NULL,
        "Date" DATE NOT NULL DEFAULT CURRENT_DATE,
        CONSTRAINT fk_ChecksPeer_PeersNickname FOREIGN KEY ("Peer") REFERENCES Peers("Nickname"),
        CONSTRAINT fk_ChecksTask_TasksTitle FOREIGN KEY ("Task") REFERENCES Tasks("Title")
    );

--Таблица P2P
--ID
--ID проверки
--Ник проверяющего пира
--Статус P2P проверки
--Время
--Каждая P2P проверка состоит из 2-х записей в таблице: первая имеет статус начало,
--вторая - успех или неуспех.
--В таблице не может быть больше одной незавершенной P2P проверки,
--относящейся к конкретному заданию, пиру и проверяющему.
--Каждая P2P проверка (т.е. обе записи, из которых она состоит)
--ссылается на проверку в таблице Checks, к которой она относится.

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

--Таблица Verter
--ID
--ID проверки
--Статус проверки Verter'ом
--Время
--Каждая проверка Verter'ом состоит из 2-х записей в таблице:
--первая имеет статус начало, вторая - успех или неуспех.
--Каждая проверка Verter'ом (т.е. обе записи, из которых она состоит)
--ссылается на проверку в таблице Checks, к которой она относится.
--Проверка Verter'ом может ссылаться только на те проверки в таблице Checks,
--которые уже включают в себя успешную P2P проверку.

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

CREATE OR REPLACE FUNCTION check_parent_task() RETURNS TRIGGER AS $$ 
	BEGIN 
		IF NEW."ParentTask" IS NULL THEN 
			IF EXISTS ( SELECT * FROM Tasks WHERE "ParentTask" IS NULL ) 
			THEN RETURN NULL;
			END IF;
		END IF;
		IF NEW."ParentTask" IS NOT NULL THEN 
			IF NOT EXISTS (SELECT * FROM Tasks WHERE "ParentTask" IS NULL) 
			THEN RETURN NULL;
			END IF;
		END IF;
	RETURN NEW;
	END;
$$ LANGUAGE plpgsql; 

CREATE OR REPLACE FUNCTION one_p2p_check_started() RETURNS TRIGGER AS $$ 
	BEGIN 
		IF NEW."State" = 'Start' 
			THEN 
				IF EXISTS (SELECT * FROM P2P WHERE "Check" = NEW."Check" AND "CheckingPeer" = New."CheckingPeer" AND "State" = 'Start' ) 
				THEN RETURN NULL;
				END IF;
		END IF;
	RETURN NEW;
	END;
$$ LANGUAGE plpgsql; 

CREATE OR REPLACE FUNCTION verter_check_is_allowed() RETURNS TRIGGER AS $$ 
	BEGIN 
		IF NOT EXISTS (select Checks."ID" from Checks left join P2P on Checks."ID" = P2P."Check" WHERE "State" = 'Success' and Checks."ID" = NEW."Check" ) 
		THEN RETURN NULL;
		END IF;
	RETURN NEW;
	END;
$$ LANGUAGE plpgsql; 

CREATE OR REPLACE FUNCTION pair_friends() RETURNS TRIGGER AS $$ 
	BEGIN 
		IF NOT EXISTS (SELECT "Peer1" , "Peer2" FROM Friends WHERE "Peer1" = NEW."Peer2" AND "Peer2" = NEW."Peer1") 
			THEN INSERT INTO Friends ( "Peer1" , "Peer2" ) VALUES ( NEW."Peer2" , NEW."Peer1" );
			RETURN NEW;
		ELSE RETURN NULL;
		END IF;
	END;
$$ LANGUAGE plpgsql; 

CREATE OR REPLACE TRIGGER t_Friends	AFTER INSERT ON Friends FOR EACH ROW EXECUTE FUNCTION pair_friends (); 

CREATE OR REPLACE TRIGGER t_Verter BEFORE INSERT OR	UPDATE ON Verter FOR EACH ROW EXECUTE FUNCTION verter_check_is_allowed (); 

CREATE OR REPLACE TRIGGER t_P2P BEFORE INSERT OR UPDATE ON P2P FOR EACH ROW	EXECUTE FUNCTION one_p2p_check_started (); 

CREATE OR REPLACE TRIGGER t_Tasks BEFORE INSERT OR UPDATE ON Tasks FOR EACH ROW EXECUTE FUNCTION check_parent_task (); 


CREATE OR REPLACE PROCEDURE restore_from_csv(IN table_name VARCHAR, IN file_name VARCHAR, IN sep CHAR) AS 
$$ DECLARE dir text;
	BEGIN dir := '/tmp/CSV/';
	EXECUTE
	    FORMAT (
	        'COPY %s FROM ''%s'' DELIMITER ''%s'' CSV HEADER;', table_name, dir || file_name, sep);
	END;
$$ LANGUAGE plpgsql; 

CREATE OR REPLACE PROCEDURE backup_to_csv(IN table_name VARCHAR, IN file_name VARCHAR, IN sep CHAR) AS 
$$ DECLARE dir text;
	BEGIN dir := '/tmp/CSV/';
	EXECUTE
	    FORMAT ('copy %s TO ''%s'' DELIMITER ''%s'' CSV HEADER;', table_name, dir || file_name, sep);
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

--CALL backup_to_csv('Peers', 'Peers.csv', ',');
--CALL backup_to_csv('TimeTracking', 'TimeTracking.csv', ',');
--CALL backup_to_csv('Recommendations', 'Recommendations.csv', ',');
--CALL backup_to_csv('Friends', 'Friends.csv', ',');
--CALL backup_to_csv('TransferredPoints', 'TransferredPoints.csv', ',');
--CALL backup_to_csv('Tasks', 'Tasks.csv', ',');
--CALL backup_to_csv('Checks', 'Checks.csv', ',');
--CALL backup_to_csv('XP', 'XP.csv', ',');
--CALL backup_to_csv('P2P', 'P2P.csv', ',');
--CALL backup_to_csv('Verter', 'Verter.csv', ',');


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