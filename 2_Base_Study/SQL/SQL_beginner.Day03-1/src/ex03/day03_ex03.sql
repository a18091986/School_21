-- Exercise 03: Let’s compare visits	
-- Turn-in directory	ex03
-- Files to turn-in	day03_ex03.sql
-- Allowed	
-- Language	ANSI SQL

-- Please find pizzerias that have been visited more often by women or by men. For any SQL operators with sets save duplicates (UNION ALL, EXCEPT ALL, INTERSECT ALL constructions). Please sort a result by the pizzeria name. The data sample is provided below.

WITH 
    all_visiters AS 
        (SELECT gender, pizzeria.name FROM
            person_visits
        JOIN
            person
        ON person_visits.person_id = person.id
        JOIN
            pizzeria
        ON pizzeria.id = person_visits.pizzeria_id),
    male_visiters AS 
        (SELECT name FROM all_visiters WHERE gender = 'male'
        EXCEPT ALL
        SELECT name FROM all_visiters WHERE gender = 'female'),
    female_visiters AS 
        (SELECT name FROM all_visiters WHERE gender = 'female'
        EXCEPT ALL
        SELECT name FROM all_visiters WHERE gender = 'male')
SELECT name pizzeria_name FROM male_visiters
UNION ALL
SELECT name pizzeria_name FROM female_visiters
ORDER BY pizzeria_name;