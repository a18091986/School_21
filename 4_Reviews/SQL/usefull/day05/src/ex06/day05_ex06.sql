-- Exercise 06: Let’s make performance improvement	
-- Turn-in directory	ex06
-- Files to turn-in	day05_ex06.sql
-- Allowed	
-- Language	ANSI SQL
-- Please take a look at SQL below from a technical perspective (ignore a logical case of that SQL statement) .

-- SELECT
--     m.pizza_name AS pizza_name,
--     max(rating) OVER (PARTITION BY rating ORDER BY rating ROWS BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING) AS k
-- FROM  menu m
-- INNER JOIN pizzeria pz ON m.pizzeria_id = pz.id
-- ORDER BY 1,2;
-- Create a new BTree index with name idx_1 which should improve the “Execution Time” metric of this SQL. Please provide proof (EXPLAIN ANALYZE) that SQL was improved.

-- Hint: this exercise looks like a “brute force” task to find a good covering index therefore before your new test remove idx_1 index.

SET ENABLE_SEQSCAN TO ON;
EXPLAIN ANALYZE
SELECT m.pizza_name AS pizza_name, MAX(rating)
       OVER (PARTITION BY rating ORDER BY rating ROWS BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING) AS k
FROM menu m
         INNER JOIN pizzeria pz ON m.pizzeria_id = pz.id
ORDER BY 1, 2;

-- CREATE INDEX IF NOT EXISTS idx_1 ON menu(pizzeria_id, pizza_name);
-- CREATE INDEX IF NOT EXISTS idx_2 ON pizzeria (rating);
CREATE INDEX IF NOT EXISTS idx_1 ON pizzeria(id, name, rating);


SET ENABLE_SEQSCAN TO OFF;
EXPLAIN ANALYZE
SELECT m.pizza_name AS pizza_name, MAX(rating)
       OVER (PARTITION BY rating ORDER BY rating ROWS BETWEEN UNBOUNDED PRECEDING AND UNBOUNDED FOLLOWING) AS k
FROM menu m
         INNER JOIN pizzeria pz ON m.pizzeria_id = pz.id
ORDER BY 1, 2;

DROP INDEX idx_1;