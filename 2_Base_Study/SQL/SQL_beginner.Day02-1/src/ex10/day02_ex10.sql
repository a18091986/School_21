-- Exercise 10: Find persons from one city	
-- Turn-in directory	ex10
-- Files to turn-in	day02_ex10.sql
-- Allowed	
-- Language	ANSI SQL

-- Please find the names of persons who live on the same address. Make sure that the result is ordered by 1st person, 2nd person's name and common address. The data sample is presented below. Please make sure your column names are corresponding column names below.

SELECT p1.name AS person_name1, p2.name AS person_name2, p1.address AS common_address
FROM 
person p1
JOIN
person p2
ON p1.address = p2.address
WHERE p1.id > p2.id
ORDER BY 1, 2, 3