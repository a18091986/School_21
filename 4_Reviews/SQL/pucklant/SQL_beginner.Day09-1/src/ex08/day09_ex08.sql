CREATE OR REPLACE FUNCTION fnc_fibonacci(pstop integer DEFAULT 10)
    RETURNS SETOF INTEGER
    LANGUAGE SQL
AS $$
WITH RECURSIVE fib(a,b) AS (
    VALUES(0,1)
    UNION ALL
    SELECT greatest(a,b), a + b AS a FROM fib
    WHERE b < $1
)
SELECT a FROM fib;
$$;

select * from fnc_fibonacci(100);
select * from fnc_fibonacci();

