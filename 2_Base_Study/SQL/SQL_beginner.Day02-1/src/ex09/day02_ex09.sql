select * from
(SELECT DISTINCT name FROM
    (SELECT id, name FROM person WHERE gender = 'female') pp
LEFT JOIN 
    person_order
ON pp.id = person_order.person_id
LEFT JOIN
    (SELECT id FROM menu WHERE pizza_name = 'pepperoni pizza') pz
ON pz.id = person_order.id) t1

INTERSECT

(SELECT DISTINCT name FROM
    (SELECT id, name FROM person WHERE gender = 'female') pp
LEFT JOIN 
    person_order
ON pp.id = person_order.person_id
LEFT JOIN
    (SELECT id FROM menu WHERE pizza_name = 'cheese pizza') pz
ON pz.id = person_order.id) t2

ORDER BY name DESC;