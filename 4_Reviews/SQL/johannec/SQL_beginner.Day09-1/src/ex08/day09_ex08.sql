CREATE OR REPLACE FUNCTION fnc_fibonacci(pstop INT DEFAULT 10)
RETURNS TABLE (fib_number INT) AS $$
DECLARE
    a INT := 0;
    b INT := 1;
BEGIN
    WHILE a < pstop LOOP
        fib_number := a;
        a := b;
        b := fib_number + a;
        RETURN NEXT;
    END LOOP;
END;
$$ LANGUAGE plpgsql;

SELECT * FROM fnc_fibonacci(100);
SELECT * FROM fnc_fibonacci(20);