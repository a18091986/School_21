-- Exercise 02: FULL means ‘completely filled’	
-- Turn-in directory	ex02
-- Files to turn-in	day02_ex02.sql
-- Allowed	
-- Language	ANSI SQL
-- Denied	
-- SQL Syntax Construction	NOT IN, IN, NOT EXISTS, EXISTS, UNION, EXCEPT, INTERSECT

-- Please write a SQL statement that returns a whole list of person names visited (or not visited) pizzerias during the period from 1st to 3rd of January 2022 from one side and the whole list of pizzeria names which have been visited (or not visited) from the other side. The data sample with needed column names is presented below. Please pay attention to the substitution value ‘-’ for NULL values in person_name and pizzeria_name columns. Please also add ordering for all 3 columns.

SELECT
    COALESCE(person.name, '-') AS person_name,
    visit_date,
    COALESCE(pizzeria.name, '-') AS pizzeria_name
FROM
    (SELECT * from person_visits WHERE visit_date BETWEEN '2022-01-01' AND '2022-01-03') pv
FULL JOIN
    person
ON person.id = pv.person_id
FULL JOIN
    pizzeria
ON pizzeria.id = pv.pizzeria_id
ORDER BY person_name, visit_date, pizzeria_name

