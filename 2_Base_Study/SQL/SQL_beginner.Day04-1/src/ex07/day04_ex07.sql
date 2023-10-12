-- Exercise 07: Refresh our state	
-- Turn-in directory	ex07
-- Files to turn-in	day04_ex07.sql
-- Allowed	
-- Language	ANSI SQL
-- Denied	
-- SQL Syntax Pattern	Don’t use direct numbers for identifiers of Primary Key, person and pizzeria

-- Let's refresh data in our Materialized View mv_dmitriy_visits_and_eats from exercise #06. Before this action, please generate one more Dmitriy visit that satisfies the SQL clause of Materialized View except pizzeria that we can see in a result from exercise #06. After adding a new visit please refresh a state of data for mv_dmitriy_visits_and_eats.

INSERT INTO person_visits VALUES
  ((SELECT MAX(id) + 1 FROM person_visits), 
   (SELECT id FROM person WHERE name = 'Dmitriy'),
   (SELECT id FROM pizzeria WHERE name = 'Best Pizza'), 
   '2022-01-08');

REFRESH MATERIALIZED VIEW mv_dmitriy_visits_and_eats;

-- SELECT * FROM mv_dmitriy_visits_and_eats;