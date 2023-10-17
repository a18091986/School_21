-- Exercise 01: Opposite TSP	
-- Turn-in directory	ex01
-- Files to turn-in	team00_ex01.sql SQL DML statement
-- Allowed	
-- Language	ANSI SQL
-- SQL Syntax Pattern	RECURSIVE Query

-- Please add a possibility to see additional rows WITH the most expensive cost to the SQL FROM previous exercise. Just take a look at the sample of data below. Please sort data by total_cost AND then by tour.

-- total_cost	tour
-- 80	{a,b,d,c,a}
-- ...	...
-- 95	{a,d,c,b,a}

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
UNION
SELECT total_cost, CONCAT('{', tour, ',a') tour FROM trip
WHERE 
    LENGTH(tour) = 7 
AND 
    p2 = 'a' 
AND 
    total_cost = (SELECT max(total_cost) FROM trip WHERE LENGTH(tour) = 7 AND p2 = 'a')
ORDER BY total_cost, tour;