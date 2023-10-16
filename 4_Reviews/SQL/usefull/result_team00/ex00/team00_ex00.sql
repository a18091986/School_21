drop table if exists nodes;

create table nodes (
    point_1 varchar, 
    point_2 varchar,
    cost integer
);

insert into nodes
values ('a', 'b', 10);
insert into nodes
values ('b', 'a', 10);
insert into nodes
values ('a', 'd', 20);
insert into nodes
values ('d', 'a', 20);
insert into nodes
values ('a', 'c', 15);
insert into nodes
values ('c', 'a', 15);
insert into nodes
values ('b', 'd', 25);
insert into nodes
values ('d', 'b', 25);
insert into nodes
values ('b', 'c', 35);
insert into nodes
values ('c', 'b', 35);
insert into nodes
values ('c', 'd', 30);
insert into nodes
values ('d', 'c', 30);

-- стартовая точка
-- отбираем точки 'a' из таблицы nodes

-- with recursive routes(tour, p1, p2, total_cost) as (
--     select point_1 as tour, 
--     point_1 p1, point_2 p2, cost
--     from nodes
--     where point_1 = 'a'
-- )
-- select * from routes;

-- стартовая таблица:
-- tour   p1    p2     total_cost
--  a     a     b          10
--  a     a     d          20
--  a     a     c          15

-- далее добавляем собственно рекурсивную часть
-- нам нужно на каждом шаге рекурсии: 
-- 1. к tour из предыдущего шага прибавлять p2 
-- 2. в столбец p1 написать p2 из предыдущего шага
-- 3. получать новые p2
-- 4. в total cost класть сумму нового шага и предыдущих

-- UNION - просто вертикально стыкует всю таблицу полученную
-- на предыдущем шаге с новой таблицей

-- join - для того, чтобы выбрать из nodes строки подходящие для продолжения маршрута (чтобы не было маршрута а-а например), а конструкция like - для того, чтобы отсечь в получившейся после join таблице те строки, которые предлагают пойти в точку, которая уже есть в tour

-- with recursive trip(tour, p1, p2, total_cost) as (
--     select 
--         point_1 as tour, point_1 as p1, point_2 as p2, cost
--     from 
--         nodes
--     where 
--         point_1 = 'a'
--     UNION ALL
--     SELECT
--         concat(tour, ',', p2), p2, point_2, total_cost + cost
--     FROM 
--         nodes JOIN trip
--     ON p2 = point_1 
--     WHERE tour not like '%' || point_1 || '%'
-- )
-- select * from trip;

-- теперь просто из полученной таблицы выбираем пути с минимальной ценой

with recursive trip(tour, p1, p2, total_cost) as (
    select 
        point_1 as tour, point_1 as p1, point_2 as p2, cost
    from 
        nodes
    where 
        point_1 = 'a'
    UNION ALL
    SELECT
        concat(tour, ',', p2), p2, point_2, total_cost + cost
    FROM 
        nodes JOIN trip
    ON p2 = point_1 
    WHERE tour not like '%' || point_1 || '%'
)
select total_cost, concat('{', tour, ',a') tour from trip
where 
    length(tour) = 7 
and 
    p2 = 'a' 
and 
    total_cost = (select min(total_cost) from trip where length(tour) = 7 and p2 = 'a')
order by total_cost, tour;