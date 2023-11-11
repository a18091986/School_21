-- Please write a SQL statement that returns all Users, all Balance transactions (in this task please ignore currencies that  do not have a key in the Currency table)
-- with currency name and calculated value of currency in USD for the nearest day.

-- insert into currency values (100, 'EUR', 0.85, '2022-01-01 13:29');
-- insert into currency values (100, 'EUR', 0.79, '2022-01-08 13:29');

WITH rate_date AS (
        SELECT user_id, money, rate_to_usd, currency.name currency_name ,
               row_number() over (partition by balance
               order by ( balance.updated :: date >= currency.updated :: date) DESC,
                          abs(balance.updated :: date - currency.updated :: date)) days_between
        FROM balance JOIN currency on currency.id = balance.currency_id)
SELECT
    coalesce("user".name, 'not defined') AS name,
    coalesce("user".lastname, 'not defined') AS lastname,
    currency_name, money * rate_date.rate_to_usd currency_in_usd
FROM rate_date FULL JOIN "user" on rate_date.user_id = "user".id
WHERE days_between = 1
ORDER BY 1 desc, 2, 3;