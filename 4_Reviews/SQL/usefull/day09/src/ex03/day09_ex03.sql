-- Exercise 03: Generic Audit	
-- Turn-in directory	ex03
-- Files to turn-in	day09_ex03.sql
-- Allowed	
-- Language	SQL, DDL, DML
-- Actually, there are 3 triggers for one person table. Let’s merge all our logic to the one main trigger with the name trg_person_audit and a new corresponding trigger function fnc_trg_person_audit.

-- Other words, all DML traffic (INSERT, UPDATE, DELETE) should be handled from the one functional block. Please explicitly define a separated IF-ELSE block for every event (I, U, D)!

-- Additionally, please take the steps below .

-- to drop 3 old triggers from the person table.
-- to drop 3 old trigger functions
-- to make a TRUNCATE (or DELETE) of all rows in our person_audit table
-- When you are ready, please re-apply the set of DML statements. INSERT INTO person(id, name, age, gender, address) VALUES (10,'Damir', 22, 'male', 'Irkutsk'); UPDATE person SET name = 'Bulat' WHERE id = 10; UPDATE person SET name = 'Damir' WHERE id = 10; DELETE FROM person WHERE id = 10;

DROP TRIGGER IF EXISTS trg_person_insert_audit ON person;
DROP TRIGGER IF EXISTS trg_person_update_audit ON person;
DROP TRIGGER  IF EXISTS trg_person_delete_audit ON person;

DROP FUNCTION IF EXISTS fnc_trg_person_insert_audit;
DROP FUNCTION IF EXISTS fnc_trg_person_update_audit;
DROP FUNCTION IF EXISTS fnc_trg_person_delete_audit;

CREATE OR REPLACE FUNCTION fnc_trg_person_audit() RETURNS trigger AS
$trg_person_audit$
BEGIN
    IF
        (TG_OP = 'UPDATE') THEN INSERT INTO person_audit
        SELECT CURRENT_TIMESTAMP AT TIME ZONE 'Europe/Moscow', 'U', NEW.*;
    ELSEIF (TG_OP = 'INSERT') THEN INSERT INTO person_audit
        SELECT CURRENT_TIMESTAMP AT TIME ZONE 'Europe/Moscow', 'I', NEW.*;
    ELSEIF (TG_OP = 'DELETE') THEN INSERT INTO person_audit
        SELECT CURRENT_TIMESTAMP AT TIME ZONE 'Europe/Moscow', 'D', OLD.*;
    END IF;
    RETURN NULL;
END;
$trg_person_audit$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER trg_person_audit AFTER INSERT OR UPDATE OR DELETE ON person FOR EACH ROW
EXECUTE FUNCTION fnc_trg_person_audit();

-- select * from person_audit;
