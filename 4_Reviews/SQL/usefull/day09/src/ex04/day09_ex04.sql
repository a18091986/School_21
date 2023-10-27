-- Exercise 04: Database View VS Database Function	
-- Turn-in directory	ex04
-- Files to turn-in	day09_ex04.sql
-- Allowed	
-- Language	SQL, DDL, DML
-- As you remember, we created 2 database views to separate data from the person tables by gender attribute. Please define 2 SQL-functions (please be aware, not pl/pgsql-functions) with names

-- fnc_persons_female (should return female persons)
-- fnc_persons_male (should return male persons)
-- To check yourself and call a function, you can make a statement like below (amazing! you can work with a function like with a virtual table!).

-- SELECT *
-- FROM fnc_persons_male();

-- SELECT *
-- FROM fnc_persons_female();

CREATE OR REPLACE FUNCTION fnc_persons_female()
    RETURNS table
            (
                id      bigint,
                name    varchar,
                age     int,
                gender  varchar,
                address varchar
            ) AS
$$
SELECT * FROM person WHERE gender = 'female';
$$ LANGUAGE SQL;
CREATE OR REPLACE FUNCTION fnc_persons_male()
    RETURNS table
            (
                id      bigint,
                name    varchar,
                age     int,
                gender  varchar,
                address varchar
            ) AS
$$
SELECT * FROM person WHERE gender = 'male';
$$ LANGUAGE SQL;

SELECT * FROM fnc_persons_female();
SELECT * FROM fnc_persons_male();
