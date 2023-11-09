
-- Exercise 03: Non-Repeatable Reads Anomaly	
-- Turn-in directory	ex03
-- Files to turn-in	day08_ex03.sql with comments for Session #1, Session #2 statements; screenshot of psql output for Session #1; screenshot of psql output for Session #2
-- Allowed	
-- Language	SQL
-- Please for this task use the command line for PostgreSQL database (psql). You need to check how your changes will be published in the database for other database users.

-- Actually, we need two active sessions (meaning 2 parallel sessions in the command lines).

-- Let’s check one of the famous “Non-Repeatable Reads” database pattern but under READ COMMITTED isolation level. You can see a graphical presentation of that anomaly on a picture. Horizontal Red Line means the final results after all sequential steps for both Sessions.	D08_08
-- Please check a rating for “Pizza Hut” in a transaction mode for both Sessions and after that make UPDATE of rating to 3.6 value in session #2 (in the same order as in the picture).

-- Session #1
BEGIN TRANSACTION ISOLATION LEVEL READ COMMITTED;

-- Session #2
BEGIN TRANSACTION ISOLATION LEVEL READ COMMITTED;

-- Session #1
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';

-- Session #2
UPDATE pizzeria SET rating = 3.6 WHERE name = 'Pizza Hut';
COMMIT;

-- Session #1
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';
COMMIT;
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';

-- Session #2
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';