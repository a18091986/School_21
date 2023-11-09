-- Exercise 06: Phantom Reads for Repeatable Read	
-- Turn-in directory	ex06
-- Files to turn-in	day08_ex06.sql with comments for Session #1, Session #2 statements; screenshot of psql output for Session #1; screenshot of psql output for Session #2
-- Allowed	
-- Language	SQL
-- Please for this task use the command line for PostgreSQL database (psql). You need to check how your changes will be published in the database for other database users.

-- Actually, we need two active sessions (meaning 2 parallel sessions in the command lines).

-- Let’s check one of the famous “Phantom Reads” database pattern but under REPEATABLE READ isolation level. You can see a graphical presentation of that anomaly on a picture. Horizontal Red Line means the final results after all sequential steps for both Sessions.	D08_11
-- Please summarize all ratings for all pizzerias in a transaction mode for both Sessions and after that make UPDATE of rating to 5 value for “Pizza Hut” restaurant in session #2 (in the same order as in the picture).

-- Session #1
BEGIN TRANSACTION ISOLATION LEVEL REPEATABLE READ;

-- Session #2
BEGIN TRANSACTION ISOLATION LEVEL REPEATABLE READ;

-- Session #1
SELECT SUM(rating) FROM pizzeria;

-- Session #2
UPDATE pizzeria SET rating = 5.0 WHERE name = 'Pizza Hut';
COMMIT;

-- Session #1
SELECT SUM(rating) FROM pizzeria;
COMMIT;
SELECT SUM(rating) FROM pizzeria;

-- Session #2
SELECT SUM(rating) FROM pizzeria;