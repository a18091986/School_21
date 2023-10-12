-- Exercise 03: Find missing visit days with Database View	
-- Turn-in directory	ex03
-- Files to turn-in	day04_ex03.sql
-- Allowed	
-- Language	ANSI SQL

-- Please write a SQL statement which returns missing days for persons’ visits in January of 2022. Use v_generated_dates view for that task and sort the result by missing_date column. The sample of data is presented below.

-- missing_date
-- 2022-01-11
-- 2022-01-12
-- ...

WITH 
    all_days AS
        (SELECT * FROM v_generated_dates),
    visited_days AS
        (SELECT visit_date FROM person_visits)
SELECT generated_date as missing_date FROM all_days
EXCEPT
SELECT * FROM visited_days
ORDER BY 1;