-- Exercise 03: Restaurants statistics #2	
-- Turn-in directory	ex03
-- Files to turn-in	day07_ex03.sql
-- Allowed	
-- Language	ANSI SQL
-- Please write a SQL statement to see restaurants are grouping by visits and by orders and joined with each other by using restaurant name.
-- You can use internal SQLs from Exercise 02 (restaurants by visits and by orders) without limitations of amount of rows.

-- Additionally, please add the next rules.

-- calculate a sum of orders and visits for corresponding pizzeria (be aware, not all pizzeria keys are presented in both tables).
-- sort results by total_count column in descending mode and by name in ascending mode. Take a look at the data sample below.
-- name	total_count
-- Dominos	13
-- DinoPizza	9
-- ...	...

WITH 
    orders AS 
        (SELECT name, COUNT(*) AS count
         FROM pizzeria
         JOIN menu
         ON pizzeria.id = menu.pizzeria_id
         JOIN person_order
         ON person_order.menu_id = menu.id
         GROUP BY name
         ORDER BY count DESC),
    visits AS 
        (SELECT name, COUNT(*) AS count
        FROM pizzeria
        JOIN person_visits
        ON person_visits.pizzeria_id = pizzeria.id
        GROUP BY name
        ORDER BY count DESC)
SELECT pizzeria.name, 
       COALESCE(orders.count, 0) + COALESCE(visits.count, 0) as total_count
FROM pizzeria
LEFT JOIN visits
ON pizzeria.name = visits.name
LEFT JOIN orders
ON pizzeria.name = orders.name
ORDER BY total_count DESC, name;
