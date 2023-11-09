-- Exercise 03: Improvements are in a way	
-- Turn-in directory	ex03
-- Files to turn-in	day06_ex03.sql
-- Allowed	
-- Language	SQL, DML, DDL

-- Actually, we have to make improvements to data consistency from one side and performance tuning from the other side. Please create a multicolumn unique index (with name idx_person_discounts_unique) that prevents duplicates of pair values person and pizzeria identifiers.

-- After creation of a new index, please provide any simple SQL statement that shows proof of index usage (by using EXPLAIN ANALYZE). The example of “proof” is below

-- ...
-- Index Scan using idx_person_discounts_unique on person_discounts
-- ...

CREATE UNIQUE INDEX idx_person_discounts_unique ON person_discounts(person_id, pizzeria_id);

SET ENABLE_SEQSCAN = OFF;
EXPLAIN ANALYSE
SELECT * FROM person_discounts WHERE person_id = 1 AND pizzeria_id = 1