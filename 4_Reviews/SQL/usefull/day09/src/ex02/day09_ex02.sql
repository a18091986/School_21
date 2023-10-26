-- Exercise 02: Audit of incoming deletes	
-- Turn-in directory	ex02
-- Files to turn-in	day09_ex02.sql
-- Allowed	
-- Language	SQL, DDL, DML
-- Finally, we need to handle DELETE statements and make a copy of OLD states for all attribute’s values. Please create a trigger trg_person_delete_audit and corresponding trigger function fnc_trg_person_delete_audit.

-- When you are ready please apply the SQL statement below.

-- DELETE FROM person WHERE id = 10;

CREATE OR REPLACE FUNCTION fnc_trg_person_delete_audit() 
RETURNS TRIGGER AS $trg_person_delete_audit$
BEGIN
    IF (TG_OP = 'DELETE') THEN
        INSERT INTO person_audit
        SELECT CURRENT_TIMESTAMP AT TIME ZONE 'Europe/Moscow', 'D', OLD.*;
    END IF;
    RETURN NULL;
END;
$trg_person_delete_audit$ LANGUAGE plpgsql;

CREATE OR REPLACE TRIGGER trg_person_delete_audit
AFTER DELETE ON person FOR EACH ROW
EXECUTE FUNCTION fnc_trg_person_delete_audit();

DELETE FROM person WHERE id = 10;

select * from person_audit;
