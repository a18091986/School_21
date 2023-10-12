-- Exercise 02: Let’s find forgotten pizza and pizzerias	
-- Turn-in directory	ex02
-- Files to turn-in	day03_ex02.sql
-- Allowed	
-- Language	ANSI SQL

-- Please use SQL statement from Exercise #01 and show pizza names from pizzeria which are not ordered by anyone, including corresponding prices also. The result should be sorted by pizza name and price. The sample of output data is presented below.

SELECT pizza_name, price, name pizzeria_name FROM
(SELECT id menu_id FROM menu
EXCEPT
SELECT menu_id FROM person_order) pz_id
JOIN
    menu 
ON menu.id = pz_id.menu_id
JOIN
    pizzeria
ON pizzeria.id = menu.pizzeria_id
ORDER BY pizza_name, price;