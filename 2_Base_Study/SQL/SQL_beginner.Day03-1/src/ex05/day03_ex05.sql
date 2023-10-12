-- Exercise 05: Visited but did not make any order	
-- Turn-in directory	ex05
-- Files to turn-in	day03_ex05.sql
-- Allowed	
-- Language	ANSI SQL

-- Please write a SQL statement which returns a list of pizzerias which Andrey visited but did not make any orders. Please order by the pizzeria name. The sample of data is provided below.

WITH 
    visited AS
        (SELECT pizzeria.name FROM
            person_visits
        JOIN
            person
        ON person_visits.person_id = person.id
        JOIN
            pizzeria
        ON pizzeria.id = person_visits.pizzeria_id
        WHERE person.name = 'Andrey'),
    ordered AS
        (SELECT pizzeria.name FROM
            person_order
        JOIN
            person
        ON person.id = person_order.person_id
        JOIN
            menu
        ON person_order.menu_id = menu.id
        JOIN
            pizzeria
        ON pizzeria.id = menu.pizzeria_id
        WHERE person.name = 'Andrey')
SELECT * FROM visited
EXCEPT
SELECT * FROM ordered
ORDER BY 1;