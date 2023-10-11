-- Exercise 08: Continuing to research data	
-- Turn-in directory	ex08
-- Files to turn-in	day02_ex08.sql
-- Allowed	
-- Language	ANSI SQL

-- Please find the names of all males from Moscow or Samara cities who orders either pepperoni or mushroom pizzas (or both) . Please order the result by person name in descending mode. The sample of output is presented below.

SELECT DISTINCT name FROM
    (SELECT id, name FROM person WHERE gender = 'male' AND address IN ('Moscow','Samara')) pp
JOIN 
    person_order
ON pp.id = person_order.person_id
JOIN
    (SELECT id FROM menu WHERE pizza_name IN ('pepperoni pizza', 'mushroom pizza')) pz
ON pz.id = person_order.menu_id
ORDER BY name DESC;
