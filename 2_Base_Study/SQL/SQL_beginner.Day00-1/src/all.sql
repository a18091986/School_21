SELECT * FROM person p ;
SELECT * FROM pizzeria p ;
SELECT * FROM person_visits pv ;
SELECT * FROM person_order po ;

--ex00
SELECT name, age FROM person WHERE address = 'Kazan';

--ex01

SELECT name, age FROM person p WHERE gender = 'female' AND address = 'Kazan' ORDER BY name;

--ex02
--2.1
SELECT name, rating FROM pizzeria p WHERE rating >= 3.5 AND rating <= 5.0 ORDER BY rating;
--2.2
SELECT name, rating FROM pizzeria p WHERE rating BETWEEN 3.5 AND 5.0 ORDER BY rating ;

--ex03

SELECT DISTINCT 
	person_id FROM person_visits pv 
WHERE 
	(visit_date BETWEEN '2022-01-06' AND '2022-01-09') OR (pizzeria_id = 2)
ORDER BY 
	person_id DESC;

--ex04  

SELECT CONCAT(name, ' (age:', age,',gender:''',gender,''',address:''',address,''')') AS person_information FROM person p ORDER BY person_information ASC;


--ex05
SELECT
    (SELECT name FROM person WHERE person.id = person_order.person_id) AS NAME
FROM person_order
WHERE (menu_id = 13 OR menu_id = 14 OR menu_id = 18) AND order_date = '2022-01-07';

--ex06

SELECT
    (SELECT name FROM person WHERE person.id = person_order.person_id) AS NAME,
    (SELECT name = 'Denis' FROM person WHERE person.id = person_order.person_id) AS check_name
FROM person_order
WHERE (menu_id = 13 OR menu_id = 14 OR menu_id = 18) AND order_date = '2022-01-07';

--ex07

SELECT id, name
	(CASE 
		when age >=10 AND age <=20 then 'interval #1' 
		when age > 20 AND age < 24 then 'interval #2'
        else 'interval #3' 
     END) AS interval_info
FROM person p
ORDER BY interval_info;

--ex08

SELECT * FROM person_order WHERE id % 2 = 0 ORDER BY id;

--ex09

SELECT
	(SELECT name FROM person WHERE person.id = person_visits.person_id) AS person_name,
	(SELECT name FROM pizzeria WHERE pizzeria.id = person_visits.pizzeria_id) AS pizzeria_name
FROM person_visits WHERE visit_date BETWEEN '2022-01-07' AND '2022-01-09'
ORDER BY person_name ASC, pizzeria_name DESC;



------------------------------------------------DAY 04-----------------------------------------
SELECT name from v_persons_female
UNION
SELECT name from v_persons_male
ORDER by name;


CREATE view v_generated_dates as 
(SELECT days::DATE as generated_date
from generate_series('2022-01-01', '2022-01-31', interval '1 day') as days
 order by generated_date
);

  select count(*) =31 as check,
      min(generated_date) as check1,
      max(generated_date) as check2
  from v_generated_dates;      
 
  select generated_date as missing_date
  from v_generated_dates
  except
  select visit_date
  from person_visits
  order by 1 
 
  
  
SELECT DISTINCT generated_date as missing_date
from v_generated_dates
LEFT JOIN person_visits as ps
on v_generated_dates.generated_date = ps.visit_date
where ps.visit_date IS NULL
ORDER BY missing_date;

CREATE view v_symmetric_union as (
(SELECT person_id FROM person_visits
        WHERE visit_date = '2022-01-02'
    EXCEPT
    SELECT person_id FROM person_visits
        WHERE visit_date = '2022-01-06')
	
	UNION
	
	 (SELECT person_id FROM person_visits
        WHERE visit_date = '2022-01-06'
    EXCEPT
    SELECT person_id FROM person_visits
        WHERE visit_date = '2022-01-02')
)

 select * from v_symmetric_union;

CREATE VIEW v_price_with_discount AS(
	SELECT
 name,
 pizza_name,
 price,
CAST(price - price * 0.1 as INTEGER) as discount_price
from person_order
 	JOIN menu ON person_order.menu_id = menu.id
    JOIN person on person_order.person_id = person.id
    ORDER BY name, pizza_name
)

  select *
  from v_price_with_discount  
  
  
CREATE MATERIALIZED VIEW mv_dmitriy_visits_and_eats AS(
SELECT pizzeria.name as pizzeria_name
	from person_visits
JOIN person on person_visits.person_id = person.id
JOIN menu ON person_visits.pizzeria_id = menu.pizzeria_id
JOIN pizzeria on menu.pizzeria_id = pizzeria.id
where person.name = 'Dmitriy' and visit_date = '2022-01-08' AND price < 800
)


  select *
  from mv_dmitriy_visits_and_eats      ;
 
 
 INSERT INTO person_visits(id, person_id, pizzeria_id, visit_date)
values(
(SELECT MAX(id) from person_visits) +1,
(SELECT id from person where name = 'Dmitriy'),
(SELECT DISTINCT pizzeria.id
from pizzeria
 JOIN menu ON pizzeria.id = menu.pizzeria_id
 JOIN mv_dmitriy_visits_and_eats AS mv ON mv.pizzeria_name != pizzeria.name
 WHERE menu.price < 800 LIMIT 1
),
	'2022-01-08'
);
REFRESH MATERIALIZED VIEW mv_dmitriy_visits_and_eats;



  select *
  from mv_dmitriy_visits_and_eats;
 
 
 DROP VIEW v_persons_female;
DROP VIEW v_persons_male;
DROP VIEW v_price_with_discount;
DROP VIEW v_generated_dates;
DROP VIEW v_symmetric_union;
DROP MATERIALIZED VIEW mv_dmitriy_visits_and_eats;


   select count(*) =0 as check
  from pg_class
  where relname in ('v_generated_dates','v_persons_female','v_persons_male',
  'v_price_with_discount','v_symmetric_union', 'mv_dmitriy_visits_and_eats')


  
  
  -----------------------------------------DAY03---------------------
  
  SELECT menu.pizza_name,
	menu.price,
	pizzeria.name AS pizzeria_name,
	person_visits.visit_date
FROM menu
JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
JOIN person_visits ON person_visits.pizzeria_id = menu.pizzeria_id
JOIN person ON person.id = person_visits.person_id
WHERE person.name = 'Kate' AND menu.price BETWEEN 800 AND 1000
ORDER BY 1, 2, 3;

SELECT id AS menu_id
FROM menu
WHERE id NOT IN (SELECT menu_id FROM person_order WHERE menu_id = menu.id)
ORDER BY 1;

SELECT pizza_name, price, pizzeria.name AS pizzeria_name
FROM menu
JOIN pizzeria ON menu.pizzeria_id = pizzeria.id
WHERE menu.id NOT IN (SELECT menu_id FROM person_order WHERE menu_id = menu.id)
ORDER BY 1, 2;


----------------------ТУТ DINO лишнее!!!!!----------------------
WITH my_cte AS (SELECT pizzeria.name AS name, person.gender AS gender
				   FROM person_order
				   JOIN person ON person.id = person_order.person_id
				   JOIN menu ON menu.id = person_order.menu_id
				   JOIN pizzeria ON pizzeria.id = menu.pizzeria_id)
(SELECT my_cte.name AS pizzeria_name
FROM my_cte
WHERE my_cte.gender = 'female'
EXCEPT ALL
SELECT my_cte.name AS pizzeria_name
FROM my_cte
WHERE my_cte.gender = 'male') 

UNION

(SELECT my_cte.name AS pizzeria_name
FROM my_cte
WHERE my_cte.gender = 'male'
EXCEPT ALL
SELECT my_cte.name AS pizzeria_name
FROM my_cte
WHERE my_cte.gender = 'female')

ORDER BY 1;


WITH my_cte AS (SELECT pizzeria.name AS name, person.gender AS gender
				   FROM person_order
				   JOIN person ON person.id = person_order.person_id
				   JOIN menu ON menu.id = person_order.menu_id
				   JOIN pizzeria ON pizzeria.id = menu.pizzeria_id)
(SELECT my_cte.name AS pizzeria_name
FROM my_cte
WHERE my_cte.gender = 'female'
EXCEPT
SELECT my_cte.name AS pizzeria_name
FROM my_cte
WHERE my_cte.gender = 'male') 

UNION

(SELECT my_cte.name AS pizzeria_name
FROM my_cte
WHERE my_cte.gender = 'male'
EXCEPT
SELECT my_cte.name AS pizzeria_name
FROM my_cte
WHERE my_cte.gender = 'female')

ORDER BY 1;

SELECT pizzeria.name AS pizzeria_name
FROM person_visits
JOIN person ON person.id = person_visits.person_id
JOIN pizzeria ON pizzeria.id = person_visits.pizzeria_id
WHERE person.name = 'Andrey' 

EXCEPT 

SELECT pizzeria.name AS pizzeria_name
FROM person_order
JOIN person ON person.id = person_order.person_id
JOIN menu ON menu.id = person_order.menu_id
JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
WHERE person.name = 'Andrey' 

ORDER BY 1;

WITH pizza_1 AS (SELECT pizza_name,	pizzeria.name AS pizzeria_name_1, price
				FROM menu
				JOIN pizzeria ON pizzeria.id = menu.pizzeria_id),
pizza_2 AS (SELECT pizza_name,	pizzeria.name AS pizzeria_name_2, price
				FROM menu
				JOIN pizzeria ON pizzeria.id = menu.pizzeria_id)
SELECT pizza_1.pizza_name,
	pizza_1.pizzeria_name_1,
	pizza_2.pizzeria_name_2,
	pizza_1.price
FROM pizza_1, pizza_2
WHERE pizza_1.pizza_name = pizza_2.pizza_name
	AND pizza_1.pizzeria_name_1 != pizza_2.pizzeria_name_2
	AND pizza_1.price = pizza_2.price
	AND pizza_1.pizzeria_name_1 < pizza_2.pizzeria_name_2
ORDER BY 1;

INSERT INTO menu (id, pizza_name, pizzeria_id, price)
VALUES (19, 'greek pizza', 2, 800);

 SELECT * FROM menu
 WHERE id = 19
 
 
   select count(*)=1 as check
   from menu
   where id = 19 and pizzeria_id=2 and pizza_name = 'greek pizza' and price=800;

  
  INSERT INTO menu (id, pizza_name, pizzeria_id, price)
VALUES ((SELECT MAX(id) + 1 FROM menu), 
		'sicilian pizza', 
   (SELECT id FROM pizzeria WHERE name = 'Dominos'),
   900);

-- SELECT * FROM menu
-- WHERE pizza_name = 'sicilian pizza'
  
     select count(*)=1 as check
   from menu
   where id = 20 and pizzeria_id=2 and pizza_name = 'sicilian pizza' and price=900
   
   
   INSERT INTO person_visits (id, person_id, pizzeria_id, visit_date)
VALUES ((SELECT MAX(id) + 1 FROM person_visits),
	   (SELECT id FROM person WHERE name = 'Denis'),
	   (SELECT id FROM pizzeria WHERE name = 'Dominos'),
	   '2022-02-24');
	   
INSERT INTO person_visits (id, person_id, pizzeria_id, visit_date)
VALUES ((SELECT MAX(id) + 1 FROM person_visits),
	   (SELECT id FROM person WHERE name = 'Irina'),
	   (SELECT id FROM pizzeria WHERE name = 'Dominos'),
	   '2022-02-24');
	   
-- SELECT * FROM person_visits
-- WHERE visit_date = '2022-02-24'
	  
         select count(*)=2 as check
   from person_visits
   where visit_date = '2022-02-24' and person_id in (6,4) and pizzeria_id=2;
  
  
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
	  
	  
         select count(*)=2 as check
   from person_order
   where order_date = '2022-02-24' and person_id in (6,4) and menu_id=(select id from menu where pizza_name = 'sicilian pizza')

   UPDATE menu
SET price = price * 0.9
WHERE pizza_name = 'greek pizza';

-- SELECT * FROM menu
-- WHERE pizza_name = 'greek pizza'



   select (800-800*0.1) = price as check
   from menu
   where pizza_name ='greek pizza'
   
   
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
	
   select count(*)=9 as check
   from person_order
   where order_date='2022-02-25' and menu_id = (select id from menu where pizza_name = 'greek pizza')
   
   
   DELETE FROM person_order
WHERE order_date = '2022-02-25';

DELETE FROM menu
WHERE pizza_name = 'greek pizza';
		
-- SELECT * FROM person_order
-- WHERE order_date = '2022-02-25'

-- SELECT * FROM menu
-- WHERE pizza_name = 'greek pizza'


   select count(*)=0 as check
   from person_order
   where order_date='2022-02-25' and menu_id = (select id from menu where pizza_name = 'greek pizza')
   
select count(*)=0 as check
from menu
where pizza_name = 'greek pizza'