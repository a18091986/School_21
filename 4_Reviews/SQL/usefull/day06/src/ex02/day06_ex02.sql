-- Exercise 02: Let’s recalculate a history of orders	
-- Turn-in directory	ex02
-- Files to turn-in	day06_ex02.sql
-- Allowed	
-- Language	SQL, DML, DDL

-- Please write a SQL statement that returns orders with actual price and price with applied discount for each person in the corresponding pizzeria restaurant and sort by person name, and pizza name. Please take a look at the sample of data below.

-- name	pizza_name	price	discount_price	pizzeria_name
-- Andrey	cheese pizza	800	624	Dominos
-- Andrey	mushroom pizza	1100	858	Dominos
-- ...	...	...	...	...

SELECT 
    person.name, menu.pizza_name, menu.price, ROUND((1 - person_discounts.discount / 100) * price, 2) AS discount_price, pizzeria.name as pizzeria_name 
FROM
    person_order INNER JOIN person ON person_order.person_id = person.id
INNER JOIN
    menu ON person_order.menu_id = menu.id
INNER JOIN
    person_discounts ON person_discounts.person_id = person.id and person_discounts.pizzeria_id = menu.pizzeria_id
INNER JOIN 
    pizzeria ON person_discounts.pizzeria_id = pizzeria.id
ORDER BY name, pizza_name;
