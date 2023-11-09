-- Exercise 09: Explicit type transformation	
-- Turn-in directory	ex09
-- Files to turn-in	day07_ex09.sql
-- Allowed	
-- Language	ANSI SQL
-- Please write a SQL statement that returns aggregated information by person’s address , the result of “Maximal Age - (Minimal Age / Maximal Age)” that is presented as a formula column, next one is average age per address and the result of comparison between formula and average columns (other words, if formula is greater than average then True, otherwise False value).

-- The result should be sorted by address column. Please take a look at the sample of output data below.

-- address	formula	average	comparison
-- Kazan	44.71	30.33	true
-- Moscow	20.24	18.5	true
-- ...	...	...	...


SELECT 
    address,
    ROUND(MAX(age) - MIN(age)::NUMERIC / MAX(age), 2) AS formula,
    ROUND(AVG(age), 2) AS average,
    MAX(age) - MIN(age)::NUMERIC / MAX(age) > AVG(age) AS comparison
FROM person
GROUP BY address
ORDER BY address;

