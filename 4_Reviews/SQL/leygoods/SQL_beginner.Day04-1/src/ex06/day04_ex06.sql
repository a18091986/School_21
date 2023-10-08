CREATE MATERIALIZED VIEW mv_dmitriy_visits_and_eats AS(
SELECT pizzeria.name as pizzeria_name
	from person_visits
JOIN person on person_visits.person_id = person.id
JOIN menu ON person_visits.pizzeria_id = menu.pizzeria_id
JOIN pizzeria on menu.pizzeria_id = pizzeria.id
where person.name = 'Dmitriy' and visit_date = '2022-01-08' AND price < 800
)