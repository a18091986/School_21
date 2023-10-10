-- Exercise 00: Move to the LEFT, move to the RIGHT	
-- Turn-in directory	ex00
-- Files to turn-in	day02_ex00.sql
-- Allowed	
-- Language	ANSI SQL
-- Denied	
-- SQL Syntax Construction	NOT IN, IN, NOT EXISTS, EXISTS, UNION, EXCEPT, INTERSECT

-- Please write a SQL statement which returns a list of pizzerias names with corresponding rating value which have not been visited by persons.

SELECT name, rating FROM 
    pizzeria
LEFT JOIN
    person_visits
on pizzeria.id = person_visits.pizzeria_id
WHERE visit_date IS NULL;