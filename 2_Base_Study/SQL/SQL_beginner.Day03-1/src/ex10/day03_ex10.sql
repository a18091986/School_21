-- Exercise 10: New visits means new orders	
-- Turn-in directory	ex10
-- Files to turn-in	day03_ex10.sql
-- Allowed	
-- Language	ANSI SQL
-- Denied	
-- SQL Syntax Pattern	Don’t use direct numbers for identifiers of Primary Key and pizzeria

-- Please register new orders from Denis and Irina on 24th of February 2022 for the new menu with “sicilian pizza”. Warning: this exercise will probably be the cause of changing data in the wrong way. Actually, you can restore the initial database model with data from the link in the “Rules of the day” section and replay script from Exercises 07 , 08 and 09.

INSERT INTO person_order (id, person_id, menu_id, order_date) VALUES
    ((SELECT MAX(id) + 1 from person_order),
    (SELECT id FROM person WHERE name = 'Denis'),
    (SELECT id FROM menu WHERE pizza_name = 'sicilian pizza'),
    '2022-02-24'),
    ((SELECT MAX(id) + 2 from person_order),
    (SELECT id FROM person WHERE name = 'Irina'),
    (SELECT id FROM menu WHERE pizza_name = 'sicilian pizza'),
    '2022-02-24');

-- SELECT po.id, person.name, menu.pizza_name, po.order_date FROM 
--     (SELECT * FROM person_order ORDER BY id DESC LIMIT 3) po
-- JOIN
--     person
-- ON po.person_id = person.id
-- JOIN
--     menu
-- ON menu.id = po.menu_id
-- ORDER BY po.id