-- Exercise 09: Who loves cheese and pepperoni?	
-- Turn-in directory	ex09
-- Files to turn-in	day02_ex09.sql
-- Allowed	
-- Language	ANSI SQL

-- Please find the names of all females who ordered both pepperoni and cheese pizzas (at any time and in any pizzerias). Make sure that the result is ordered by person name. The sample of data is presented below.


SELECT DISTINCT name FROM
    (SELECT id, name FROM person WHERE gender = 'female') pp
JOIN 
    person_order
ON pp.id = person_order.person_id
JOIN
    (SELECT id FROM menu WHERE pizza_name = 'pepperoni pizza') pz
ON pz.id = person_order.menu_id

INTERSECT

SELECT DISTINCT name FROM
    (SELECT id, name FROM person WHERE gender = 'female') pp
JOIN 
    person_order
ON pp.id = person_order.person_id
JOIN
    (SELECT id FROM menu WHERE pizza_name = 'cheese pizza') pz
ON pz.id = person_order.menu_id
ORDER BY name;