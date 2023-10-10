CREATE TABLE person_audit
( created  timestamp with time zone NOT NULL DEFAULT (CURRENT_TIMESTAMP),
  type_event char(1)  CONSTRAINT ch_type_event CHECK (type_event IN ('I', 'U', 'D')),
  row_id bigint NOT NULL,
  name varchar,
  age integer,
  gender varchar,
  address varchar
);

CREATE OR REPLACE FUNCTION fnc_trg_person_insert_audit()
    RETURNS trigger AS $trg_person_insert_audit$
    BEGIN
        IF (TG_OP = 'INSERT') THEN
            INSERT INTO person_audit
            SELECT CURRENT_TIMESTAMP, 'I', NEW.id, NEW.name,
                   NEW.age, NEW.gender, NEW.address;
        END IF;
        RETURN NULL;
END;
$trg_person_insert_audit$ LANGUAGE plpgsql;

CREATE TRIGGER trg_person_insert_audit
    AFTER INSERT ON person
    FOR EACH ROW EXECUTE FUNCTION fnc_trg_person_insert_audit();

INSERT INTO person(id, name, age, gender, address)
VALUES (10,'Damir', 22, 'male', 'Irkutsk');

select * from person_audit
-- 1
CREATE OR REPLACE FUNCTION fnc_trg_person_update_audit()
    RETURNS trigger AS $trg_person_update_audit$
BEGIN
    IF (TG_OP = 'UPDATE') THEN
        INSERT INTO person_audit
        SELECT CURRENT_TIMESTAMP, 'U', OLD.id, OLD.name,
               OLD.age, OLD.gender, OLD.address;
    END IF;
    RETURN NULL;
END;
$trg_person_update_audit$ LANGUAGE plpgsql;

CREATE TRIGGER trg_person_update_audit
    AFTER UPDATE ON person
    FOR EACH ROW EXECUTE FUNCTION fnc_trg_person_update_audit();

UPDATE person SET name = 'Bulat' WHERE id = 10;
UPDATE person SET name = 'Damir' WHERE id = 10;


select * from person_audit

-- 2

CREATE OR REPLACE FUNCTION fnc_trg_person_delete_audit()
    RETURNS trigger AS $trg_person_delete_audit$
BEGIN
    IF (TG_OP = 'DELETE') THEN
        INSERT INTO person_audit
        SELECT CURRENT_TIMESTAMP, 'D', OLD.id, OLD.name,
               OLD.age, OLD.gender, OLD.address;
    END IF;
    RETURN NULL;
END;
$trg_person_delete_audit$ LANGUAGE plpgsql;

CREATE TRIGGER trg_person_delete_audit
    AFTER DELETE ON person
    FOR EACH ROW EXECUTE FUNCTION fnc_trg_person_delete_audit();

DELETE FROM person WHERE id = 10;

select * from person_audit order by created;

-- 3

DROP TRIGGER trg_person_insert_audit ON person;
DROP TRIGGER trg_person_update_audit ON person;
DROP TRIGGER trg_person_delete_audit ON person;

DROP FUNCTION fnc_trg_person_delete_audit();
DROP FUNCTION fnc_trg_person_insert_audit();
DROP FUNCTION fnc_trg_person_update_audit();

DELETE FROM person_audit;

CREATE OR REPLACE FUNCTION fnc_trg_person_audit() RETURNS TRIGGER AS
$trg_person_audit$
BEGIN
    IF (TG_OP = 'INSERT') THEN
        INSERT INTO person_audit SELECT CURRENT_TIMESTAMP, 'I', NEW.id, NEW.name,
                                        NEW.age, NEW.gender, NEW.address;
    ELSIF (TG_OP = 'UPDATE') THEN
        INSERT INTO person_audit SELECT CURRENT_TIMESTAMP, 'U', OLD.id, OLD.name,
                                        OLD.age, OLD.gender, OLD.address;
    ELSIF (TG_OP = 'DELETE') THEN
        INSERT INTO person_audit SELECT CURRENT_TIMESTAMP, 'D', OLD.id, OLD.name,
                                        OLD.age, OLD.gender, OLD.address;
    END IF;
    RETURN NULL;
END;
$trg_person_audit$ LANGUAGE plpgsql;


CREATE TRIGGER trg_person_audit
    AFTER INSERT OR UPDATE OR DELETE ON person
    FOR EACH ROW EXECUTE FUNCTION fnc_trg_person_audit();

INSERT INTO person(id, name, age, gender, address)
VALUES (10,'Damir', 22, 'male', 'Irkutsk');
UPDATE person SET name = 'Bulat' WHERE id = 10;
UPDATE person SET name = 'Damir' WHERE id = 10;
DELETE FROM person WHERE id = 10;

 select * from person_audit order by created;        


--  4

CREATE OR REPLACE FUNCTION fnc_persons_female()
    RETURNS TABLE (id integer,
                   name varchar,
                   age integer,
                   gender varchar,
                   address varchar) AS $$
        SELECT id, name, age, gender, address
        FROM person
        WHERE gender = 'female';
$$ LANGUAGE SQL;

CREATE OR REPLACE FUNCTION fnc_persons_male()
    RETURNS TABLE (id integer,
                   name varchar,
                   age integer,
                   gender varchar,
                   address varchar) AS $$
        SELECT id, name, age, gender, address
        FROM person
        WHERE gender = 'male';
$$ LANGUAGE SQL;

 select * from fnc_persons_male();
 select * from fnc_persons_female();


--  5

DROP FUNCTION fnc_persons_female();
DROP FUNCTION fnc_persons_male();

CREATE OR REPLACE FUNCTION fnc_persons(IN pgender varchar DEFAULT 'female')
    RETURNS TABLE (id bigint,
                   name varchar,
                   age integer,
                   gender varchar,
                   address varchar
    ) AS $$
SELECT *
FROM person
WHERE pgender = person.gender
$$ LANGUAGE SQL;

SELECT * FROM fnc_persons(pgender := 'male');

SELECT * FROM fnc_persons();

-- 6

CREATE OR REPLACE FUNCTION fnc_person_visits_and_eats_on_date(IN pperson varchar DEFAULT 'Dmitriy',
                                                              IN pprice numeric DEFAULT 500,
                                                              IN pdate date DEFAULT '2022-01-08')
RETURNS TABLE(name varchar) AS $$
BEGIN
    RETURN QUERY(
        SELECT pz.name AS pizzeria_name
        FROM person_visits pv
        JOIN pizzeria pz ON pv.pizzeria_id = pz.id
        JOIN menu m on pz.id = m.pizzeria_id
        JOIN person p ON pv.person_id = p.id
        WHERE p.name = pperson AND m.price < pprice
          AND pv.visit_date = pdate
);
END;
$$ LANGUAGE plpgsql;

SELECT *
FROM fnc_person_visits_and_eats_on_date(pprice := 800);

SELECT *
FROM fnc_person_visits_and_eats_on_date(pperson := 'Anna',pprice := 1300,pdate := '2022-01-01');

-- 7

CREATE OR REPLACE FUNCTION func_minimum(VARIADIC arr NUMERIC[])
RETURNS NUMERIC AS $$
BEGIN
    RETURN (
        SELECT MIN(value)
        FROM unnest(arr) AS value
    );
END;
$$ LANGUAGE plpgsql;

SELECT func_minimum(VARIADIC arr => ARRAY [10.0, -1.0, 5.0, 4.4]);


-- 8

CREATE OR REPLACE FUNCTION fnc_fibonacci(pstop integer DEFAULT 10)
    RETURNS SETOF INTEGER
    LANGUAGE SQL
AS $$
WITH RECURSIVE fib(a,b) AS (
    VALUES(0,1)
    UNION ALL
    SELECT greatest(a,b), a + b AS a FROM fib
    WHERE b < $1
)
SELECT a FROM fib;
$$;

select * from fnc_fibonacci(20);
select * from fnc_fibonacci();