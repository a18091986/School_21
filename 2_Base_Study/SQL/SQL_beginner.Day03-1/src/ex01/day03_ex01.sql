-- Exercise 01: Let’s find forgotten menus	
-- Turn-in directory	ex01
-- Files to turn-in	day03_ex01.sql
-- Allowed	
-- Language	ANSI SQL
-- Denied	
-- SQL Syntax Construction	any type of JOINs

-- Please find all menu identifiers which are not ordered by anyone. The result should be sorted by identifiers. The sample of output data is presented below.

select id menu_id from menu
EXCEPT
select menu_id from person_order
order by 1;