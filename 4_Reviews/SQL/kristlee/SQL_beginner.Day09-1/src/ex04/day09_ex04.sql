CREATE FUNCTION fnc_persons_female()
RETURNS TABLE (id bigint,
  name varchar,
  age integer,
  gender varchar,
  address varchar
) AS $$  SELECT id, name, age, gender, address
FROM person
WHERE gender = 'female';
$$ LANGUAGE SQL;


SELECT * from fnc_persons_female();

CREATE FUNCTION fnc_persons_male()
RETURNS TABLE (id bigint,
  name varchar,
  age integer,
  gender varchar,
  address varchar
) AS $$  SELECT id, name, age, gender, address
FROM person
WHERE gender = 'male';
$$ LANGUAGE SQL;


SELECT * from fnc_persons_male();
