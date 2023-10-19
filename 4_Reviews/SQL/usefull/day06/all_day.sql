drop table if exists person_visits;
drop table if exists person_order;
drop table if exists person_discounts;
drop table if exists menu;
drop table if exists pizzeria;
drop table if exists person;

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


select * from person;

drop table if exists person_discounts;
CREATE TABLE IF NOT EXISTS person_discounts (
    id BIGINT PRIMARY KEY,
    person_id  BIGINT,
    pizzeria_id BIGINT,
    discount NUMERIC,
    CONSTRAINT fk_person_discounts_person_id FOREIGN KEY(person_id) REFERENCES person(id),
    CONSTRAINT fk_person_discounts_pizzeria_id FOREIGN KEY(pizzeria_id) REFERENCES pizzeria(id)
);

WITH subq AS (
    SELECT 
        person_id, pizzeria_id, count(pizzeria_id) as amount_of_orders
    FROM 
        person_order
    JOIN
        menu
    ON person_order.menu_id = menu.id
    GROUP BY person_id, pizzeria_id)
INSERT INTO person_discounts(id, person_id, pizzeria_id, discount)
    SELECT  ROW_NUMBER() OVER() as id,
            person_id,
            pizzeria_id,
            CASE
                WHEN amount_of_orders = 1 THEN 10.5
                WHEN amount_of_orders = 2 THEN 22
                ELSE 30
            END AS discount
FROM subq;

SELECT * FROM person_discounts;

drop table if exists person_discounts;

CREATE TABLE IF NOT EXISTS person_discounts (
    id BIGINT PRIMARY KEY,
    person_id  BIGINT NOT NULL,
    pizzeria_id BIGINT NOT NULL,
    discount NUMERIC,
    CONSTRAINT fk_person_discounts_person_id FOREIGN KEY(person_id) REFERENCES person(id),
    CONSTRAINT fk_person_discounts_pizzeria_id FOREIGN KEY(pizzeria_id) REFERENCES pizzeria(id)
);

insert into person_discounts (id, person_id, pizzeria_id, discount)
select
row_number() over () as id,
person_id,
m.pizzeria_id,
case
when count(*) = 1 then 10.5
when count(*) = 2 then 22
else 30
end as discount
from person_order inner join menu m on m.id = person_order.menu_id
group by person_id, m.pizzeria_id;

SELECT * FROM person_discounts;

-- 02

SELECT 
    person.name, menu.pizza_name, menu.price, ROUND((1 - person_discounts.discount / 100) * price, 2) AS discount_price, pizzeria.name as pizzeria_name 
FROM
    person_order INNER JOIN person ON person_order.person_id = person.id
INNER JOIN
    menu ON person_order.menu_id = menu.id
INNER JOIN
    person_discounts ON person_discounts.person_id = person.id and person_discounts.pizzeria_id = menu.pizzeria_id
INNER JOIN 
    pizzeria ON person_discounts.pizzeria_id = pizzeria.id
ORDER BY name, pizza_name;


select p.name, m.pizza_name, m.price, (m.price - (m.price * pd.discount/100) ) as discount_price, p2.name as pizzeria_name
from person_order 
inner join menu m on m.id = person_order.menu_id
inner join person p on p.id = person_order.person_id
inner join person_discounts pd on p.id = pd.person_id and pd.pizzeria_id = m.pizzeria_id
inner join pizzeria p2 on m.pizzeria_id = p2.id
order by 1,2


--03

CREATE UNIQUE INDEX idx_person_discounts_unique ON person_discounts(person_id, pizzeria_id);

SET ENABLE_SEQSCAN = OFF;
EXPLAIN ANALYSE
SELECT * FROM person_discounts WHERE person_id = 1 AND pizzeria_id = 1

-- 04

ALTER TABLE person_discounts ADD CONSTRAINT ch_nn_person_id CHECK(person_id IS NOT NULL);
ALTER TABLE person_discounts ADD CONSTRAINT ch_nn_pizzeria_id CHECK(pizzeria_id IS NOT NULL);
ALTER TABLE person_discounts ADD CONSTRAINT ch_nn_discount CHECK(discount IS NOT NULL);
ALTER TABLE person_discounts ALTER COLUMN discount SET DEFAULT 0;
ALTER TABLE person_discounts ADD CONSTRAINT ch_range_discount CHECK(discount BETWEEN 0 AND 100);

select count(*) = 4 as check
from pg_constraint
where conname in ('ch_nn_person_id','ch_nn_pizzeria_id','ch_nn_discount','ch_range_discount')

select column_default::integer = 0 as check
from information_schema.columns
where column_name = 'discount' and table_name = 'person_discounts'

--05

COMMENT ON TABLE person_discounts is 'table for calc person discounts';
COMMENT ON COLUMN person_discounts.id  is 'identifier for row' ;
COMMENT ON COLUMN person_discounts.person_id  is 'identifier for person' ;
COMMENT ON COLUMN person_discounts.pizzeria_id  is 'identifier for pizzeria';
COMMENT ON COLUMN person_discounts.discount  is 'discount value';

SELECT count(*) = 5 as check
FROM pg_description
WHERE objoid = 'person_discounts'::regclass


DROP SEQUENCE  if EXISTS seq_person_discounts;
CREATE SEQUENCE seq_person_discounts START 25;

select * from seq_person_discounts;

SELECT SETVAL('seq_person_discounts', max(id)) FROM person_discounts;

ALTER TABLE person_discounts ALTER COLUMN id SET DEFAULT NEXTVAL('seq_person_discounts');

INSERT INTO person_discounts (person_id, pizzeria_id, discount) values (7,5,2);

select * from person_discounts;