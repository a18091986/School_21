-- Exercise 07: Deadlock	
-- Turn-in directory	ex07
-- Files to turn-in	day08_ex07.sql with comments for Session #1, Session #2 statements; screenshot of psql output for Session #1; screenshot of psql output for Session #2
-- Allowed	
-- Language	SQL
-- Please for this task use the command line for PostgreSQL database (psql). You need to check how your changes will be published in the database for other database users.

-- Actually, we need two active sessions (meaning 2 parallel sessions in the command lines).

-- Let’s reproduce a deadlock situation in our database.

-- You can see a graphical presentation of the deadlock situation on a picture. Looks like a “christ-lock” between parallel sessions.	D08_12
-- Please write any SQL statement with any isolation level (you can use default setting) on the pizzeria table to reproduce this deadlock situation.

-- Session #1
BEGIN TRANSACTION;

-- Session #2
BEGIN TRANSACTION;

-- Session #1
UPDATE pizzeria SET rating = 3 WHERE id = 1;

-- Session #2
UPDATE pizzeria SET rating =4 WHERE id = 2;

-- Session #1
UPDATE pizzeria SET rating = 3 WHERE id = 2;

-- Session #2
UPDATE pizzeria SET rating = 4 WHERE id = 1;

-- Session #1
COMMIT;

-- Session #2
COMMIT;