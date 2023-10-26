
-- Exercise 04: Clause for groups	
-- Turn-in directory	ex04
-- Files to turn-in	day07_ex04.sql
-- Allowed	
-- Language	ANSI SQL
-- Denied	
-- Syntax construction	WHERE
-- Please write a SQL statement that returns the person name and corresponding number of visits in any pizzerias if the person has visited more than 3 times (> 3).Please take a look at the sample of data below.

-- name	count_of_visits
-- Dmitriy	4

SELECT name, COUNT(*) AS count_of_visits
FROM person
JOIN person_visits
ON person.id = person_visits.person_id
GROUP BY name
HAVING COUNT(*) > 3;
