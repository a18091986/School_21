-- Exercise 04: Let’s compare orders	
-- Turn-in directory	ex04
-- Files to turn-in	day03_ex04.sql
-- Allowed	
-- Language	ANSI SQL

-- Please find a union of pizzerias that have orders either from women or from men. Other words, you should find a set of pizzerias names have been ordered by females only and make "UNION" operation with set of pizzerias names have been ordered by males only. Please be aware with word “only” for both genders. For any SQL operators with sets don’t save duplicates (UNION, EXCEPT, INTERSECT). Please sort a result by the pizzeria name. The data sample is provided below.

WITH 
    all_orders AS 
        (SELECT gender, pizzeria.name FROM
            person_order
        JOIN
            person
        ON person_order.person_id = person.id
        JOIN menu
        ON person_order.menu_id = menu.id
        JOIN
            pizzeria
        ON pizzeria.id = menu.pizzeria_id),
    male_visiters AS 
        (SELECT name FROM all_orders WHERE gender = 'male'
        EXCEPT
        SELECT name FROM all_orders WHERE gender = 'female'),
    female_visiters AS 
        (SELECT name FROM all_orders WHERE gender = 'female'
        EXCEPT
        SELECT name FROM all_orders WHERE gender = 'male')
SELECT name pizzeria_name FROM male_visiters
UNION
SELECT name pizzeria_name FROM female_visiters
ORDER BY pizzeria_name;