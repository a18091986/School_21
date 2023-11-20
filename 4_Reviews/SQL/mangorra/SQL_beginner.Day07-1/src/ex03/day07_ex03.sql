WITH rest_ord AS (SELECT pizzeria_id, COUNT(po.id) as ord_count
		FROM person_order po
		JOIN menu ON menu.id = po.menu_id
		GROUP BY 1
		ORDER BY 2 DESC),
	rest_visnor AS
		(SELECT pv.pizzeria_id, COALESCE((COUNT(pv.id) + ord_count),0) as total_count
		FROM person_visits pv
		FULL OUTER JOIN rest_ord ro ON ro.pizzeria_id = pv.pizzeria_id
		GROUP BY pv.pizzeria_id, ord_count
		ORDER BY 2 DESC)
		
SELECT name, total_count
FROM rest_visnor rv
JOIN pizzeria pz ON pz.id = rv.pizzeria_id
ORDER BY 2 desc, 1 asc;