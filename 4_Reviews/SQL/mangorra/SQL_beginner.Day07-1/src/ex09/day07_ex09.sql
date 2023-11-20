SELECT address, round(MAX(age::numeric) - (MIN(age::numeric) / MAX(age::numeric)),2) AS formula, 
				round(AVG(age),2) AS average, 
		        (MAX(age) - (MIN(age) / MAX(age))) > AVG(age) AS comparison
FROM person p
GROUP BY 1
ORDER BY 1;