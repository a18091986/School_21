-- Active: 1698411269832@@46.8.219.63@5432@pizza
WITH
	group_in_balance AS (
		SELECT
			COALESCE(u.name, 'not defined') AS name,
			COALESCE(u.lastname, 'not defined') AS lastname,
			type,
			SUM(b.money) AS volume,
			b.currency_id
		FROM balance b
			LEFT JOIN public."user" u ON u.id = b.user_id
		GROUP BY u.name, u.lastname, type, b.currency_id
		ORDER BY u.name DESC NULLS LAST)
		
SELECT 
	g.name,
	g.lastname,
	g.type,
	g.volume,
	COALESCE(c.name, 'not defined') AS currency_name,
	COALESCE(c.rate_to_usd, 1) AS last_rate_to_usd,
	(volume * COALESCE(c.rate_to_usd, 1))::integer AS total_volume_in_usd
FROM group_in_balance g
	LEFT JOIN currency c ON c.id = g.currency_id AND
		c.updated = (SELECT MAX(updated) FROM currency WHERE currency.id = g.currency_id)
ORDER BY g.name DESC NULLS LAST, g.lastname, g.type;
