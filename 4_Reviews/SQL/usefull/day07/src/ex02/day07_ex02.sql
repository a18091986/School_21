-- Exercise 02: Restaurants statistics	
-- Turn-in directory	ex02
-- Files to turn-in	day07_ex02.sql
-- Allowed	
-- Language	ANSI SQL

-- Please write a SQL statement to see 3 favorite restaurants by visits and by orders in one list (please add an action_type column with values ‘order’ or ‘visit’, it depends on data from the corresponding table). Please take a look at the sample of data below. The result should be sorted by action_type column in ascending mode and by count column in descending mode.

-- name	count	action_type
-- Dominos	6	order
-- ...	...	...
-- Dominos	7	visit
-- ...	...	...

(SELECT name, COUNT(*) AS count, 'order' AS action_type
FROM pizzeria
JOIN menu
ON pizzeria.id = menu.pizzeria_id
JOIN person_order
ON person_order.menu_id = menu.id
GROUP BY name
ORDER BY count DESC
LIMIT 3)
UNION 
(SELECT name, COUNT(*) AS count, 'visit' AS action_type
FROM pizzeria
JOIN person_visits
ON person_visits.pizzeria_id = pizzeria.id
GROUP BY name
ORDER BY count DESC
LIMIT 3)
ORDER BY action_type, count DESC;