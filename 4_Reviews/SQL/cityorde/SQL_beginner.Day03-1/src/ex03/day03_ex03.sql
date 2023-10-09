WITH my_cte AS (SELECT pizzeria.name AS name, person.gender AS gender
				   FROM person_order
				   JOIN person ON person.id = person_order.person_id
				   JOIN menu ON menu.id = person_order.menu_id
				   JOIN pizzeria ON pizzeria.id = menu.pizzeria_id)
(SELECT my_cte.name AS pizzeria_name
FROM my_cte
WHERE my_cte.gender = 'female'
EXCEPT ALL
SELECT my_cte.name AS pizzeria_name
FROM my_cte
WHERE my_cte.gender = 'male') 

UNION

(SELECT my_cte.name AS pizzeria_name
FROM my_cte
WHERE my_cte.gender = 'male'
EXCEPT ALL
SELECT my_cte.name AS pizzeria_name
FROM my_cte
WHERE my_cte.gender = 'female')

ORDER BY 1;