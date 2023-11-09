-- Active: 1698411269832@@46.8.219.63@5432@pizza
-- Exercise 01: Let’s see real names	
-- Turn-in directory	ex01
-- Files to turn-in	day07_ex01.sql
-- Allowed	
-- Language	ANSI SQL

-- Please change a SQL statement from Exercise 00 and return a person name (not identifier). Additional clause is we need to see only top-4 persons with maximal visits in any pizzerias and sorted by a person name. Please take a look at the example of output data below.

-- name	count_of_visits
-- Dmitriy	4
-- Denis	3
-- ...	...

SELECT name, COUNT(*) AS count_of_visits
FROM 
    person_visits
JOIN
    person
on person.id = person_visits.person_id
GROUP BY name
ORDER BY count_of_visits DESC, name
LIMIT 4;
