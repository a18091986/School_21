CREATE OR REPLACE FUNCTION fnc_fibonacci(pstop integer default 10) RETURNS TABLE(numbers integer) AS $$
    WITH RECURSIVE r AS (
    -- стартовая часть рекурсии (т.н. "anchor")
    SELECT
        0 AS a,
        1 AS b
    UNION

    -- рекурсивная часть
    SELECT
        b,
        a + b
    FROM r
    WHERE b < pstop
)
SELECT a FROM r;
$$ LANGUAGE SQL;


CREATE OR REPLACE FUNCTION fnc_fibonacci(pstop integer default 10) RETURNS TABLE(numbers integer) AS $$
    WITH RECURSIVE r AS (
    -- стартовая часть рекурсии (т.н. "anchor")
    SELECT
        0 AS a,
        1 AS b
    UNION

    -- рекурсивная часть
    SELECT
        b,
        a + b
    FROM r
    WHERE b < pstop
)
SELECT a FROM r;
$$ LANGUAGE SQL;