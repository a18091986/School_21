-- Exercise 02: Duplicates or not duplicates	
-- Turn-in directory	ex02
-- Files to turn-in	day01_ex02.sql
-- Allowed	
-- Language	ANSI SQL
-- Denied	
-- SQL Syntax Construction	DISTINCT, GROUP BY, HAVING, any type of JOINs

-- Please write a SQL statement which returns unique pizza names from the menu table and orders by pizza_name column in descending mode. Please pay attention to the Denied section.


(SELECT pizza_name FROM menu)
union
(SELECT pizza_name FROM menu)
ORDER BY pizza_name DESC;