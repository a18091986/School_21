WITH more_three AS (SELECT prs.name, COUNT(pv.id) as count_of_visits, COUNT(pv.id) > 3 as check
					FROM person_visits pv
					JOIN person prs ON prs.id = pv.person_id
					GROUP BY prs.name),
					
mask AS (SELECT TRUE AS check)
SELECT name, count_of_visits
FROM more_three mt
JOIN mask ON mt.check = mask.check;