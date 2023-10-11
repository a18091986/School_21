-- Exercise 05 - Investigate Person Data
-- Exercise 05: Investigate Person Data	
-- Turn-in directory	ex05
-- Files to turn-in	day02_ex05.sql
-- Allowed	
-- Language	ANSI SQL

-- Find names of all female persons older than 25 and order the result by name. The sample of output is presented below.

SELECT 
    name 
FROM 
    person 
WHERE 
    gender = 'female' AND age > 25
ORDER BY
    name;