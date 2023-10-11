-- Exercise 07: Cheapest pizzeria for Dmitriy	
-- Turn-in directory	ex07
-- Files to turn-in	day02_ex07.sql
-- Allowed	
-- Language	ANSI SQL

-- Please find the name of pizzeria Dmitriy visited on January 8, 2022 and could eat pizza for less than 800 rubles.

SELECT
    name
FROM pizzeria 
WHERE id IN 
    (SELECT 
        pizzeria_id FROM menu WHERE price < 800 
    AND 
    pizzeria_id IN 
        (SELECT 
            pizzeria_id FROM person_visits 
        WHERE 
            visit_date = '2022-01-08' AND person_id = 
                (SELECT id FROM person WHERE name = 'Dmitriy')));