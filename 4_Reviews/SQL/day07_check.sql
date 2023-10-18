-- 00 

Checks for the file day07_ex00.sql
- The SQL script looks like below.

      select person_id, count(*) as "count_of_visits"
      from person_visits
      group by person_id
      order by 2 desc,1 asc;

- The result is below (raw ordering should be the same like on a screen below)

      "9"	"4"
      "4"	"3"
      "6"	"3"
      "8"	"3"
      "2"	"2"
      "3"	"2"
      "5"	"2"
      "7"	"2"
      "1"	"1"




SELECT person_id, COUNT(pizzeria_id) AS count_of_visits
FROM person_visits
GROUP BY person_id
ORDER BY count_of_visits DESC, person_id;

-- 01 
Checks for the file day07_ex01.sql
- The SQL script looks like below.

      select p.name, count(*) as "count_of_visits"
      from person_visits inner join person p on p.id = person_visits.person_id
      group by p.name
      order by 2 desc,1 asc
      limit 4;

- The result is below (raw ordering should be the same like below)

      "Dmitriy"	"4"
      "Denis"	"3"
      "Irina"	"3"
      "Nataly"	"3"


SELECT person.name, COUNT(pizzeria_id) AS count_of_visits
FROM person_visits INNER JOIN person ON person.id = person_visits.person_id
GROUP BY person_id, person.name
ORDER BY count_of_visits DESC, person.name
LIMIT 4;
-- 02 
Checks for the file day07_ex02.sql
- The SQL script looks like below.

      (select p.name, count(*) as "count", 'visit' as action_type
      from person_visits inner join pizzeria p on p.id = person_visits.pizzeria_id
      group by p.name
      order by 2 desc
      limit 3)
      union
      (select p.name, count(*) as "count", 'order' as action_type
      from person_order inner join menu m on person_order.menu_id = m.id
          inner join pizzeria p on m.pizzeria_id = p.id
      group by p.name
      order by 2 desc
      limit 3)
      order by 3,2 desc 

- The result is below (raw ordering should be the same like below)

      "Dominos"	"6"	"order"
      "Best Pizza"	"5"	"order"
      "DinoPizza"	"5"	"order"
      "Dominos"	"7"	"visit"
      "DinoPizza"	"4"	"visit"
      "Pizza Hut"	"4"	"visit"



WITH visit AS (
	SELECT pizzeria.name, COUNT(*) AS count, 'visit' AS action_type
	FROM pizzeria INNER JOIN person_visits ON pizzeria.id = person_visits.pizzeria_id
	GROUP BY pizzeria_id, pizzeria.name
	ORDER BY count DESC
	LIMIT 3
),
orders AS (
	SELECT pizzeria.name, COUNT(*) AS count, 'order' AS action_type
	FROM pizzeria
		INNER JOIN menu ON pizzeria.id = menu.pizzeria_id
		INNER JOIN person_order ON menu.id = person_order.menu_id
	GROUP BY pizzeria.name
	ORDER BY count DESC
	LIMIT 3
)
SELECT * FROM visit
UNION ALL
SELECT * FROM orders
ORDER BY action_type, count DESC;
-- 03 
Checks for the file day07_ex03.sql
- The SQL script looks like below.

      select t1.name, coalesce(t1.count,0) + coalesce(t2.count,0) as total_count
      from
      (select p.name, count(*) as "count"
      from person_visits inner join pizzeria p on p.id = person_visits.pizzeria_id
      group by p.name) as t1 full  join
      (select p.name, count(*) as "count"
      from person_order inner join menu m on person_order.menu_id = m.id
          inner join pizzeria p on m.pizzeria_id = p.id
      group by p.name) as t2 on  t1.name = t2.name
      order by 2 desc,1 asc; 

- The result is below (raw ordering should be the same like below)

      "Dominos"	"13"
      "DinoPizza"	"9"
      "Best Pizza"	"8"
      "Pizza Hut"	"8"
      "Papa Johns"	"5"
      "DoDo Pizza"	"1"



WITH visit AS (
	SELECT pizzeria.name, COUNT(*) AS count, 'visit' AS action_type
	FROM pizzeria INNER JOIN person_visits ON pizzeria.id = person_visits.pizzeria_id
	GROUP BY pizzeria_id, pizzeria.name
	ORDER BY count DESC
),
orders AS (
	SELECT pizzeria.name, COUNT(*) AS count, 'order' AS action_type
	FROM pizzeria
		INNER JOIN menu ON pizzeria.id = menu.pizzeria_id
		INNER JOIN person_order ON menu.id = person_order.menu_id
	GROUP BY pizzeria.name
	ORDER BY count DESC
)
SELECT v.name, v.count + o.count AS total_count
FROM visit v, orders o
WHERE v.name = o.name
ORDER BY total_count DESC, v.name ASC;
-- 04 
Checks for the file day07_ex04.sql
- The SQL script looks like below.

      select p.name, count(*) as "count_of_visits"
      from person_visits inner join person p on p.id = person_visits.person_id
      group by p.name
      having count(*) > 3;

- The result is below (raw ordering should be the same like below)

        "Dmitriy"	"4"   


SELECT person.name, COUNT(pizzeria_id) AS count_of_visits
FROM person_visits INNER JOIN person ON person.id = person_visits.person_id
GROUP BY person_visits.person_id, person.name
HAVING COUNT(pizzeria_id) > 3;
-- 05 
Checks for the file day07_ex05.sql
- The SQL script looks like below.

       select distinct p.name
       from person_order inner join person p on p.id = person_order.person_id
       order by 1;           

- The result is below (raw ordering should be the same like below)

       "Andrey"
       "Anna"
       "Denis"
       "Dmitriy"
       "Elvira"
       "Irina"
       "Kate"
       "Nataly"
       "Peter"


SELECT DISTINCT person.name
FROM person_order
         JOIN person ON person_order.person_id = person.id
ORDER BY 1;
-- 06 
Checks for the file day07_ex06.sql
- The SQL script looks like below.

        select p.name, count(*) as count_of_orders, round(avg(m.price),2) as average_price, max(m.price) as max_price, min(m.price) as min_price
          from person_order inner join menu m on person_order.menu_id = m.id
              inner join pizzeria p on m.pizzeria_id = p.id
          group by p.name
          order by 1;                 

- The result is below (raw ordering should be the same like below)

    "Best Pizza"	"5"	"780"	"850"	"700"
    "DinoPizza"	"5"	"880"	"1000"	"800"
    "Dominos"	"6"	"933.33"	"1100"	"800"
    "Papa Johns"	"2"	"975"	"1000"	"950"
    "Pizza Hut"	"4"	"1125"	"1200"	"900"


SELECT pizzeria.name AS name,
	COUNT(*) AS count_of_orders,
	ROUND(AVG(price), 2) AS average_price,
	MAX(price) AS max_price,
	MIN(price) AS min_price
FROM pizzeria
	INNER JOIN menu ON menu.pizzeria_id = pizzeria.id
	INNER JOIN person_order ON menu.id = person_order.menu_id
GROUP BY name
ORDER BY 1;
-- 07 
Checks for the file day07_ex07.sql
- The SQL script looks like below.

        select  round(avg(rating),4) as global_rating
          from pizzeria;               

- The result is below (raw ordering should be the same like below)

    "3.9167"

SELECT ROUND(AVG(rating), 4) AS global_rating
FROM pizzeria;
-- 08 
Checks for the file day07_ex08.sql
- The SQL script looks like below.

        select address, p.name, count(*)
          from person_order inner join menu m on person_order.menu_id = m.id
              inner join pizzeria p on m.pizzeria_id = p.id
              inner join person p1 on p1.id = person_order.person_id
          group by address, p.name
          order by 1,2;             

- The result is below (raw ordering should be the same like below)

    "Kazan"	"Best Pizza"	"4"
    "Kazan"	"DinoPizza"	"4"
    "Kazan"	"Dominos"	"1"
    "Moscow"	"Dominos"	"2"
    "Moscow"	"Pizza Hut"	"2"
    "Novosibirsk"	"Dominos"	"1"
    "Novosibirsk"	"Papa Johns"	"1"
    "Saint-Petersburg"	"Dominos"	"2"
    "Saint-Petersburg"	"Papa Johns"	"1"
    "Saint-Petersburg"	"Pizza Hut"	"2"
    "Samara"	"Best Pizza"	"1"
    "Samara"	"DinoPizza"	"1"


SELECT address, pizzeria.name, COUNT(*) AS count_of_orders
FROM person
	INNER JOIN person_order ON person.id = person_order.person_id
	INNER JOIN menu ON menu.id = person_order.menu_id
	INNER JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
GROUP BY pizzeria.name, address
ORDER BY 1, 2;
-- 09
Checks for the file day07_ex09.sql
- The SQL script looks like below.

        select address,round((max(age)- min(age) /max(age::numeric)),2) as formula,round(avg(age),2) as "average",
              round((max(age)- min(age) /max(age::numeric)),2) > round(avg(age),2) as comparison
          from person
          group by address
          order by 1;           

- The result is below (raw ordering should be the same like below)

    "Kazan"	"44.71"	"30.33"	"true"
    "Moscow"	"20.24"	"18.5"	"true"
    "Novosibirsk"	"29"	"30"	"false"
    "Saint-Petersburg"	"23.13"	"22.5"	"true"
    "Samara"	"17"	"18"	"false"



SELECT address,
	ROUND((MAX(age::numeric) - (MIN(age::numeric) / MAX(age::numeric))), 2) AS formula,
	ROUND(AVG(age::numeric), 2) AS average,
	((MAX(age::numeric) - (MIN(age::numeric) / MAX(age::numeric))) > AVG(age::numeric)) AS comparison
FROM person
GROUP BY 1
ORDER BY 1;
