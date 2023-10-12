-- Exercise 08: Let’s cook a new type of pizza with more dynamics	
-- Turn-in directory	ex08
-- Files to turn-in	day03_ex08.sql
-- Allowed	
-- Language	ANSI SQL
-- Denied	
-- SQL Syntax Pattern	Don’t use direct numbers for identifiers of Primary Key and pizzeria

-- Please register a new pizza with name “sicilian pizza” (whose id should be calculated by formula is “maximum id value + 1”) with a price of 900 rubles in “Dominos” restaurant (please use internal query to get identifier of pizzeria). Warning: this exercise will probably be the cause of changing data in the wrong way. Actually, you can restore the initial database model with data from the link in the “Rules of the day” section and replay script from Exercise 07.

INSERT INTO menu VALUES
    ((SELECT MAX(id) + 1 FROM menu), 
    (SELECT id FROM pizzeria WHERE name = 'Dominos'),
    'sicilian pizza',
    900);
-- SELECT * FROM menu WHERE pizza_name = 'sicilian pizza';