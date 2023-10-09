-- Exercise 07 - Just make a JOIN
-- Exercise 07: Just make a JOIN	
-- Turn-in directory	ex07
-- Files to turn-in	day01_ex07.sql
-- Allowed	
-- Language	ANSI SQL

-- Please write a SQL statement which returns the date of order from the person_order table and corresponding person name (name and age are formatted as in the data sample below) which made an order from the person table. Add a sort by both columns in ascending mode.

select 
    order_date, CONCAT(name, ' (age:', age, ')') AS person_information 
FROM 
    person_order
LEFT JOIN
    person
ON person_order.person_id = person.id
ORDER BY order_date, name
