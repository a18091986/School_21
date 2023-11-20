CREATE OR REPLACE FUNCTION fnc_persons_female()
RETURNS TABLE (
    id INT,
    name VARCHAR,
    age INT,
    gender VARCHAR,
    address VARCHAR
) AS $$
SELECT id, name, age, gender, address
FROM person
WHERE gender = 'female';
$$ LANGUAGE SQL;

CREATE OR REPLACE FUNCTION fnc_persons_male()
RETURNS TABLE (
    id INT,
    name VARCHAR,
    age INT,
    gender VARCHAR,
    address VARCHAR
) AS $$
SELECT id, name, age, gender, address
FROM person
WHERE gender = 'male';
$$ LANGUAGE SQL;

SELECT * FROM fnc_persons_female();
SELECT * FROM fnc_persons_male();