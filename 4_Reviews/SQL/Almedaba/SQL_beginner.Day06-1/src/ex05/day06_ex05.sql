COMMENT ON TABLE person_discounts is 'person discounts ¯\_(ツ)_/¯';
COMMENT ON COLUMN person_discounts.id  is 'identifier' ;
COMMENT ON COLUMN person_discounts.person_id  is 'identifier for person' ;
COMMENT ON COLUMN person_discounts.pizzeria_id  is 'identifier for pizzeria';
COMMENT ON COLUMN person_discounts.discount  is 'discount value';


SELECT count(*) = 5 as check
FROM pg_description
WHERE
    objoid = 'person_discounts' :: regclass