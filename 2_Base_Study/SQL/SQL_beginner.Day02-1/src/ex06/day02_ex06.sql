-- Exercise 06: favourite pizzas for Denis and Anna	
-- Turn-in directory	ex06
-- Files to turn-in	day02_ex06.sql
-- Allowed	
-- Language	ANSI SQL

-- Please find all pizza names (and corresponding pizzeria names using menu table) that Denis or Anna ordered. Sort a result by both columns. The sample of output is presented below.

WITH 
    orders_by_users
AS 
    (SELECT menu_id FROM
        person_order 
    LEFT JOIN 
        person 
    ON person_order.person_id = person.id 
    WHERE NAME IN ('Denis', 'Anna')),
    pz_pzz
AS
    (SELECT menu.id as menu_id, pizzeria_id, pizza_name, name as pizzeria_name FROM
        menu
    LEFT JOIN
        pizzeria
    ON menu.pizzeria_id = pizzeria.id)
SELECT 
    pizza_name, pizzeria_name
FROM 
    orders_by_users
LEFT JOIN
    pz_pzz
ON orders_by_users.menu_id = pz_pzz.menu_id
ORDER BY 1,2;