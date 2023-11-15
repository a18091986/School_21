-- Active: 1698411269832@@46.8.219.63@5432@pizza
CREATE TABLE IF NOT EXISTS person_discounts (
    id BIGINT PRIMARY KEY,
    person_id  BIGINT NOT NULL,
    pizzeria_id BIGINT NOT NULL,
    discount NUMERIC,
    CONSTRAINT fk_person_discounts_person_id FOREIGN KEY(person_id) REFERENCES person(id),
    CONSTRAINT fk_person_discounts_pizzeria_id FOREIGN KEY(pizzeria_id) REFERENCES pizzeria(id)
);

select count(*) = 1 as check
from pg_tables
where tablename = 'person_discounts'