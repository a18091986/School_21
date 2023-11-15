WITH total AS (
  (SELECT 
    name, 
    COUNT(person_visits.visit_date) AS count
  FROM pizzeria
  LEFT JOIN person_visits
    ON person_visits.pizzeria_id = pizzeria.id
  GROUP BY name)
  UNION ALL
  (SELECT 
    name, 
    COUNT(person_order.order_date) AS count
  FROM pizzeria
  LEFT JOIN menu
    ON menu.pizzeria_id = pizzeria.id
  LEFT JOIN person_order
    ON person_order.menu_id = menu.id
  GROUP BY name
  ORDER BY count DESC) 
)
SELECT name, SUM(count) AS total_count
FROM total
GROUP BY name
ORDER BY total_count DESC, name ASC;