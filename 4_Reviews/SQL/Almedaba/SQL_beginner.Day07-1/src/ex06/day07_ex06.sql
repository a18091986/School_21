SELECT
    name, 
    COUNT(*) AS count_of_orders, 
    ROUND(AVG(price), 2), 
    MAX(price) as max_price, 
    MIN(price) as min_price
FROM pizzeria
JOIN menu
  ON pizzeria.id = menu.pizzeria_id
JOIN person_order
  ON person_order.menu_id = menu.id
GROUP BY name
ORDER BY name;