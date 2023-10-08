-- Exercise 03: “Hidden” Insights	
-- Turn-in directory	ex03
-- Files to turn-in	day01_ex03.sql
-- Allowed	
-- Language	ANSI SQL
-- Denied	
-- SQL Syntax Construction	any type of JOINs

-- Please write a SQL statement which returns common rows for attributes order_date, person_id from person_order table from one side and visit_date, person_id from person_visits table from the other side (please see a sample below). In other words, let’s find identifiers of persons, who visited and ordered some pizza on the same day. Actually, please add ordering by action_date in ascending mode and then by person_id in descending mode.

(SELECT order_date as action_date, person_id FROM person_order)
INTERSECT
(SELECT visit_date, person_id FROM person_visits)
ORDER BY action_date ASC, person_id DESC;