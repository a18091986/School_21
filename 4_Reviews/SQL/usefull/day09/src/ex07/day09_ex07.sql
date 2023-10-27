-- Exercise 07: Different view to find a Minimum	
-- Turn-in directory	ex07
-- Files to turn-in	day09_ex07.sql
-- Allowed	
-- Language	SQL, DDL, DML
-- Please write a SQL or pl/pgsql function func_minimum (it’s up to you) that has an input parameter is an array of numbers and the function should return a minimum value.

-- To check yourself and call a function, you can make a statement like below.

-- SELECT func_minimum(VARIADIC arr => ARRAY[10.0, -1.0, 5.0, 4.4]);

CREATE OR REPLACE FUNCTION
    func_minimum(VARIADIC arr NUMERIC[])
    returns NUMERIC AS
$$
SELECT min($1[i])
FROM generate_subscripts($1, 1) g(i);
$$ LANGUAGE SQL;

SELECT func_minimum(VARIADIC arr => ARRAY [10.0, -1.0, 5.0, 4.4]);
