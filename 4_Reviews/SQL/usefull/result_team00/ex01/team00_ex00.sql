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
UNION
select total_cost, concat('{', tour, ',a') tour from trip
where 
    length(tour) = 7 
and 
    p2 = 'a' 
and 
    total_cost = (select max(total_cost) from trip where length(tour) = 7 and p2 = 'a')
order by total_cost, tour;