INSERT INTO person_order (id, menu_id, order_date, person_id)
VALUES ((SELECT MAX(id) + 1 FROM person_order),
	   (SELECT id FROM menu WHERE pizza_name = 'sicilian pizza'),
	   '2022-02-24',
	   (SELECT id FROM person WHERE name = 'Denis'));
	   
INSERT INTO person_order (id, menu_id, order_date, person_id)
VALUES ((SELECT MAX(id) + 1 FROM person_order),
	   (SELECT id FROM menu WHERE pizza_name = 'sicilian pizza'),
	   '2022-02-24',
	   (SELECT id FROM person WHERE name = 'Irina'));
	   
-- SELECT * FROM person_order
-- WHERE order_date = '2022-02-24'