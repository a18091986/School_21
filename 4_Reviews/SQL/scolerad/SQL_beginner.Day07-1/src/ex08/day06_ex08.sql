SELECT address, pizzeria.name, COUNT(*) AS count_of_orders
FROM person
	INNER JOIN person_order ON person.id = person_order.person_id
	INNER JOIN menu ON menu.id = person_order.menu_id
	INNER JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
GROUP BY pizzeria.name, address
ORDER BY 1, 2;