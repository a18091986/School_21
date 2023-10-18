SET ENABLE_SEQSCAN = OFF;

EXPLAIN ANALYZE SELECT pizza_name, name AS pizzeria_name
FROM pizzeria INNER JOIN menu ON pizzeria.id = menu.pizzeria_id