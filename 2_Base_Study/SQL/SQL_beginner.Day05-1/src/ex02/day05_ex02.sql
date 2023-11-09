-- Exercise 02: Formula is in the index. Is it Ok?	
-- Turn-in directory	ex02
-- Files to turn-in	day05_ex02.sql
-- Allowed	
-- Language	ANSI SQL
-- Please create a functional B-Tree index with name idx_person_name for the column name of the person table. Index should contain person names in upper case.

-- Please write and provide any SQL with proof (EXPLAIN ANALYZE) that index idx_person_name is working.

CREATE INDEX idx_person_name ON person ((UPPER(name)));

SET ENABLE_SEQSCAN TO OFF;

EXPLAIN ANALYZE
SELECT *
FROM person p
WHERE UPPER(p.name) = 'DENIS';