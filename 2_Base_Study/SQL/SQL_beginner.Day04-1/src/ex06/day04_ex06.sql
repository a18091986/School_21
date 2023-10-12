-- Exercise 06: Materialization from virtualization	
-- Turn-in directory	ex06
-- Files to turn-in	day04_ex06.sql
-- Allowed	
-- Language	ANSI SQL

-- Please create a Materialized View mv_dmitriy_visits_and_eats (with data included) based on SQL statement that finds the name of pizzeria Dmitriy visited on January 8, 2022 and could eat pizzas for less than 800 rubles (this SQL you can find out at Day #02 Exercise #07).

-- To check yourself you can write SQL to Materialized View mv_dmitriy_visits_and_eats and compare results with your previous query.

CREATE MATERIALIZED VIEW mv_dmitriy_visits_and_eats AS
(SELECT
    name
FROM pizzeria 
WHERE id IN 
    (SELECT 
        pizzeria_id FROM menu WHERE price < 800 
    AND 
    pizzeria_id IN 
        (SELECT 
            pizzeria_id FROM person_visits 
        WHERE 
            visit_date = '2022-01-08' AND person_id = 
                (SELECT id FROM person WHERE name = 'Dmitriy'))));

-- SELECT * FROM mv_dmitriy_visits_and_eats;