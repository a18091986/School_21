-- Exercise 01: Find data gaps	
-- Turn-in directory	ex01
-- Files to turn-in	day02_ex01.sql
-- Allowed	
-- Language	ANSI SQL
-- SQL Syntax Construction	generate_series(...)
-- Denied	
-- SQL Syntax Construction	NOT IN, IN, NOT EXISTS, EXISTS, UNION, EXCEPT, INTERSECT

-- Please write a SQL statement which returns the missing days from 1st to 10th of January 2022 (including all days) for visits of persons with identifiers 1 or 2 (it means days missed by both). Please order by visiting days in ascending mode. The sample of data with column name is presented below.

SELECT missing_date::DATE 
FROM 
    generate_series('2022-01-01'::DATE, '2022-01-10', '1 day') AS missing_date
LEFT JOIN
    (SELECT visit_date FROM person_visits WHERE person_id = 1 OR person_id = 2) AS vd
ON 
    missing_date.date = vd.visit_date
WHERE visit_date IS NULL
ORDER BY missing_date;