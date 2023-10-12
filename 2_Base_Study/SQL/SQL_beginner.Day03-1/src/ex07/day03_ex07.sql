-- Exercise 07: Let’s cook a new type of pizza	
-- Turn-in directory	ex07
-- Files to turn-in	day03_ex07.sql
-- Allowed	
-- Language	ANSI SQL

-- Please register a new pizza with name “greek pizza” (use id = 19) with price 800 rubles in “Dominos” restaurant (pizzeria_id = 2). Warning: this exercise will probably be the cause of changing data in the wrong way. Actually, you can restore the initial database model with data from the link in the “Rules of the day” section.

INSERT INTO menu VALUES (19, 2, 'greek pizza', 800);

-- SELECT * FROM menu WHERE pizza_name = 'greek pizza';

