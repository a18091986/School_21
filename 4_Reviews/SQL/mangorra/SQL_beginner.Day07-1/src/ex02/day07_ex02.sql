WITH fav_rest AS ((SELECT pizzeria_id, COUNT(po.id), 'order' AS action_type
		FROM person_order po
		JOIN menu ON menu.id = po.menu_id
		GROUP BY 1
		ORDER BY 2 DESC
		LIMIT 3)
		UNION ALL
		(SELECT pizzeria_id, COUNT(pv.id), 'visit' AS action_type
		FROM person_visits pv
		GROUP BY 1
		ORDER BY 2 DESC
		LIMIT 3))
		
SELECT name, count, action_type
FROM fav_rest fr
JOIN pizzeria pz ON pz.id = fr.pizzeria_id
ORDER BY 3 asc, 2 desc;