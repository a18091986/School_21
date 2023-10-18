WITH ord AS (
	SELECT p.person_id, m.pizzeria_id,
	CASE
		WHEN (COUNT(m.pizzeria_id) = 1) THEN 10.5
		WHEN (COUNT(m.pizzeria_id) = 2) THEN 22
		ELSE 30
	END AS discount
	FROM person_order p INNER JOIN menu m ON p.menu_id = m.id
	GROUP BY person_id, pizzeria_id
	ORDER  BY 1
)
INSERT INTO person_discounts (id, person_id, pizzeria_id, discount)
SELECT ROW_NUMBER() OVER() AS id,
	person_id,
	pizzeria_id,
	discount
FROM ord;