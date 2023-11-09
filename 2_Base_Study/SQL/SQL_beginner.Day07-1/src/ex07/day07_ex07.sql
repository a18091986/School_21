-- Exercise 07: Average global rating	
-- Turn-in directory	ex07
-- Files to turn-in	day07_ex07.sql
-- Allowed	
-- Language	ANSI SQL
-- Please write a SQL statement that returns a common average rating (the output attribute name is global_rating) for all restaurants. Round your average rating to 4 floating numbers.


SELECT ROUND(AVG(rating), 4) global_rating FROM pizzeria;