-- Exercise 00: Classical TSP	
-- Turn-in directory	ex00
-- Files to turn-in	team00_ex00.sql DDL for table creation with INSERTs of data; SQL DML statement
-- Allowed	
-- Language	ANSI SQL
-- SQL Syntax Pattern	Recursive Query

-- Please take a look at the Graph on the left. There are 4 cities (a, b, c and d) and arcs between them with cost (or taxination). Actually the cost (a,b) = (b,a).

-- Please create a table with name nodes by using structure {point1, point2, cost} and fill data based on a picture (remember there are direct and reverse paths between 2 nodes). Please write one SQL statement that returns all tours (aka paths) with minimal traveling cost if we will start from city "a". Just remember, you need to find the cheapest way of visiting all the cities and returning to your starting point. For example, the tour looks like that a -> b -> c -> d -> a.

-- The sample of output data you can find below. Please sort data by total_cost and then by tour.

-- total_cost	tour
-- 80	{a,b,d,c,a}
-- ...	...

DROP TABLE IF EXISTS nodes;

CREATE TABLE nodes (
    point_1 VARCHAR, 
    point_2 VARCHAR,
    cost INTEGER
);

INSERT INTO
    nodes
VALUES
    ('a', 'b', 10), ('b', 'a', 10), ('a', 'd', 20), ('d', 'a', 20), ('a', 'c', 15), ('c', 'a', 15), ('b', 'd', 25), ('d', 'b', 25), ('b', 'c', 35), ('c', 'b', 35), ('c', 'd', 30), ('d', 'c', 30);

-- стартовая точка
-- отбираем точки 'a' из таблицы nodes

-- WITH RECURSIVE routes(tour, p1, p2, total_cost) AS (
--     SELECT point_1 AS tour, 
--     point_1 p1, point_2 p2, cost
--     FROM nodes
--     WHERE point_1 = 'a'
-- )
-- SELECT * FROM routes;

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

-- WITH RECURSIVE trip(tour, p1, p2, total_cost) AS (
--     SELECT 
--         point_1 AS tour, point_1 AS p1, point_2 AS p2, cost
--     FROM 
--         nodes
--     WHERE 
--         point_1 = 'a'
--     UNION ALL
--     SELECT
--         CONCAT(tour, ',', p2), p2, point_2, total_cost + cost
--     FROM 
--         nodes JOIN trip
--     ON p2 = point_1 
--     WHERE tour NOT LIKE '%' || point_1 || '%'
-- )
-- SELECT * FROM trip;

-- теперь просто из полученной таблицы выбираем пути с минимальной ценой

WITH RECURSIVE trip(tour, p1, p2, total_cost) AS (
    SELECT 
        point_1 AS tour, point_1 AS p1, point_2 AS p2, cost
    FROM 
        nodes
    WHERE 
        point_1 = 'a'
    UNION ALL
    SELECT
        CONCAT(tour, ',', p2), p2, point_2, total_cost + cost
    FROM 
        nodes JOIN trip
    ON p2 = point_1 
    WHERE tour NOT LIKE '%' || point_1 || '%'
)
SELECT total_cost, CONCAT('{', tour, ',a') tour FROM trip
WHERE 
    LENGTH(tour) = 7 
AND 
    p2 = 'a' 
AND 
    total_cost = (SELECT min(total_cost) FROM trip WHERE LENGTH(tour) = 7 AND p2 = 'a')
order by total_cost, tour;