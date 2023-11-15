SELECT 
  person.name AS name, 
  menu.pizza_name AS pizza_name,
  price,
  ROUND((1 - person_discounts.discount / 100) * price, 2) AS discount_price, 
  pizzeria.name AS pizzeria_name
FROM person_order
JOIN person
ON person.id = person_id 
JOIN menu
ON menu.id = menu_id
JOIN pizzeria
ON pizzeria.id = menu.pizzeria_id 
JOIN person_discounts
ON person_discounts.person_id = person.id AND person_discounts.pizzeria_id = pizzeria.id
ORDER BY 1, 2;
