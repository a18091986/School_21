-- Please write a SQL statement that returns the total volume (sum of all money) of transactions
-- from user balance aggregated by user and balance type.Please be aware, all data should be processed including data with
-- anomalies.Below presented a table of result columns and corresponding calculation formula 

WITH
    uv AS (
        -- получаем таблицу пользователь - траты
        -- full join потому что данные не консистентны
        SELECT name, lastname, type, SUM(money) AS volume, currency_id
        FROM "user" FULL JOIN balance ON "user".id = balance.user_id
        GROUP BY type, name, lastname, currency_id),
    uvc AS (
        -- получаем пользователь - траты - валюта
        SELECT uv.name, lastname, type, volume, currency.name AS currency_name, currency_id
        FROM uv LEFT JOIN currency ON currency.id = uv.currency_id
        GROUP BY uv.name, lastname, type, volume, currency.name, uv.currency_id),
    rtc AS (
        -- получаем курсы обмена
        SELECT currency.id, name, rate_to_usd, date_for_rate
        FROM (SELECT id, MAX(updated) AS date_for_rate FROM currency GROUP BY id) t
        LEFT JOIN currency ON t.date_for_rate  = currency.updated AND t.id = currency.id
    )
SELECT
    COALESCE(uvc.name, 'not defined') AS name, 
    COALESCE(lastname, 'not defined')  AS lastname, 
    type, volume, 
    COALESCE(currency_name, 'not defined') AS currency_name, 
    COALESCE(rate_to_usd, 1) AS last_rate_to_usd,
    COALESCE(volume * rate_to_usd, volume) AS total_volume_in_usd
FROM uvc
    LEFT JOIN rtc ON rtc.id = uvc.currency_id
ORDER BY 1 DESC, 2, 3;


