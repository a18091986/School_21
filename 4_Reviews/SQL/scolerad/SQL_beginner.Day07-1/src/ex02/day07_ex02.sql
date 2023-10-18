WITH visit AS (
	SELECT pizzeria.name, COUNT(*) AS count, 'visit' AS action_type
	FROM pizzeria INNER JOIN person_visits ON pizzeria.id = person_visits.pizzeria_id
	GROUP BY pizzeria_id, pizzeria.name
	ORDER BY count DESC
	LIMIT 3
),
orders AS (
	SELECT pizzeria.name, COUNT(*) AS count, 'order' AS action_type
	FROM pizzeria
		INNER JOIN menu ON pizzeria.id = menu.pizzeria_id
		INNER JOIN person_order ON menu.id = person_order.menu_id
	GROUP BY pizzeria.name
	ORDER BY count DESC
	LIMIT 3
)
SELECT * FROM visit
UNION ALL
SELECT * FROM orders
ORDER BY action_type, count DESC;