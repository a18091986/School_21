SELECT prs.name, COUNT(pv.id) AS count_of_visits
FROM person_visits pv
JOIN person prs ON prs.id = pv.person_id
GROUP BY prs.name
ORDER BY 2 DESC, 1 ASC
LIMIT 4;