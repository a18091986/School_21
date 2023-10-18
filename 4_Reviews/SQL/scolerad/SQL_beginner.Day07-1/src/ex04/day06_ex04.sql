SELECT person.name, COUNT(pizzeria_id) AS count_of_visits
FROM person_visits INNER JOIN person ON person.id = person_visits.person_id
GROUP BY person_visits.person_id, person.name
HAVING COUNT(pizzeria_id) > 3;