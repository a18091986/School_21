-- Exercise 02: “Store” generated dates in one place	
-- Turn-in directory	ex02
-- Files to turn-in	day04_ex02.sql
-- Allowed	
-- Language	ANSI SQL
-- SQL Syntax Construction	generate_series(...)

-- Please create a Database View (with name v_generated_dates) which should be “store” generated dates from 1st to 31th of January 2022 in DATE type. Don’t forget about order for the generated_date column.

-- generated_date
-- 2022-01-01
-- 2022-01-02
-- ...

CREATE OR REPLACE VIEW v_generated_dates as 
    SELECT generate_series('2022-01-01', '2022-01-31', interval '1 day')::date AS generated_date ORDER BY 1;

-- SELECT * FROM v_generated_dates;
