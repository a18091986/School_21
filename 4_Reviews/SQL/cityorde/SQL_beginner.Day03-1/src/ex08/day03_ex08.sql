INSERT INTO menu (id, pizza_name, pizzeria_id, price)
VALUES ((SELECT MAX(id) + 1 FROM menu), 
		'sicilian pizza', 
	   (SELECT id FROM pizzeria WHERE name = 'Dominos'),
	   900);

-- SELECT * FROM menu
-- WHERE pizza_name = 'sicilian pizza'