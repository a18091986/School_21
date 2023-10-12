-- Exercise 06: Find price-similarity pizzas	
-- Turn-in directory	ex06
-- Files to turn-in	day03_ex06.sql
-- Allowed	
-- Language	ANSI SQL

-- Please find the same pizza names who have the same price, but from different pizzerias. Make sure that the result is ordered by pizza name. The sample of data is presented below. Please make sure your column names are corresponding column names below.

WITH 
    info_about_pizza AS
        (SELECT menu.id, pizza_name, pizzeria.name AS pizzeria_name, price FROM
            menu
        JOIN
            pizzeria
        ON menu.pizzeria_id = pizzeria.id)
SELECT iap1.pizza_name, iap1.pizzeria_name, iap2.pizzeria_name, iap1.price FROM 
    info_about_pizza iap1
JOIN
    info_about_pizza iap2
ON iap1.pizza_name = iap2.pizza_name
WHERE iap1.id > iap2.id AND iap1.price = iap2.price;