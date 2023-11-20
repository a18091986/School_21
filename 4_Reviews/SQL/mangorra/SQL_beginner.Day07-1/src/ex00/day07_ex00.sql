-- Active: 1699227231092@@46.8.219.63@5432@pizza
SELECT person_id, COUNT(id) AS count_of_visits
FROM person_visits pv
GROUP BY person_id
ORDER BY 2 DESC, 1 ASC;