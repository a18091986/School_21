-- Exercise 01: How to see that index works?	
-- Turn-in directory	ex01
-- Files to turn-in	day05_ex01.sql
-- Allowed	
-- Language	ANSI SQL
-- Before further steps please write a SQL statement that returns pizzas’ and corresponding pizzeria names. Please take a look at the sample result below (no sort needed).

-- pizza_name	pizzeria_name
-- cheese pizza	Pizza Hut
-- ...	...
-- Let’s provide proof that your indexes are working for your SQL. The sample of proof is the output of the EXPLAIN ANALYZE command. Please take a look at the sample output command.

-- ...
-- ->  Index Scan using idx_menu_pizzeria_id on menu m  (...)
-- ...
-- Hint: please think why your indexes are not working in a direct way and what should we do to enable it?


SET ENABLE_SEQSCAN TO OFF;
-- Включает или отключает использование планировщиком планов последовательного сканирования для текущего запроса.
-- SELECT pizza_name, name FROM menu
-- JOIN pizzeria pz on menu.pizzeria_id = pz.id;

EXPLAIN ANALYZE
SELECT pizza_name, name FROM menu
JOIN pizzeria pz on menu.pizzeria_id = pz.id;

-- Hint: please think why your indexes are not working in a direct way and what should we do to enable it?

-- drop table if exists test_for_index;

-- create table test_for_index as
-- select generate_series(1, 1000, 1), random()*100 as num;

-- create index idx_test_for_index_num on test_for_index (num);

-- EXPLAIN ANALYSE
-- select * from test_for_index where num > 95;

-- EXPLAIN ANALYSE
-- select * from test_for_index where num > 5;

-- индексы не работают вследствие малого объема данных - для выборки с помощью индексов СУБД придётся кроме того, что прочитать страницы, в которых хранятся данные колонок, ещё и страницы, в которых хранятся записи индексов. 

-- https://edu.postgrespro.ru/sqlprimer/sqlprimer-2019-msu-08.pdf page 22

