CREATE OR REPLACE FUNCTION fnc_persons_female()
    RETURNS TABLE (id integer,
                   name varchar,
                   age integer,
                   gender varchar,
                   address varchar) AS $$
        SELECT id, name, age, gender, address
        FROM person
        WHERE gender = 'female';
$$ LANGUAGE SQL;

CREATE OR REPLACE FUNCTION fnc_persons_male()
    RETURNS TABLE (id integer,
                   name varchar,
                   age integer,
                   gender varchar,
                   address varchar) AS $$
        SELECT id, name, age, gender, address
        FROM person
        WHERE gender = 'male';
$$ LANGUAGE SQL;

SELECT *
FROM fnc_persons_male();

SELECT *
FROM fnc_persons_female();

