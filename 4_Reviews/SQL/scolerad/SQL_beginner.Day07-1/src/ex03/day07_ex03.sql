WITH visit AS (
	SELECT pizzeria.name, COUNT(*) AS count, 'visit' AS action_type
	FROM pizzeria INNER JOIN person_visits ON pizzeria.id = person_visits.pizzeria_id
	GROUP BY pizzeria_id, pizzeria.name
	ORDER BY count DESC
),
orders AS (
	SELECT pizzeria.name, COUNT(*) AS count, 'order' AS action_type
	FROM pizzeria
		INNER JOIN menu ON pizzeria.id = menu.pizzeria_id
		INNER JOIN person_order ON menu.id = person_order.menu_id
	GROUP BY pizzeria.name
	ORDER BY count DESC
)
SELECT v.name, v.count + o.count AS total_count
FROM visit v, orders o
WHERE v.name = o.name
ORDER BY total_count DESC, v.name ASC;