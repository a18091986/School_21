-- Exercise 04: Uniqueness for data	
-- Turn-in directory	ex04
-- Files to turn-in	day05_ex04.sql
-- Allowed	
-- Language	ANSI SQL
-- Please create a unique BTree index with the name idx_menu_unique on the menu table for pizzeria_id and pizza_name columns. Please write and provide any SQL with proof (EXPLAIN ANALYZE) that index idx_menu_unique is working.

CREATE UNIQUE INDEX idx_menu_unique ON menu (pizzeria_id, pizza_name);

SET ENABLE_SEQSCAN TO OFF;

EXPLAIN ANALYZE
SELECT *
FROM menu
WHERE menu.pizzeria_id = 1
  AND menu.pizza_name = 'cheese pizza';