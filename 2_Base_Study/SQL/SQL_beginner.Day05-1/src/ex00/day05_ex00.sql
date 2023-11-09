-- Active: 1698411269832@@46.8.219.63@5432@pizza
-- Exercise 00: Let’s create indexes for every foreign key	
-- Turn-in directory	ex00
-- Files to turn-in	day05_ex00.sql
-- Allowed	
-- Language	ANSI SQL

-- Please create a simple BTree index for every foreign key in our database. The name pattern should satisfy the next rule “idx_{table_name}_{column_name}”. For example, the name BTree index for the pizzeria_id column in the menu table is idx_menu_pizzeria_id.




CREATE INDEX idx_menu_pizzeria_id ON menu USING btree (pizzeria_id); 

-- btree by default

CREATE INDEX idx_person_visits_person_id ON person_visits(person_id);
CREATE INDEX idx_person_visits_pizzeria_id ON person_visits(pizzeria_id);
CREATE INDEX idx_person_order_person_id ON person_order(person_id);
CREATE INDEX idx_person_order_menu_id ON person_order(menu_id);


-- SELECT
--     tablename,
--     indexname,
--     indexdef
-- FROM
--     pg_indexes
-- WHERE
--     schemaname = 'public'
-- ORDER BY
--     tablename,
--     indexname;

-- DROP INDEX idx_menu_pizzeria_id;
-- DROP INDEX idx_person_order_person_id;
-- DROP INDEX idx_person_order_menu_id;
-- DROP INDEX idx_person_visits_person_id;
-- DROP INDEX idx_person_visits_pizzeria_id;