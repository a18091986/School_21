INSERT INTO person_order (id, menu_id, order_date, person_id)
VALUES (generate_series(
			(SELECT MAX(id) + 1 FROM person_order),
			(SELECT MAX(id) FROM person) + (SELECT MAX(id) FROM person_order)
		),
		(SELECT id FROM menu WHERE pizza_name = 'greek pizza'),
		'2022-02-25',
		generate_series(
			(SELECT MIN(id) FROM person),
			(SELECT MAX(id) FROM person)
		));
		
-- SELECT * FROM person_order
-- WHERE order_date = '2022-02-25'