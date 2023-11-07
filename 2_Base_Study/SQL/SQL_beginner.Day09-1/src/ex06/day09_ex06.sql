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



CREATE OR REPLACE FUNCTION fnc_person_visits_and_eats_on_date (pperson VARCHAR DEFAULT 'Dmitry', pprice NUMERIC DEFAULT 500, pdate DATE DEFAULT '2022-01-08')
    RETURNS TABLE (pizzeria_name VARCHAR) AS 
$$
BEGIN
RETURN QUERY
    SELECT pizzeria.name AS pizzeria_name
    FROM menu JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
    JOIN person_visits ON menu.pizzeria_id = person_visits.pizzeria_id
    JOIN person ON person.id = person_visits.person_id
    WHERE price < pprice AND person.name = pperson AND visit_date = pdate;
END;
$$ LANGUAGE plpgsql;

SELECT * FROM fnc_person_visits_and_eats_on_date(pprice := 800);
SELECT * FROM fnc_person_visits_and_eats_on_date(pperson := 'Anna', pprice := 1300, pdate := '2022-01-01');
