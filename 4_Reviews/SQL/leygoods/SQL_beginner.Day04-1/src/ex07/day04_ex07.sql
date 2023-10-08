INSERT INTO person_visits(id, person_id, pizzeria_id, visit_date)
values(
(SELECT MAX(id) from person_visits) +1,
(SELECT id from person where name = 'Dmitriy'),
(SELECT DISTINCT pizzeria.id
from pizzeria
 JOIN menu ON pizzeria.id = menu.pizzeria_id
 JOIN mv_dmitriy_visits_and_eats AS mv ON mv.pizzeria_name != pizzeria.name
 WHERE menu.price < 800 LIMIT 1
),
	'2022-01-08'
);
REFRESH MATERIALIZED VIEW mv_dmitriy_visits_and_eats;