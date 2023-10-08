WITH pizza_1 AS (SELECT pizza_name,	pizzeria.name AS pizzeria_name_1, price
				FROM menu
				JOIN pizzeria ON pizzeria.id = menu.pizzeria_id),
pizza_2 AS (SELECT pizza_name,	pizzeria.name AS pizzeria_name_2, price
				FROM menu
				JOIN pizzeria ON pizzeria.id = menu.pizzeria_id)
SELECT pizza_1.pizza_name,
	pizza_1.pizzeria_name_1,
	pizza_2.pizzeria_name_2,
	pizza_1.price
FROM pizza_1, pizza_2
WHERE pizza_1.pizza_name = pizza_2.pizza_name
	AND pizza_1.pizzeria_name_1 != pizza_2.pizzeria_name_2
	AND pizza_1.price = pizza_2.price
	AND pizza_1.pizzeria_name_1 < pizza_2.pizzeria_name_2
ORDER BY 1;