-- Exercise 03: Reformat to CTE	
-- Turn-in directory	ex03
-- Files to turn-in	day02_ex03.sql
-- Allowed	
-- Language	ANSI SQL
-- SQL Syntax Construction	generate_series(...)
-- Denied	
-- SQL Syntax Construction	NOT IN, IN, NOT EXISTS, EXISTS, UNION, EXCEPT, INTERSECT

-- Let’s return back to Exercise #01, please rewrite your SQL by using the CTE (Common Table Expression) pattern. Please move into the CTE part of your "day generator". The result should be similar like in Exercise #01

WITH md AS (SELECT generate_series('2022-01-01'::DATE, '2022-01-10', '1 day') AS missing_date)
SELECT 
    missing_date::DATE
FROM
    md
LEFT JOIN
    (SELECT visit_date FROM person_visits WHERE person_id = 1 OR person_id = 2) AS vd
ON md.missing_date = vd.visit_date
WHERE visit_date IS NULL
ORDER BY missing_date;