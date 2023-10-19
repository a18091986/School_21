-- Exercise 05: Data Governance Rules	
-- Turn-in directory	ex05
-- Files to turn-in	day06_ex05.sql
-- Allowed	
-- Language	SQL, DML, DDL

-- To satisfy Data Governance Policies need to add comments for the table and table's columns. Let’s apply this policy for the person_discounts table. Please add English or Russian comments (it's up to you) that explain what is a business goal of a table and all included attributes.

COMMENT ON TABLE person_discounts is 'table for calc person discounts';
COMMENT ON COLUMN person_discounts.id  is 'identifier for row' ;
COMMENT ON COLUMN person_discounts.person_id  is 'identifier for person' ;
COMMENT ON COLUMN person_discounts.pizzeria_id  is 'identifier for pizzeria';
COMMENT ON COLUMN person_discounts.discount  is 'discount value';

