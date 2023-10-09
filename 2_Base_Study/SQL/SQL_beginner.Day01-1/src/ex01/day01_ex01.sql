-- Please make a select statement which returns names , ages for all women from the city ‘Kazan’. Yep, and please sort result by name.

(SELECT name AS object_name FROM person ORDER BY object_name)
UNION ALL
(SELECT pizza_name AS object_name FROM menu ORDER BY object_name);
