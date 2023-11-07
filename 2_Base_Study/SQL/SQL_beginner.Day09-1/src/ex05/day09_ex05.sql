-- Exercise 06: Function like a function-wrapper	
-- Turn-in directory	ex06
-- Files to turn-in	day09_ex06.sql
-- Allowed	
-- Language	SQL, DDL, DML
-- Let’s look at pl/pgsql functions right now.

-- Please create a pl/pgsql function fnc_person_visits_and_eats_on_date based on SQL statement that finds the names of pizzerias which person (IN pperson parameter with default value is ‘Dmitriy’) visited and in which he could buy pizza for less than the given sum in rubles (IN pprice parameter with default value is 500) on the specific date (IN pdate parameter with default value is 8th of January 2022).

-- To check yourself and call a function, you can make a statement like below.

-- select *
-- from fnc_person_visits_and_eats_on_date(pprice := 800);

-- select *
-- from fnc_person_visits_and_eats_on_date(pperson := 'Anna',pprice := 1300,pdate := '2022-01-01');

DROP FUNCTION IF EXISTS fnc_persons_female();
DROP FUNCTION IF EXISTS fnc_persons_male();
DROP FUNCTION IF EXISTS fnc_persons(pgender VARCHAR);

CREATE FUNCTION fnc_persons(pgender VARCHAR DEFAULT 'female')
    RETURNS TABLE (
        id bigint,
        name varchar,
        age int,
        gender varchar,
        address varchar) AS
$$ SELECT * FROM person WHERE gender = pgender; $$ LANGUAGE SQL;

SELECT * FROM fnc_persons(pgender := 'male');

SELECT * FROM fnc_persons();