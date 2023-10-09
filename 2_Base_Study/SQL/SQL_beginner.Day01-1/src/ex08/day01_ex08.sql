-- Exercise 08 - Migrate JOIN to NATURAL JOIN
-- Exercise 08: Migrate JOIN to NATURAL JOIN	
-- Turn-in directory	ex08
-- Files to turn-in	day01_ex08.sql
-- Allowed	
-- Language	ANSI SQL
-- SQL Syntax Construction	NATURAL JOIN
-- Denied	
-- SQL Syntax Construction	other type of JOINs
-- Please rewrite a SQL statement from exercise #07 by using NATURAL JOIN construction. The result must be the same like for exercise #07.


SELECT
    order_date, CONCAT(name, ' (age:', age, ')') AS person_information 
FROM 
    person_order
NATURAL JOIN
    (SELECT id AS person_id, name, age FROM person) AS p
ORDER BY order_date, name