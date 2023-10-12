-- Exercise 01: From parts to common view	
-- Turn-in directory	ex01
-- Files to turn-in	day04_ex01.sql
-- Allowed	
-- Language	ANSI SQL

-- Please use 2 Database Views from Exercise #00 and write SQL to get female and male person names in one list. Please set the order by person name. The sample of data is presented below.

-- name
-- Andrey
-- Anna
-- ...

SELECT name FROM v_persons_female
UNION
SELECT name FROM v_persons_male
ORDER BY name;

