-- 00

SELECT pizza_name, price, pizzeria.name AS pizzeria_name, visit_date FROM
    person
JOIN
    person_visits
ON person.id = person_visits.person_id
JOIN
    pizzeria
ON pizzeria.id = person_visits.pizzeria_id
JOIN
    menu
ON menu.pizzeria_id = pizzeria.id
WHERE person.name = 'Kate' AND price BETWEEN 800 AND 1000
ORDER BY pizza_name, price, pizzeria_name;
-- 
-- SELECT pizza_name,
--        price,
--        pizzeria.NAME AS pizzeria_name,
--        visit_date
-- FROM   person
--        JOIN person_visits
--          ON person.id = person_visits.person_id
--        JOIN pizzeria
--          ON person_visits.pizzeria_id = pizzeria.id
--        JOIN menu
--          ON pizzeria.id = menu.pizzeria_id
-- WHERE  person.NAME = 'Kate'
--        AND price BETWEEN '800' AND '1000'
-- ORDER  BY pizza_name,
--           price,
--           pizzeria_name;
-- -- 
-- SELECT
--   m.pizza_name,
--   m.price,
--   pz.name AS pizzeria_name,
--   pv.visit_date
-- FROM
--   pizzeria pz
--   JOIN menu m ON pz.id = m.pizzeria_id
--   JOIN person_visits pv on pz.id = pv.pizzeria_id
--   JOIN person p on p.id = pv.person_id
-- WHERE
--   p.name = 'Kate'
--   AND price BETWEEN 800
--   AND 1000
-- ORDER BY
--   m.pizza_name,
--   m.price,
--   pz.name;

-- --   

-- WITH visits AS (SELECT pv.person_id, pv.pizzeria_id, pv.visit_date
--                 FROM person_visits pv
--                          JOIN (SELECT * FROM person WHERE person.name = 'Kate') q1
--                               ON pv.person_id = q1.id),
--      pizzerias AS (SELECT pi.id, pi.name, visits.visit_date
--                    FROM pizzeria pi
--                             JOIN visits ON
--                        pi.id = visits.pizzeria_id),
--      prices AS (SELECT *
--                 FROM menu m
--                          JOIN pizzerias ON m.pizzeria_id = pizzerias.id)
-- SELECT pr.pizza_name,
--        pr.price,
--        pr.name AS pizzeria_name,
--        pr.visit_date
-- FROM prices pr
-- WHERE pr.price BETWEEN 800 AND 1000
-- ORDER BY 1, 2, 3, 4;

---------------------------- 01  --------------------

select id menu_id from menu
EXCEPT
select menu_id from person_order
order by 1;

--
SELECT id AS menu_id
FROM   menu
EXCEPT
SELECT menu_id
FROM   person_order
ORDER  BY menu_id; 
--
(
  SELECT
    id AS menu_id
  FROM
    menu
)
EXCEPT
   ALL(
    SELECT
      menu_id
    FROM
      person_order
  )
ORDER BY menu_id;
--
SELECT m.id AS menu_id
FROM menu m
EXCEPT
SELECT po.menu_id
FROM person_order po
ORDER BY 1;

---------------------------- 02  --------------------
SELECT pizza_name, price, name pizzeria_name FROM
(SELECT id menu_id FROM menu
EXCEPT
SELECT menu_id FROM person_order) pz_id
JOIN
    menu 
ON menu.id = pz_id.menu_id
JOIN
    pizzeria
ON pizzeria.id = menu.pizzeria_id
ORDER BY pizza_name, price;
--
-- WITH orders AS (SELECT m.id AS menu_id
--                 FROM menu m
--                 EXCEPT
--                 SELECT po.menu_id
--                 FROM person_order po
--                 ORDER BY 1),
--      pizzas AS (SELECT *
--                 FROM menu
--                          RIGHT JOIN orders ON menu.id = orders.menu_id)
-- SELECT pizzas.pizza_name,
--        pizzas.price,
--        pi.name AS pizzeria_name
-- FROM pizzas
--          JOIN pizzeria pi ON pizzas.pizzeria_id = pi.id
-- ORDER BY 1, 2;
-- --
-- WITH tmp_lack_orders AS (
--   (
--     SELECT
--       id
--     FROM
--       menu
--   )
--   EXCEPT
--     ALL (
--       SELECT
--         menu_id
--       FROM
--         person_order
--     )
-- )
-- SELECT
--   pizza_name,
--   price,
--   pz.name AS name_pizzeria
-- FROM
--   pizzeria pz
--   JOIN menu m on pz.id = m.pizzeria_id
-- WHERE
--   m.id IN (
--     SELECT
--       id
--     FROM
--       tmp_lack_orders
--   )
-- ORDER BY
--   pizza_name,
--   price;
-- --
-- SELECT pizza_name,
--        price,
--        pizzeria.name AS pizzeria_name
-- FROM   menu
--        JOIN (SELECT id AS menu_id
--              FROM   menu
--              EXCEPT
--              SELECT menu_id
--              FROM   person_order
--              ORDER  BY menu_id) AS pz_id
--          ON menu.id = pz_id.menu_id
--        JOIN pizzeria
--          ON menu.pizzeria_id = pizzeria.id
-- ORDER  BY pizza_name,
--           price; 
---------------------------- 03  --------------------

WITH 
    all_visiters AS 
        (SELECT gender, pizzeria.name FROM
            person_visits
        JOIN
            person
        ON person_visits.person_id = person.id
        JOIN
            pizzeria
        ON pizzeria.id = person_visits.pizzeria_id),
    male_visiters AS 
        (SELECT name FROM all_visiters WHERE gender = 'male'
        EXCEPT ALL
        SELECT name FROM all_visiters WHERE gender = 'female'),
    female_visiters AS 
        (SELECT name FROM all_visiters WHERE gender = 'female'
        EXCEPT ALL
        SELECT name FROM all_visiters WHERE gender = 'male')
SELECT name pizzeria_name FROM male_visiters
UNION ALL
SELECT name pizzeria_name FROM female_visiters
ORDER BY pizzeria_name;

--
WITH people AS (SELECT p.gender, pi.name
                FROM person_visits pv
                         JOIN
                     person p ON pv.person_id = p.id
                         JOIN pizzeria pi ON pv.pizzeria_id = pi.id),
     women AS (SELECT p1.name AS pizzeria_name
               FROM people p1
               WHERE p1.gender = 'female'),
     men AS (SELECT p2.name AS pizzeria_name
             FROM people p2
             WHERE p2.gender = 'male'),
     only_women AS (SELECT *
                    FROM women
                    EXCEPT ALL
                    SELECT *
                    FROM men),
     only_men AS (SELECT *
                  FROM men
                  EXCEPT ALL
                  SELECT *
                  FROM women)
SELECT *
FROM only_women
UNION ALL
SELECT *
FROM only_men
ORDER BY 1;
--
(SELECT pizzeria.name AS pizzeria_name
FROM person_visits
    INNER JOIN pizzeria ON person_visits.pizzeria_id = pizzeria.id
    INNER JOIN person ON person_visits.person_id = person.id
WHERE person.gender = 'female'
EXCEPT ALL
SELECT pizzeria.name AS pizzeria_name
FROM person_visits
    INNER JOIN pizzeria ON person_visits.pizzeria_id = pizzeria.id
    INNER JOIN person ON person_visits.person_id = person.id
WHERE person.gender = 'male'
)

UNION ALL

(SELECT pizzeria.name AS pizzeria_name
FROM person_visits
    INNER JOIN pizzeria ON person_visits.pizzeria_id = pizzeria.id
    INNER JOIN person ON person_visits.person_id = person.id
WHERE person.gender = 'male'
EXCEPT ALL
SELECT pizzeria.name AS pizzeria_name
FROM person_visits
    INNER JOIN pizzeria ON person_visits.pizzeria_id = pizzeria.id
    INNER JOIN person ON person_visits.person_id = person.id
WHERE person.gender = 'female')
ORDER BY pizzeria_name;
--
WITH male
     AS (SELECT pizzeria.name AS pizzeria_name
         FROM   person
                JOIN person_visits
                  ON person.id = person_visits.person_id
                JOIN pizzeria
                  ON person_visits.pizzeria_id = pizzeria.id
         WHERE  gender = 'male'),
     female
     AS (SELECT pizzeria.NAME AS pizzeria_name
         FROM   person
                JOIN person_visits
                  ON person.id = person_visits.person_id
                JOIN pizzeria
                  ON person_visits.pizzeria_id = pizzeria.id
         WHERE  gender = 'female'),
     only_male
     AS (SELECT *
         FROM   male
         EXCEPT ALL
         SELECT *
         FROM   female),
     only_female
     AS (SELECT *
         FROM   female
         EXCEPT ALL
         SELECT *
         FROM   male) SELECT pizzeria_name
FROM   only_male
UNION ALL
SELECT pizzeria_name
FROM   only_female
ORDER  BY pizzeria_name;
---------------------------- 04  --------------------

WITH 
    all_orders AS 
        (SELECT gender, pizzeria.name FROM
            person_order
        JOIN
            person
        ON person_order.person_id = person.id
        JOIN menu
        ON person_order.menu_id = menu.id
        JOIN
            pizzeria
        ON pizzeria.id = menu.pizzeria_id),
    male_visiters AS 
        (SELECT name FROM all_orders WHERE gender = 'male'
        EXCEPT
        SELECT name FROM all_orders WHERE gender = 'female'),
    female_visiters AS 
        (SELECT name FROM all_orders WHERE gender = 'female'
        EXCEPT
        SELECT name FROM all_orders WHERE gender = 'male')
SELECT name pizzeria_name FROM male_visiters
UNION
SELECT name pizzeria_name FROM female_visiters
ORDER BY pizzeria_name;
--
WITH people AS (SELECT p.gender, pi.name
                FROM person_order po
                         JOIN
                     person p ON po.person_id = p.id
                         JOIN menu m ON po.menu_id = m.id
                         JOIN pizzeria pi ON m.pizzeria_id = pi.id),
     women AS (SELECT p1.name AS pizzeria_name
               FROM people p1
               WHERE p1.gender = 'female'),
     men AS (SELECT p2.name AS pizzeria_name
             FROM people p2
             WHERE p2.gender = 'male'),
     only_women AS (SELECT *
                    FROM women
                    EXCEPT
                    SELECT *
                    FROM men),
     only_men AS (SELECT *
                  FROM men
                  EXCEPT
                  SELECT *
                  FROM women)
SELECT *
FROM only_women
UNION
SELECT *
FROM only_men
ORDER BY 1;
--
(SELECT pizzeria.name AS pizzeria_name
FROM menu
    INNER JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
    INNER JOIN person_order ON person_order.menu_id = menu.id
    JOIN person on person_order.person_id = person.id
WHERE person.gender = 'female'
EXCEPT
SELECT pizzeria.name AS pizzeria_name
FROM menu
    INNER JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
    INNER JOIN person_order ON person_order.menu_id = menu.id
    JOIN person on person_order.person_id = person.id
WHERE person.gender = 'male'
)

UNION

(SELECT pizzeria.name AS pizzeria_name
FROM menu
    INNER JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
    INNER JOIN person_order ON person_order.menu_id = menu.id
    JOIN person on person_order.person_id = person.id
WHERE person.gender = 'male'
EXCEPT
SELECT pizzeria.name AS pizzeria_name
FROM menu
    INNER JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
    INNER JOIN person_order ON person_order.menu_id = menu.id
    JOIN person on person_order.person_id = person.id
WHERE person.gender = 'female'
)
ORDER BY pizzeria_name;
--
WITH femail
     AS (SELECT pizzeria.name AS pizzeria_name
         FROM   person
                JOIN person_order
                  ON person.id = person_order.person_id
                JOIN menu
                  ON person_order.menu_id = menu.id
                JOIN pizzeria
                  ON menu.pizzeria_id = pizzeria.id
         WHERE  gender = 'female'),
     male
     AS (SELECT pizzeria.NAME AS pizzeria_name
         FROM   person
                JOIN person_order
                  ON person.id = person_order.person_id
                JOIN menu
                  ON person_order.menu_id = menu.id
                JOIN pizzeria
                  ON menu.pizzeria_id = pizzeria.id
         WHERE  gender = 'male'),
     only_female
     AS (SELECT *
         FROM   femail
         EXCEPT
         SELECT *
         FROM   male),
     only_male
     AS (SELECT *
         FROM   male
         EXCEPT
         SELECT *
         FROM   femail) SELECT pizzeria_name
FROM   only_female
UNION
SELECT pizzeria_name
FROM   only_male; 
---------------------------- 05  --------------------
WITH 
    visited AS
        (SELECT pizzeria.name FROM
            person_visits
        JOIN
            person
        ON person_visits.person_id = person.id
        JOIN
            pizzeria
        ON pizzeria.id = person_visits.pizzeria_id
        WHERE person.name = 'Andrey'),
    ordered AS
        (SELECT pizzeria.name FROM
            person_order
        JOIN
            person
        ON person.id = person_order.person_id
        JOIN
            menu
        ON person_order.menu_id = menu.id
        JOIN
            pizzeria
        ON pizzeria.id = menu.pizzeria_id
        WHERE person.name = 'Andrey')
SELECT * FROM visited
EXCEPT
SELECT * FROM ordered
ORDER BY 1;

--
WITH visit_pz
     AS (SELECT pizzeria.NAME AS pizzeria_name
         FROM   person
                JOIN person_visits
                  ON person.id = person_visits.person_id
                JOIN pizzeria
                  ON person_visits.pizzeria_id = pizzeria.id
         WHERE  person.name = 'Andrey'),
     order_pz
     AS (SELECT pizzeria.name AS pizzeria_name
         FROM   person
                JOIN person_order
                  ON person.id = person_order.person_id
                JOIN menu
                  ON person_order.menu_id = menu.id
                JOIN pizzeria
                  ON menu.pizzeria_id = pizzeria.id
         WHERE  person.name = 'Andrey'),
     v_o
     AS (SELECT *
         FROM   visit_pz
         EXCEPT
         SELECT *
         FROM   order_pz),
     o_v
     AS (SELECT *
         FROM   order_pz
         EXCEPT
         SELECT *
         FROM   visit_pz) SELECT pizzeria_name
FROM   v_o
UNION
SELECT pizzeria_name
FROM   o_v
ORDER  BY pizzeria_name;
--
SELECT pizzeria.name AS pizzeria_name
FROM person_visits
    INNER JOIN pizzeria ON person_visits.pizzeria_id = pizzeria.id
    INNER JOIN person ON person_visits.person_id = person.id
WHERE person.name = 'Andrey'

EXCEPT

SELECT pizzeria.name AS pizzeria_name
FROM menu
    INNER JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
    INNER JOIN person_order ON person_order.menu_id = menu.id
    JOIN person on person_order.person_id = person.id
WHERE person.name = 'Andrey';
--
WITH visits AS (SELECT DISTINCT pi.name AS pizzeria_name
                FROM person_visits pv
                         JOIN (SELECT * FROM person p WHERE p.name = 'Andrey') q1
                              ON pv.person_id = q1.id
                         JOIN pizzeria pi ON pv.pizzeria_id = pi.id),
     orders AS (SELECT DISTINCT pi.name AS pizzeria_name
                FROM person_order po
                         JOIN (SELECT * FROM person p WHERE p.name = 'Andrey') q2
                              ON po.person_id = q2.id
                         JOIN menu m ON po.menu_id = m.id
                         JOIN pizzeria pi ON m.pizzeria_id = pi.id)
SELECT *
FROM visits
EXCEPT
SELECT *
FROM orders;
---------------------------- 06  --------------------
WITH 
    info_about_pizza AS
        (SELECT menu.id, pizza_name, pizzeria.name AS pizzeria_name, price FROM
            menu
        JOIN
            pizzeria
        ON menu.pizzeria_id = pizzeria.id)
SELECT iap1.pizza_name, iap1.pizzeria_name, iap2.pizzeria_name, iap1.price FROM 
    info_about_pizza iap1
JOIN
    info_about_pizza iap2
ON iap1.pizza_name = iap2.pizza_name
WHERE iap1.id > iap2.id AND iap1.price = iap2.price;

--
WITH p1
     AS (SELECT pizza_name,
                pizzeria.name AS pizzeria_name_1,
                price,
                pizzeria.id
         FROM   pizzeria
                JOIN menu
                  ON pizzeria.id = menu.pizzeria_id),
     p2
     AS (SELECT pizza_name,
                pizzeria.name AS pizzeria_name_2,
                price,
                pizzeria.id
         FROM   pizzeria
                JOIN menu
                  ON pizzeria.id = menu.pizzeria_id)
SELECT p1.pizza_name,
       pizzeria_name_1,
       pizzeria_name_2,
       p1.price
FROM   p1,
       p2
WHERE  p1.pizza_name = p2.pizza_name
       AND p1.price = p2.price
       AND p1.id > p2.id
ORDER  BY pizza_name; 
--
SELECT
  m1.pizza_name AS pizza_name,
  m2.pizza_name AS pizza_name_1,
  piz2.name,
  m1.price AS pizzeria_name_2
FROM
  menu m1
  JOIN menu m2 ON m1.pizza_name = m2.pizza_name
  JOIN pizzeria piz1 ON piz1.id = m1.pizzeria_id
  JOIN pizzeria piz2 ON piz2.id = m2.pizzeria_id
WHERE
  m1.price = m2.price
  AND m1.pizzeria_id > m2.pizzeria_id
ORDER BY
  pizza_name;
--
WITH main AS (SELECT m.pizza_name,
                     pi.name,
                     m.price,
                     pi.id
              FROM menu m
                       JOIN pizzeria pi
                            ON m.pizzeria_id = pi.id)
SELECT q1.pizza_name,
       q1.name   AS pizzeria_name_1,
       main.name AS pizzeria_name_2,
       q1.price
FROM (SELECT * FROM main) q1
         JOIN main ON q1.price = main.price AND q1.pizza_name = main.pizza_name AND q1.id > main.id
ORDER BY 1;
-----------------------------------------------------
-- ####################################################





-- ####################################################
-----------------------------------------------------

drop table if exists person_visits;
drop table if exists person_order;
drop table if exists person;
drop table if exists menu;
drop table if exists pizzeria;



create table person
( id bigint primary key ,
  name varchar not null,
  age integer not null default 10,
  gender varchar default 'female' not null ,
  address varchar
  );

alter table person add constraint ch_gender check ( gender in ('female','male') );

insert into person values (1, 'Anna', 16, 'female', 'Moscow');
insert into person values (2, 'Andrey', 21, 'male', 'Moscow');
insert into person values (3, 'Kate', 33, 'female', 'Kazan');
insert into person values (4, 'Denis', 13, 'male', 'Kazan');
insert into person values (5, 'Elvira', 45, 'female', 'Kazan');
insert into person values (6, 'Irina', 21, 'female', 'Saint-Petersburg');
insert into person values (7, 'Peter', 24, 'male', 'Saint-Petersburg');
insert into person values (8, 'Nataly', 30, 'female', 'Novosibirsk');
insert into person values (9, 'Dmitriy', 18, 'male', 'Samara');


create table pizzeria
(id bigint primary key ,
 name varchar not null ,
 rating numeric not null default 0);

alter table pizzeria add constraint ch_rating check ( rating between 0 and 5);

insert into pizzeria values (1,'Pizza Hut', 4.6);
insert into pizzeria values (2,'Dominos', 4.3);
insert into pizzeria values (3,'DoDo Pizza', 3.2);
insert into pizzeria values (4,'Papa Johns', 4.9);
insert into pizzeria values (5,'Best Pizza', 2.3);
insert into pizzeria values (6,'DinoPizza', 4.2);


create table person_visits
(id bigint primary key ,
 person_id bigint not null ,
 pizzeria_id bigint not null ,
 visit_date date not null default current_date,
 constraint uk_person_visits unique (person_id, pizzeria_id, visit_date),
 constraint fk_person_visits_person_id foreign key  (person_id) references person(id),
 constraint fk_person_visits_pizzeria_id foreign key  (pizzeria_id) references pizzeria(id)
 );

insert into person_visits values (1, 1, 1, '2022-01-01');
insert into person_visits values (2, 2, 2, '2022-01-01');
insert into person_visits values (3, 2, 1, '2022-01-02');
insert into person_visits values (4, 3, 5, '2022-01-03');
insert into person_visits values (5, 3, 6, '2022-01-04');
insert into person_visits values (6, 4, 5, '2022-01-07');
insert into person_visits values (7, 4, 6, '2022-01-08');
insert into person_visits values (8, 5, 2, '2022-01-08');
insert into person_visits values (9, 5, 6, '2022-01-09');
insert into person_visits values (10, 6, 2, '2022-01-09');
insert into person_visits values (11, 6, 4, '2022-01-01');
insert into person_visits values (12, 7, 1, '2022-01-03');
insert into person_visits values (13, 7, 2, '2022-01-05');
insert into person_visits values (14, 8, 1, '2022-01-05');
insert into person_visits values (15, 8, 2, '2022-01-06');
insert into person_visits values (16, 8, 4, '2022-01-07');
insert into person_visits values (17, 9, 4, '2022-01-08');
insert into person_visits values (18, 9, 5, '2022-01-09');
insert into person_visits values (19, 9, 6, '2022-01-10');


create table menu
(id bigint primary key ,
 pizzeria_id bigint not null ,
 pizza_name varchar not null ,
 price numeric not null default 1,
 constraint fk_menu_pizzeria_id foreign key (pizzeria_id) references pizzeria(id));

insert into menu values (1,1,'cheese pizza', 900);
insert into menu values (2,1,'pepperoni pizza', 1200);
insert into menu values (3,1,'sausage pizza', 1200);
insert into menu values (4,1,'supreme pizza', 1200);

insert into menu values (5,6,'cheese pizza', 950);
insert into menu values (6,6,'pepperoni pizza', 800);
insert into menu values (7,6,'sausage pizza', 1000);

insert into menu values (8,2,'cheese pizza', 800);
insert into menu values (9,2,'mushroom pizza', 1100);

insert into menu values (10,3,'cheese pizza', 780);
insert into menu values (11,3,'supreme pizza', 850);

insert into menu values (12,4,'cheese pizza', 700);
insert into menu values (13,4,'mushroom pizza', 950);
insert into menu values (14,4,'pepperoni pizza', 1000);
insert into menu values (15,4,'sausage pizza', 950);

insert into menu values (16,5,'cheese pizza', 700);
insert into menu values (17,5,'pepperoni pizza', 800);
insert into menu values (18,5,'supreme pizza', 850);

create table person_order
(
    id bigint primary key ,
    person_id  bigint not null ,
    menu_id bigint not null ,
    order_date date not null default current_date,
    constraint fk_order_person_id foreign key (person_id) references person(id),
    constraint fk_order_menu_id foreign key (menu_id) references menu(id)
);

insert into person_order values (1,1, 1, '2022-01-01');
insert into person_order values (2,1, 2, '2022-01-01');

insert into person_order values (3,2, 8, '2022-01-01');
insert into person_order values (4,2, 9, '2022-01-01');

insert into person_order values (5,3, 16, '2022-01-04');

insert into person_order values (6,4, 16, '2022-01-07');
insert into person_order values (7,4, 17, '2022-01-07');
insert into person_order values (8,4, 18, '2022-01-07');
insert into person_order values (9,4, 6, '2022-01-08');
insert into person_order values (10,4, 7, '2022-01-08');

insert into person_order values (11,5, 6, '2022-01-09');
insert into person_order values (12,5, 7, '2022-01-09');

insert into person_order values (13,6, 13, '2022-01-01');

insert into person_order values (14,7, 3, '2022-01-03');
insert into person_order values (15,7, 9, '2022-01-05');
insert into person_order values (16,7, 4, '2022-01-05');

insert into person_order values (17,8, 8, '2022-01-06');
insert into person_order values (18,8, 14, '2022-01-07');

insert into person_order values (19,9, 18, '2022-01-09');
insert into person_order values (20,9, 6, '2022-01-10');

---------------------------- 07  --------------------

INSERT INTO menu VALUES (19, 2, 'greek pizza', 800);
SELECT * FROM menu WHERE pizza_name = 'greek pizza';

--

--

--
---------------------------- 08  --------------------

INSERT INTO menu VALUES
    ((SELECT MAX(id) + 1 FROM menu), 
    (SELECT id FROM pizzeria WHERE name = 'Dominos'),
    'sicilian pizza',
    900
    );
SELECT * FROM menu WHERE pizza_name = 'sicilian pizza';
--

--

--
---------------------------- 09  --------------------

INSERT INTO person_visits VALUES
    ((SELECT MAX(id) + 1 FROM person_visits), 
    (SELECT id FROM person WHERE name = 'Denis'),
    (SELECT id FROM pizzeria WHERE name = 'Dominos'),
    '2022-02-24'),

    ((SELECT MAX(id) + 2 FROM person_visits), 
    (SELECT id FROM person WHERE name = 'Irina'),
    (SELECT id FROM pizzeria WHERE name = 'Dominos'),
    '2022-02-24');

SELECT * FROM person_visits ORDER BY id DESC LIMIT 3;

--

--

--
---------------------------- 10  --------------------

INSERT INTO person_order (id, person_id, menu_id, order_date) VALUES
    ((SELECT MAX(id) + 1 from person_order),
    (SELECT id FROM person WHERE name = 'Denis'),
    (SELECT id FROM menu WHERE pizza_name = 'sicilian pizza'),
    '2022-02-24'),
    ((SELECT MAX(id) + 2 from person_order),
    (SELECT id FROM person WHERE name = 'Irina'),
    (SELECT id FROM menu WHERE pizza_name = 'sicilian pizza'),
    '2022-02-24');

SELECT po.id, person.name, menu.pizza_name, po.order_date FROM 
    (SELECT * FROM person_order ORDER BY id DESC LIMIT 3) po
JOIN
    person
ON po.person_id = person.id
JOIN
    menu
ON menu.id = po.menu_id
ORDER BY po.id;


--

--

--
---------------------------- 11  --------------------

UPDATE menu
SET price = 0.9 * price
WHERE pizza_name = 'greek pizza';

SELECT * FROM menu WHERE pizza_name = 'greek pizza';

--

--
---------------------------- 12  --------------------
INSERT INTO person_order(id, person_id, menu_id, order_date)
SELECT (GENERATE_SERIES(((SELECT MAX(id) FROM person_order) + 1),
                        ((SELECT MAX(id) FROM person_order) + (SELECT COUNT(*) FROM person)))),
       (GENERATE_SERIES((SELECT MIN(id) FROM person), (SELECT COUNT(*) FROM person))),
       (SELECT m.id FROM menu m WHERE m.pizza_name = 'greek pizza'),
       '2022-02-25';
--

SELECT * FROM person_order ORDER BY id DESC LIMIT (SELECT COUNT(*) FROM person);

SELECT * FROM person;

--

--
---------------------------- 13  --------------------
DELETE FROM person_order
WHERE order_date='2022-02-25';

DELETE FROM menu
WHERE pizza_name='greek pizza';
--

SELECT * FROM person_order WHERE order_date = '2022-02-25';
SELECT * FROM menu WHERE pizza_name='greek pizza';

--

--