-- Exercise 09 - IN versus EXISTS
-- Exercise 09: IN versus EXISTS	
-- Turn-in directory	ex09
-- Files to turn-in	day01_ex09.sql
-- Allowed	
-- Language	ANSI SQL

-- Please write 2 SQL statements which return a list of pizzerias names which have not been visited by persons by using IN for 1st one and EXISTS for the 2nd one.

SELECT id FROM pizzeria WHERE id NOT IN (SELECT pizzeria_id FROM person_visits);

SELECT id FROM pizzeria WHERE NOT EXISTS (SELECT pizzeria_id FROM person_visits WHERE pizzeria_id = pizzeria.id);