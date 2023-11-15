-- Active: 1698411269832@@46.8.219.63@5432@pizza_mart
SELECT 
    address,
    ROUND(MAX(age) - MIN(age)::NUMERIC / MAX(age), 2) AS formula,
    ROUND(AVG(age), 2) AS average,
    MAX(age) - MIN(age)::NUMERIC / MAX(age) > AVG(age) AS comparison
FROM person
GROUP BY address
ORDER BY address;

select * from person;

