
-- Exercise 01: Lost Update Anomaly	
-- Turn-in directory	ex01
-- Files to turn-in	day08_ex01.sql with comments for Session #1, Session #2 statements; screenshot of psql output for Session #1; screenshot of psql output for Session #2
-- Allowed	
-- Language	SQL
-- Please for this task use the command line for PostgreSQL database (psql). You need to check how your changes will be published in the database for other database users.

-- Actually, we need two active sessions (meaning 2 parallel sessions in the command lines).

-- Before a task, make sure you are at a default isolation level in your database. Just run the next statement

-- SHOW TRANSACTION ISOLATION LEVEL;

-- and the result should be “read committed”;

-- If not, then please set “read committed” isolation level explicitly on a session level.

-- Let’s check one of the famous “Lost Update Anomaly” database pattern. You can see a graphical presentation of that anomaly on a picture. Horizontal Red Line means the final results after all sequential steps for both Sessions.	D08_06
-- Please check a rating for “Pizza Hut” in a transaction mode for both Sessions and after that make UPDATE of rating to 4 value in session #1 and make UPDATE of rating to 3.6 value in session #2 (in the same order as in the picture).

-- Session #1
BEGIN TRANSACTION;

-- Session #2
BEGIN TRANSACTION;

-- Session #1
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';

-- Session #2
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';

-- Session #1
UPDATE pizzeria SET rating = 4 WHERE name = 'Pizza Hut';

-- Session #2
UPDATE pizzeria SET rating = 3.6 WHERE name = 'Pizza Hut';

-- Session #1
COMMIT;

-- Session #2
COMMIT;

-- Session #1
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';

-- Session #2
SELECT * FROM pizzeria WHERE name = 'Pizza Hut';