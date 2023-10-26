-- Exercise 01: Audit of incoming updates	
-- Turn-in directory	ex01
-- Files to turn-in	day09_ex01.sql
-- Allowed	
-- Language	SQL, DDL, DML
-- Let’s continue to implement our audit pattern for the person table. Just define a trigger trg_person_update_audit and corresponding trigger function fnc_trg_person_update_audit to handle all UPDATE traffic on the person table. We should save OLD states of all attribute’s values.

-- When you are ready please apply UPDATE’s statements below.

-- UPDATE person SET name = 'Bulat' WHERE id = 10; UPDATE person SET name = 'Damir' WHERE id = 10;

CREATE OR REPLACE FUNCTION fnc_trg_person_update_audit() 
RETURNS TRIGGER AS $trg_person_update_audit$
BEGIN
    IF (TG_OP = 'UPDATE') THEN
        INSERT INTO person_audit
        SELECT CURRENT_TIMESTAMP AT TIME ZONE 'Europe/Moscow', 'U', OLD.*;
    END IF;
    RETURN NULL;
END;
$trg_person_update_audit$ LANGUAGE plpgsql;

CREATE TRIGGER trg_person_update_audit
AFTER UPDATE ON person FOR EACH ROW
EXECUTE FUNCTION fnc_trg_person_update_audit();

UPDATE person SET name = 'Bulat' WHERE id = 10; 
UPDATE person SET name = 'Damir' WHERE id = 10;

select * from person_audit;