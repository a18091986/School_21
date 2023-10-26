
-- Exercise 06: Restaurant metrics	
-- Turn-in directory	ex06
-- Files to turn-in	day07_ex06.sql
-- Allowed	
-- Language	ANSI SQL
-- Please write a SQL statement that returns the amount of orders, average of price, maximum and minimum prices for sold pizza by corresponding pizzeria restaurant. The result should be sorted by pizzeria name. Please take a look at the data sample below. Round your average price to 2 floating numbers.

-- name	count_of_orders	average_price	max_price	min_price
-- Best Pizza	5	780	850	700
-- DinoPizza	5	880	1000	800
-- ...	...	...	...	...

SELECT
    name, COUNT(*) AS count_of_orders, 
    ROUND(AVG(price), 2), 
    MAX(price) as max_price, MIN(price) as min_price
FROM
    pizzeria
JOIN
    menu
ON pizzeria.id = menu.pizzeria_id
JOIN
    person_order
ON person_order.menu_id = menu.id
GROUP BY name
ORDER BY name