-- 00

SELECT
  person_id,
  COUNT(visit_date) AS count_of_visits
FROM
  person_visits
GROUP BY
  person_id
ORDER BY
  count_of_visits DESC,
  person_id;

SELECT person_id, COUNT(*) AS count_of_visits
FROM person_visits
GROUP BY person_id
ORDER BY count_of_visits DESC, person_id;

-- 01
SELECT
  p.name,
  COUNT(pv.visit_date) AS count_of_visits
FROM
  person p
  INNER JOIN person_visits pv ON pv.person_id = p.id
GROUP BY
  p.name
ORDER BY
  count_of_visits DESC,
  p.name FETCH FIRST 4 ROWS ONLY;


SELECT name, COUNT(*) AS count_of_visits
FROM 
    person_visits
JOIN
    person
on person.id = person_visits.person_id
GROUP BY name
ORDER BY count_of_visits DESC, name
LIMIT 4;
-- 02
(
  SELECT
    name,
    COUNT(*) as count,
    'order' AS action_type
  FROM
    person_order po
    JOIN menu m ON m.id = po.menu_id
    JOIN pizzeria pz ON pz.id = m.pizzeria_id
  GROUP BY
    name
  ORDER BY
    count DESC FETCH FIRST 3 ROWS ONLY
)
UNION ALL
  (
    SELECT
      name,
      COUNT(*) as count,
      'visit' AS action_type
    FROM
      person_visits pv
      JOIN pizzeria pz ON pz.id = pv.pizzeria_id
    GROUP BY
      name
    ORDER BY
      count DESC FETCH FIRST 3 ROWS ONLY
  )
ORDER BY
  action_type,
  count DESC;

(SELECT name, COUNT(*) AS count, 'order' AS action_type
FROM pizzeria
JOIN menu
ON pizzeria.id = menu.pizzeria_id
JOIN person_order
ON person_order.menu_id = menu.id
GROUP BY name
ORDER BY count DESC
LIMIT 3)
UNION 
(SELECT name, COUNT(*) AS count, 'visit' AS action_type
FROM pizzeria
JOIN person_visits
ON person_visits.pizzeria_id = pizzeria.id
GROUP BY name
ORDER BY count DESC
LIMIT 3)
ORDER BY action_type, count DESC;
-- 03

WITH o_order AS (
  SELECT
    name,
    COUNT(*) AS count
  FROM
    person_order po
    JOIN menu m ON m.id = po.menu_id
    JOIN pizzeria pz ON pz.id = m.pizzeria_id
  GROUP BY
    name
  ORDER BY
    count DESC
),
v_visit AS (
  SELECT
    name,
    COUNT(*) as count
  FROM
    person_visits pv
    JOIN pizzeria pz ON pz.id = pv.pizzeria_id
  GROUP BY
    name
  ORDER BY
    count DESC
)
SELECT
  pz.name,
  (
    CASE WHEN v.count IS NULL THEN 0 ELSE v.count END
  ) + (
    CASE WHEN o.count IS NULL THEN 0 ELSE o.count END
  ) AS total_count
FROM
  pizzeria pz
  LEFT JOIN v_visit v ON v.name = pz.name
  LEFT JOIN o_order o ON o.name = v.name
ORDER BY
  total_count DESC,
  name;

WITH 
    orders AS 
        (SELECT name, COUNT(*) AS count
         FROM pizzeria
         JOIN menu
         ON pizzeria.id = menu.pizzeria_id
         JOIN person_order
         ON person_order.menu_id = menu.id
         GROUP BY name
         ORDER BY count DESC),
    visits AS 
        (SELECT name, COUNT(*) AS count
        FROM pizzeria
        JOIN person_visits
        ON person_visits.pizzeria_id = pizzeria.id
        GROUP BY name
        ORDER BY count DESC)
SELECT pizzeria.name, 
       COALESCE(orders.count, 0) + COALESCE(visits.count, 0) as total_count
FROM pizzeria
LEFT JOIN visits
ON pizzeria.name = visits.name
LEFT JOIN orders
ON pizzeria.name = orders.name
ORDER BY total_count DESC, name;


SELECT name, SUM(count) AS total_count
FROM ((SELECT pizzeria_id, COUNT(*) AS count
       FROM person_visits
       GROUP BY pizzeria_id)
       UNION ALL
      (SELECT pizzeria_id, COUNT(*) AS count
       FROM person_order
       JOIN menu ON person_order.menu_id = menu.id
       GROUP BY pizzeria_id)) AS new_table
FULL JOIN pizzeria ON new_table.pizzeria_id = pizzeria.id
GROUP BY name
ORDER BY total_count DESC, name ASC;

SELECT q.name, SUM(q.total_count) AS total_count
FROM ((SELECT pi.name,
              COUNT(pizzeria_id) AS total_count
       FROM person_visits AS pv
                JOIN pizzeria pi ON pv.pizzeria_id = pi.id
       GROUP BY 1
       ORDER BY 2 DESC)
      UNION ALL
      (SELECT pi.name,
              COUNT(pi.name) AS total_count
       FROM person_order po
                JOIN menu m ON po.menu_id = m.id
                JOIN pizzeria pi ON m.pizzeria_id = pi.id
       GROUP BY 1
       ORDER BY 2 DESC)) q
GROUP BY q.name
ORDER BY 2 DESC, 1 ASC;

-- 04
SELECT name, COUNT(*) AS count_of_visits
FROM person
JOIN person_visits
ON person.id = person_visits.person_id
GROUP BY name
HAVING COUNT(*) > 3;


SELECT
  p.name,
  COUNT(visit_date) AS count_of_visits
FROM
  person p
  JOIN person_visits pv ON p.id = pv.person_id
GROUP BY
  p.name
HAVING
  COUNT(visit_date) > 3;
-- 05
SELECT DISTINCT name FROM
    person
JOIN
    person_order
ON person.id = person_order.person_id
ORDER BY name;

SELECT
  DISTINCT p.name
FROM
  person p
  JOIN person_order po ON po.person_id = p.id
ORDER BY
  p.name;
-- 06
SELECT
    name, COUNT(*) AS count_of_orders, 
    ROUND(AVG(price), 2), 
    MAX(price) as max_price, MIN(price) as min_price
FROM
    pizzeria
JOIN
    menu
ON pizzeria.id = menu.pizzeria_id
JOIN
    person_order
ON person_order.menu_id = menu.id
GROUP BY name
ORDER BY name

SELECT
  pz.name,
  COUNT(order_date) AS count_of_orders,
  ROUND(
    avg(price),
    2
  ) AS average_price,
  max(price) AS max_price,
  min(price) AS min_price
FROM
  pizzeria pz
  JOIN menu m on pz.id = m.pizzeria_id
  JOIN person_order pv ON m.id = pv.menu_id
GROUP BY
  pz.name
ORDER BY
  pz.name;
-- 07
SELECT ROUND(AVG(rating), 4) global_rating FROM pizzeria;
-- 08
SELECT address, pizzeria.name name, COUNT(*) as count_of_orders
FROM person
JOIN person_order ON person.id = person_order.person_id
JOIN menu ON person_order.menu_id = menu.id
JOIN pizzeria ON pizzeria.id = menu.pizzeria_id
GROUP BY address, pizzeria.name
ORDER BY 1, 2;

SELECT
  p.address,
  pz.name,
  COUNT(order_date) AS count_of_orders
FROM
  person p
  JOIN person_order po ON p.id = po.person_id
  JOIN menu m ON m.id = po.menu_id
  JOIN pizzeria pz ON pz.id = m.pizzeria_id
GROUP BY
  p.address,
  pz.name
ORDER BY
  p.address,
  pz.name;
-- 09

SELECT 
    address,
    ROUND(MAX(age) - MIN(age)::NUMERIC / MAX(age), 2) AS formula,
    ROUND(AVG(age), 2) AS average,
    MAX(age) - MIN(age)::NUMERIC / MAX(age) > AVG(age) AS comparison
FROM person
GROUP BY address
ORDER BY address;


WITH tmp AS (
  SELECT
    address,
    ROUND(
      CAST(
        max(age) AS NUMERIC
      ) - CAST(
        min(age) AS NUMERIC
      ) / CAST(
        max(age) AS NUMERIC
      ),
      2
    ) AS formula,
    ROUND(
      avg(age),
      2
    ) AS avarage
  FROM
    person
  GROUP BY
    address
)
SELECT
  *,
  (formula > avarage) AS comparison
FROM
  tmp
ORDER BY
  address;