-- Exercise 12: New orders are coming!	
-- Turn-in directory	ex12
-- Files to turn-in	day03_ex12.sql
-- Allowed	
-- Language	ANSI SQL
-- SQL Syntax Construction	generate_series(...)
-- SQL Syntax Patten	Please use “insert-select” pattern
-- INSERT INTO ... SELECT ...	
-- Denied	
-- SQL Syntax Patten	- Don’t use direct numbers for identifiers of Primary Key, and menu
-- Don’t use window functions like ROW_NUMBER( )
-- Don’t use atomic INSERT statements |

-- Please register new orders from all persons for “greek pizza” on 25th of February 2022. Warning: this exercise will probably be the cause of changing data in the wrong way. Actually, you can restore the initial database model with data from the link in the “Rules of the day” section and replay script from Exercises 07 , 08 ,09 , 10 and 11.

INSERT INTO person_order(id, person_id, menu_id, order_date)
SELECT (GENERATE_SERIES(((SELECT MAX(id) FROM person_order) + 1),
                        ((SELECT MAX(id) FROM person_order) + (SELECT COUNT(*) FROM person)))),
       (GENERATE_SERIES((SELECT MIN(id) FROM person), (SELECT COUNT(*) FROM person))),
       (SELECT m.id FROM menu m WHERE m.pizza_name = 'greek pizza'),
       '2022-02-25';
--

-- SELECT * FROM person_order ORDER BY id DESC LIMIT (SELECT COUNT(*) FROM person);