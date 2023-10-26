-- Exercise 05: Person's uniqueness	
-- Turn-in directory	ex05
-- Files to turn-in	day07_ex05.sql
-- Allowed	
-- Language	ANSI SQL
-- Denied	
-- Syntax construction	GROUP BY, any type (UNION,...) working with sets
-- Please write a simple SQL query that returns a list of unique person names who made orders in any pizzerias. The result should be sorted by person name. Please take a look at the sample below.

-- name
-- Andrey
-- Anna
-- ...


SELECT DISTINCT name FROM
    person
JOIN
    person_order
ON person.id = person_order.person_id
ORDER BY name;
