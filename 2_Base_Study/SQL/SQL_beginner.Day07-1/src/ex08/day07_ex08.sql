-- Exercise 08 - Find pizzeria’s restaurant locations
-- Exercise 08: Find pizzeria’s restaurant locations	
-- Turn-in directory	ex08
-- Files to turn-in	day07_ex08.sql
-- Allowed	
-- Language	ANSI SQL
-- We know about personal addresses from our data. Let’s imagine, that particular person visits pizzerias in his/her city only. Please write a SQL statement that returns address, pizzeria name and amount of persons’ orders. The result should be sorted by address and then by restaurant name. Please take a look at the sample of output data below.

-- address	name	count_of_orders
-- Kazan	Best Pizza	4
-- Kazan	DinoPizza	4
-- ...	...	...

SELECT address, pizzeria.name name, COUNT(*) as count_of_orders
FROM person
JOIN person_order ON person.id = person_order.person_id
JOIN menu ON person_order.menu_id = menu.id
JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
GROUP BY address, pizzeria.name
ORDER BY 1, 2;
