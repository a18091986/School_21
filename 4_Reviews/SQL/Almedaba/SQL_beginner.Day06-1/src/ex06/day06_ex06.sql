CREATE SEQUENCE seq_person_discounts START WITH 1 INCREMENT BY 1;

SELECT SETVAL('seq_person_discounts', (SELECT max(id) FROM person_discounts));

ALTER TABLE person_discounts ALTER COLUMN id SET DEFAULT NEXTVAL('seq_person_discounts');

select
    count(*) = 1 as check1,
    max("start_value") = 1 as check2,
    max("last_value") > 5 as check3
from pg_sequences
where sequencename = 'seq_person_discounts'