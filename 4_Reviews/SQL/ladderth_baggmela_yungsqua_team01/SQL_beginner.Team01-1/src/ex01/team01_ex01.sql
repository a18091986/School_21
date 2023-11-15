insert into currency values (100, 'EUR', 0.85, '2022-01-01 13:29');
insert into currency values (100, 'EUR', 0.79, '2022-01-08 13:29');

CREATE OR REPLACE FUNCTION find_rate_usd(pupdated timestamp without time zone,
										pcurrency_name varchar)
	RETURNS NUMERIC AS $$
		WITH
			ch_past AS (
				SELECT *
				FROM currency
				WHERE name = pcurrency_name AND updated < pupdated
				ORDER BY updated DESC
				LIMIT 1),
			ch_future AS (
				SELECT *
				FROM currency
				WHERE name = pcurrency_name AND updated > pupdated
				ORDER BY updated ASC
				LIMIT 1)
		SELECT
			CASE WHEN (SELECT COUNT(*) FROM ch_past) = 0 THEN (SELECT rate_to_usd FROM ch_future)
				ELSE (SELECT rate_to_usd FROM ch_past)
			END
$$ LANGUAGE SQL;

WITH
	uniq_currency AS (
		SELECT DISTINCT(id), name
		FROM currency)
SELECT
	COALESCE(u.name, 'not defined') AS name,
	COALESCE(u.lastname, 'not defined') AS lastname,
	c.name AS currency_name,
	round(find_rate_usd(b.updated, c.name) * money, 1) AS currency_in_usd
FROM balance b
	LEFT JOIN public."user" u ON u.id = b.user_id
	JOIN uniq_currency c ON c.id = b.currency_id
ORDER BY name DESC, lastname, c.name;
