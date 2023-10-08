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







