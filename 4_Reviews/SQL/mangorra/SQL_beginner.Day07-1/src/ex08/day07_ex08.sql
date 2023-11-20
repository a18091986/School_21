SELECT address, piz.name, COUNT(po.id) AS count_of_orders
FROM person_order po
JOIN person p ON po.person_id = p.id
JOIN menu m ON po.menu_id = m.id
JOIN  pizzeria piz ON piz.id = m.pizzeria_id
GROUP BY 1,2
ORDER BY 1,2;