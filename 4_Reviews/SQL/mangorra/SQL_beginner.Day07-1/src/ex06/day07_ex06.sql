SELECT name, COUNT(po.id) AS count_of_orders, ROUND(AVG(price),2) AS average_price, 
			MAX(price) AS max_price, MIN(price) AS min_price
FROM menu m
JOIN person_order po ON po.menu_id = m.id
JOIN pizzeria pz ON pz.id =  m.pizzeria_id
GROUP BY 1
ORDER BY 1;