CREATE FUNCTION func_minimum(VARIADIC arr numeric[]) RETURNS numeric AS $$
    SELECT min(value) FROM unnest($1) AS value;
$$ LANGUAGE SQL;
