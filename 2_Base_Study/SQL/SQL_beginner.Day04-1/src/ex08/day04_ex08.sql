-- Exercise 08: Just clear our database	
-- Turn-in directory	ex08
-- Files to turn-in	day04_ex08.sql
-- Allowed	
-- Language	ANSI SQL

-- After all our exercises were born a few Virtual Tables and one Materialized View. Let’s drop them!

-- SELECT * FROM PG_CLASS where relname in 
--     ('v_generated_dates',
--     'v_persons_female',
--     'v_persons_male',
--     'v_price_with_discount',
--     'v_symmetric_union',
--     'mv_dmitriy_visits_and_eats');

DROP VIEW IF EXISTS v_generated_dates,
    v_persons_female,
    v_persons_male,
    v_price_with_discount,
    v_symmetric_union;

DROP MATERIALIZED VIEW IF EXISTS mv_dmitriy_visits_and_eats;

-- SELECT * FROM PG_CLASS where relname in 
--     ('v_generated_dates',
--     'v_persons_female',
--     'v_persons_male',
--     'v_price_with_discount',
--     'v_symmetric_union',
--     'mv_dmitriy_visits_and_eats');