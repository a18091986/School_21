DROP FUNCTION fnc_persons_female;
DROP FUNCTION fnc_persons_male;

CREATE FUNCTION fnc_persons(pgender varchar default 'female')
RETURNS TABLE (id bigint,
  name varchar,
  age integer,
  gender varchar,
  address varchar
) AS $$  SELECT id, name, age, gender, address
FROM person
WHERE gender = pgender;
$$ LANGUAGE SQL;
