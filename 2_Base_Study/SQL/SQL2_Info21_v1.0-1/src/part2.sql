-- Создайте скрипт part2.sql, в который, помимо описанного ниже, внесите тестовые запросы / вызовы для каждого пункта.

-- 1) Написать процедуру добавления P2P проверки Параметры:
-- ник проверяемого, ник проверяющего, название задания,
-- статус P2P проверки, время.
-- Если задан статус "начало", добавить запись в таблицу Checks ( в качестве даты использовать сегодняшнюю).
-- Добавить запись в таблицу P2P.Если задан статус "начало", в качестве проверки указать только что добавленную запись,
-- иначе указать проверку с незавершенным P2P этапом.

CREATE OR REPLACE PROCEDURE p2p_add(IN checked_peer VARCHAR, IN checkering_peer VARCHAR, IN task_name VARCHAR, IN check_state CheckStatus, IN check_time TIME) AS $$
    BEGIN
        IF check_state = 'Start' THEN
            INSERT INTO Checks VALUES ((SELECT MAX("ID")+1 FROM Checks), checked_peer , task_name , CURRENT_DATE);
        END IF;
        INSERT INTO P2P VALUES (
            (SELECT MAX("ID") + 1 FROM P2P),
            (SELECT MAX ("ID") FROM Checks), 
            checkering_peer, check_state, check_time);
	END;
$$ LANGUAGE plpgsql; 

CALL p2p_add( 'User5', 'User4', 'Task0', 'Start', '17:00:00');
CALL p2p_add( 'User5', 'User4', 'Task0', 'Success', '17:12:00');
select * from p2p;
select * from checks;

-- 2) Написать процедуру добавления проверки Verterом
-- Параметры: ник проверяемого, название задания, статус проверки Verterом, время.
-- Добавить запись в таблицу Verter (в качестве проверки указать проверку соответствующего 
-- задания с самым поздним (по времени) успешным P2P этапом)

CREATE OR REPLACE PROCEDURE verter_add(IN nickname VARCHAR, IN task VARCHAR, check_state CheckStatus, IN check_time TIME) AS $$ 
    BEGIN 
        INSERT INTO Verter VALUES 
            ((SELECT MAX("ID") + 1 FROM Verter),
             (SELECT Checks."ID" FROM Checks JOIN Tasks ON Tasks."Title" = Checks."Task" JOIN P2P ON Checks."ID" = P2P."Check" 
             WHERE "Peer" = nickname AND Tasks."Title" = task AND P2P."State" = 'Success' ORDER BY P2P."Time" DESC LIMIT 1),
             check_state, 
             check_time) ;
	END 
$$ LANGUAGE plpgsql;

CALL verter_add('User5', 'Task0', 'Start', '17:15:00');
CALL verter_add('User5', 'Task0', 'Success', '17:17:00');

SELECT * FROM verter ORDER BY "ID" DESC LIMIT 3;

-- 3) Написать триггер: после добавления записи со статутом "начало" в таблицу P2P,
-- изменить соответствующую запись в таблице TransferredPoints 

SELECT * FROM P2P;

CREATE OR REPLACE FUNCTION trans_points_add() RETURNS TRIGGER AS $$ 
	BEGIN
        IF (NEW."State" = 'Start') THEN
            IF EXISTS (SELECT "PointsAmount" FROM TransferredPoints WHERE "CheckingPeer"=NEW."CheckingPeer" AND "CheckedPeer" = (SELECT "Peer" from Checks where "ID" = NEW."Check")) THEN
                UPDATE TransferredPoints VALUES SET 
                    "PointsAmount" = (SELECT "PointsAmount" FROM TransferredPoints WHERE "CheckingPeer"=NEW."CheckingPeer" AND "CheckedPeer" = (SELECT "Peer" from Checks where "ID" = NEW."Check")) + 1 WHERE "CheckingPeer" = NEW."CheckingPeer" AND "CheckedPeer" = (SELECT "Peer" from Checks where "ID" = NEW."Check");
            ELSE
            INSERT INTO TransferredPoints VALUES (
                    (SELECT MAX("ID") + 1 from TransferredPoints),
                    NEW."CheckingPeer",
                    (SELECT "Peer" from Checks where "ID" = NEW."Check"),
                    1);
            END IF;
	    END IF;
        RETURN NEW;
	END;
$$ LANGUAGE plpgsql; 

CREATE OR REPLACE TRIGGER t_TransferredPoints AFTER	INSERT ON P2P FOR EACH ROW EXECUTE FUNCTION trans_points_add();

CALL p2p_add( 'User5', 'User4', 'Task0', 'Start', '17:20:00' );

CALL p2p_add( 'User5', 'User4', 'Task0', 'Start', '17:32:00' );


-- 4) Написать триггер: перед добавлением записи в таблицу XP,проверить корректность добавляемой записи Запись считается корректной,
-- если: Количество XP не превышает максимальное доступное для проверяемой задачи.
-- Поле Check ссылается на успешную проверку Если запись не прошла проверку, не добавлять её в таблицу.

