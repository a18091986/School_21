-- Exercise 10 - Global JOIN
-- Exercise 10: Global JOIN	
-- Turn-in directory	ex10
-- Files to turn-in	day01_ex10.sql
-- Allowed	
-- Language	ANSI SQL

-- Please write a SQL statement which returns a list of the person names which made an order for pizza in the corresponding pizzeria. The sample result (with named columns) is provided below and yes ... please make ordering by 3 columns (person_name, pizza_name, pizzeria_name) in ascending mode.

SELECT person.name AS person_name, pizza_name, pizzeria.name AS pizzeria_name FROM
    person
LEFT JOIN
    person_order
ON person.id = person_order.person_id
LEFT JOIN 
    menu
ON person_order.menu_id = menu.id
LEFT JOIN
    pizzeria
ON menu.pizzeria_id = pizzeria.id
ORDER BY person_name, pizza_name, pizzeria_name;