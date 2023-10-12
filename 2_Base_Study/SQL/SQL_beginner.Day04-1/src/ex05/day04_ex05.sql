-- Exercise 05: Let’s calculate a discount price for each person	
-- Turn-in directory	ex05
-- Files to turn-in	day04_ex05.sql
-- Allowed	
-- Language	ANSI SQL

-- Please create a Database View v_price_with_discount that returns a person's orders with person names, pizza names, real price and calculated column discount_price (with applied 10% discount and satisfies formula price - price*0.1). The result please sort by person name and pizza name and make a round for discount_price column to integer type. Please take a look at a sample result below.

-- name	pizza_name	price	discount_price
-- Andrey	cheese pizza	800	720
-- Andrey	mushroom pizza	1100	990
-- ...	...	...	...

CREATE OR REPLACE VIEW v_price_with_discount AS
SELECT name, pizza_name, price, round(price*0.9) AS discount_price FROM
    person_order
JOIN
    person
ON person_order.person_id = person.id
JOIN
    menu
ON person_order.menu_id = menu.id
ORDER BY 1, 2;

SELECT * FROM v_price_with_discount;