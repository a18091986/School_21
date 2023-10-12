-- Exercise 00: Let’s create separated views for persons	
-- Turn-in directory	ex00
-- Files to turn-in	day04_ex00.sql
-- Allowed	
-- Language	ANSI SQL

-- Please create 2 Database Views (with similar attributes like the original table) based on simple filtering of gender of persons. Set the corresponding names for the database views: v_persons_female and v_persons_male.


CREATE OR REPLACE VIEW v_persons_female as 
    (SELECT * FROM person WHERE gender = 'female');

CREATE OR REPLACE VIEW v_persons_male as 
    (SELECT * FROM person WHERE gender = 'male');

-- SELECT * FROM v_persons_female;
-- SELECT * FROM v_persons_male;

