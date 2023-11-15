CREATE UNIQUE INDEX idx_person_discounts_unique 
  ON person_discounts(person_id, pizzeria_id);

SET ENABLE_SEQSCAN = OFF;

EXPLAIN ANALYSE
SELECT * FROM person_discounts WHERE person_id = 2 AND pizzeria_id = 2;


select
    column_default :: integer = 0 as check
from
    information_schema.columns
where
    column_name = 'discount'
    and table_name = 'person_discounts'