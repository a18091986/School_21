-- Exercise 09: New pizza means new visits	
-- Turn-in directory	ex09
-- Files to turn-in	day03_ex09.sql
-- Allowed	
-- Language	ANSI SQL
-- Denied	
-- SQL Syntax Pattern	Don’t use direct numbers for identifiers of Primary Key and pizzeria

-- Please register new visits into Dominos restaurant from Denis and Irina on 24th of February 2022. Warning: this exercise will probably be the cause of changing data in the wrong way. Actually, you can restore the initial database model with data from the link in the “Rules of the day” section and replay script from Exercises 07 and 08..

INSERT INTO person_visits VALUES
    ((SELECT MAX(id) + 1 FROM person_visits), 
    (SELECT id FROM person WHERE name = 'Denis'),
    (SELECT id FROM pizzeria WHERE name = 'Dominos'),
    '2022-02-24'),

    ((SELECT MAX(id) + 2 FROM person_visits), 
    (SELECT id FROM person WHERE name = 'Irina'),
    (SELECT id FROM pizzeria WHERE name = 'Dominos'),
    '2022-02-24');

-- SELECT * FROM person_visits ORDER BY id DESC LIMIT 3;