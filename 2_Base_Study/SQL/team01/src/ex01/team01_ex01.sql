-- insert into currency values (100, 'EUR', 0.85, '2022-01-01 13:29');
-- insert into currency values (100, 'EUR', 0.79, '2022-01-08 13:29');


------------------------------------1---------------------------------

WITH past_c AS (SELECT user_id, money, currency_id, updated, MAX(c_updated) AS latest_update
                FROM (SELECT * FROM balance AS b 
                LEFT JOIN LATERAL (SELECT rate_to_usd, updated AS c_updated FROM currency 
                WHERE id = b.currency_id AND updated <= b.updated) AS c ON TRUE) AS past
                GROUP BY 1, 2, 3, 4),
future_c AS (SELECT user_id, money, currency_id, updated, MIN(c_updated) AS closest_update
            FROM (SELECT * FROM balance AS b 
            LEFT JOIN LATERAL (SELECT rate_to_usd, updated AS c_updated FROM currency 
            WHERE id = b.currency_id AND updated > b.updated) AS c ON TRUE) AS future
            GROUP BY 1, 2, 3, 4),
actual_update AS (SELECT user_id, money, currency_id, updated,
                        CASE 
                            WHEN latest_update IS NULL THEN closest_update
                            ELSE latest_update 
                        END AS actual_update FROM past_c NATURAL JOIN future_c)
SELECT CASE 
            WHEN "user".name IS NULL THEN 'not defined'
            ELSE "user".name
        END AS name,
        CASE 
            WHEN "user".lastname IS NULL THEN 'not defined'
            ELSE "user".lastname
        END AS lastname,
        currency.name AS currency_name,
        a.money * currency.rate_to_usd AS currency_in_usd
FROM actual_update a
LEFT JOIN "user" ON "user".id = a.user_id
LEFT JOIN currency ON a.currency_id = currency.id AND currency.updated = a.actual_update
WHERE currency.name IS NOT NULL
ORDER BY 1 DESC, 2 ASC, 3 ASC;

---------------------------------------2---------------------------------
WITH cur_cte AS (
        SELECT
            b.user_id AS bui,
            b.money,
            b.updated,
            c.name AS cur_name,
            c.rate_to_usd AS cur_rate,
            c.updated AS cur_updated
        FROM
            balance b
            JOIN currency c ON b.currency_id = c.id
    ),

all_join AS (
    SELECT
        q2.id,
        q2.cur_name,
        q2.money,
        q2.updated,
        COALESCE(q1.diff, q2.diff) new_diff
    FROM (
            SELECT
                cur_cte.bui AS id,
                cur_name,
                money,
                updated,
                MIN(updated - cur_updated) AS diff
            FROM
                cur_cte
            WHERE
                updated - cur_updated > INTERVAL '0 days'
            GROUP BY
                1,
                2,
                3,
                4
        ) q1
        FULL JOIN (
            SELECT
                cur_cte.bui AS id,
                cur_name,
                money,
                updated,
                MAX(updated - cur_updated) AS diff
            FROM
                cur_cte
            WHERE
                updated - cur_updated < INTERVAL '0 days'
            GROUP BY
                1,
                2,
                3,
                4
        ) q2 ON q1.id = q2.id
        AND q1.cur_name = q2.cur_name
        AND q1.money = q2.money
        AND q1.updated = q2.updated
)
SELECT
    COALESCE(u.name, 'not defined'),
    COALESCE(u.lastname, 'not defined'),
    aj.cur_name,
    aj.money * cu.rate_to_usd AS currency_in_usd
FROM all_join aj
    LEFT JOIN "user" u ON aj.id = u.id
    LEFT JOIN currency cu ON aj.new_diff = (aj.updated - cu.updated) AND aj.cur_name = cu.name
ORDER BY 1 DESC, 2 ASC, 3 ASC;

--------------------------------------3-------------------------------

select
    t1.name,
    t1.lastname,
    currency_name,
    money * rate_to_usd as currency_in_usd
from (
        select
            coalesce(u.name, 'not defined') as name,
            coalesce(u.lastname, 'not defined') as lastname,
            c.name as currency_name,
            money,
            coalesce( (
                    select rate_to_usd
                    from currency c
                    where
                        b.currency_id = c.id
                        and c.updated < b.updated
                    order by c.updated desc
                    limit 1
                ), (
                    select rate_to_usd
                    from currency c
                    where
                        b.currency_id = c.id
                        and c.updated > b.updated
                    order by c.updated asc
                    limit 1
                )
            ) as rate_to_usd
        from balance b
            inner join (
                select c.id, c.name
                from currency c
                group by
                    c.id,
                    c.name
            ) as c on c.id = b.currency_id
            left join "user" u on u.id = b.user_id
    ) as t1
order by 1 desc, 2, 3

-- CREATE OR REPLACE FUNCTION CHECK_PAST_DATE(CUR_DATE TIMESTAMP, CUR_ID INTEGER) RETURNS TABLE(CURR_NAME VARCHAR, RATE_TO_USD_MY NUMERIC) AS $$ 
-- 	$$
-- 	    BEGIN
-- 	        RETURN QUERY
-- 	            SELECT name, rate_to_usd
-- 	            FROM (SELECT MAX(currency.updated) AS max_dt
-- 	                  FROM currency
-- 	                  WHERE cur_id = currency.id AND currency.updated <= cur_date
-- 	                  GROUP BY name) AS max_date
-- 	           JOIN currency ON max_date.max_dt = currency.updated;
-- 	END;
-- 	$$ LANGUAGE plpgsql;


-- CREATE OR REPLACE FUNCTION CHECK_FUTURE_DATE(CUR_DATE 
-- TIMESTAMP, CUR_ID INTEGER) RETURNS TABLE(CURR_NAME 
-- VARCHAR, RATE_TO_USD_MY NUMERIC) AS $$ 
-- 	$$
-- 	    BEGIN
-- 	        RETURN QUERY
-- 	            SELECT name, rate_to_usd
-- 	            FROM (SELECT MIN(currency.updated) AS min_dt, name AS min_name
-- 	                  FROM currency
-- 	                  WHERE cur_id = currency.id AND currency.updated > cur_date
-- 	                  GROUP BY name) AS min_date
-- 	           JOIN currency ON min_date.min_dt = currency.updated AND min_date.min_name = currency.name;
-- 	END;
-- 	$$ LANGUAGE plpgsql;

-- SELECT
--     COALESCE(name, 'not defined') AS name,
--     COALESCE(lastname, 'not defined') AS lastname, (
--         CASE
--             WHEN (
--                 SELECT COUNT(*)
--                 FROM
--                     check_past_date(updated, currency_id)
--             ) = 1 THEN (
--                 SELECT curr_name
--                 FROM
--                     check_past_date(updated, currency_id)
--             )
--             ELSE (
--                 SELECT curr_name
--                 FROM
--                     check_future_date(updated, currency_id)
--             )
--         END
--     ) AS currency_name, ( (
--             CASE
--                 WHEN (
--                     SELECT COUNT(*)
--                     FROM
--                         check_past_date(updated, currency_id)
--                 ) = 1 THEN (
--                     SELECT rate_to_usd_my
--                     FROM
--                         check_past_date(updated, currency_id)
--                 )
--                 ELSE (
--                     SELECT rate_to_usd_my
--                     FROM
--                         check_future_date(updated, currency_id)
--                 )
--             END
--         ) * balance.money
--     ) AS currency_in_usd
-- FROM "user"
--     FULL JOIN balance ON "user".id = balance.user_id
-- WHERE currency_id IN (
--         SELECT id
--         FROM currency
--     )
-- ORDER BY
--     name DESC,
--     lastname ASC,
--     currency_name ASC;