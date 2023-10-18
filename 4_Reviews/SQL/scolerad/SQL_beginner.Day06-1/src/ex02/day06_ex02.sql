SELECT p.name, pizza_name, price, price * (1 - discount / 100) AS discount_price, pz.name AS pizzeria_name
FROM person_order po
         JOIN menu m on m.id = po.menu_id
         JOIN person p on p.id = po.person_id
         JOIN pizzeria pz on pz.id = m.pizzeria_id
         JOIN person_discounts pd ON (po.person_id = pd.person_id AND pz.id = pd.pizzeria_id)
ORDER BY 1, 2;