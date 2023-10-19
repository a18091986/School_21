-- Exercise 06: Let’s automate Primary Key generation	
-- Turn-in directory	ex06
-- Files to turn-in	day06_ex06.sql
-- Allowed	
-- Language	SQL, DML, DDL
-- Denied	
-- SQL Syntax Pattern	Don’t use hard-coded value for amount of rows to set a right value for sequence

-- Let’s create a Database Sequence with the name seq_person_discounts (starting from 1 value) and set a default value for id attribute of person_discounts table to take a value from seq_person_discounts each time automatically. Please be aware that your next sequence number is 1, in this case please set an actual value for database sequence based on formula “amount of rows in person_discounts table” + 1. Otherwise you will get errors about Primary Key violation constraint.

CREATE SEQUENCE seq_person_discounts START 1;

SELECT SETVAL('seq_person_discounts', max(id)) FROM person_discounts;

ALTER TABLE person_discounts ALTER COLUMN id SET DEFAULT NEXTVAL('seq_person_discounts');

