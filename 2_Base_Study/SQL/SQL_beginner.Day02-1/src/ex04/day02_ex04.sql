-- Exercise 04 - Find favourite pizzas
-- Exercise 04: Find favourite pizzas	
-- Turn-in directory	ex04
-- Files to turn-in	day02_ex04.sql
-- Allowed	
-- Language	ANSI SQL

-- Find full information about all possible pizzeria names and prices to get mushroom or pepperoni pizzas. Please sort the result by pizza name and pizzeria name then. The result of sample data is below (please use the same column names in your SQL statement).

SELECT 
    pizza_name, pizzeria.name AS pizzeria_name, price 
FROM 
    (SELECT 
        pizzeria_id, pizza_name, price 
    FROM 
        menu
    WHERE 
        pizza_name IN ('mushroom pizza', 'pepperoni pizza')) pzz
LEFT JOIN
    pizzeria
ON pzz.pizzeria_id = pizzeria.id
ORDER BY pizza_name, pizzeria_name;

SELECT 
    pizza_name, pizzeria.name AS pizzeria_name, price 
FROM 
    (SELECT 
        pizzeria_id, pizza_name, price 
    FROM 
        menu
    WHERE 
        pizza_name IN ('mushroom pizza', 'pepperoni pizza')) pzz
LEFT JOIN
    pizzeria
ON pzz.pizzeria_id = pizzeria.id
ORDER BY pizza_name, pizzeria_name;