-- Active: 1698411269832@@46.8.219.63@5432@pizza
-- WITH user_a AS (
--     SELECT 
--         id,
--         CASE
--             WHEN "user".name IS NULL THEN 'not defined'
--             ELSE "user".name
--         END,
--         CASE
--             WHEN "user".lastname IS NULL THEN 'not defined'
--             ELSE "user".lastname
--         END
--     FROM "user"),
--     currency_a AS ( 
--     SELECT id, max(updated) AS updated, name
--     FROM currency
--     GROUP BY id, name)
-- SELECT user_a.name, user_a.lastname, balance.type, sum(balance.money) AS volume, 
--     CASE
--         WHEN currency_a.name IS NULL THEN 'not defined'
--         ELSE currency_a.name
--     END currency_name,
--     CASE
--         WHEN currency.rate_to_usd IS NULL THEN 1::numeric
--         ELSE currency.rate_to_usd
--     END last_rate_to_usd,
--     CASE
--         WHEN currency.rate_to_usd IS NULL THEN sum(balance.money * 1)
--         ELSE sum(balance.money * rate_to_usd)
--     END total_volume_in_usd
-- FROM user_a
-- LEFT JOIN balance ON user_a.id = balance.user_id
-- LEFT JOIN currency_a ON currency_a.id = balance.currency_id
-- LEFT JOIN currency ON currency.updated = currency_a.updated AND currency.id = currency_a.id
-- GROUP BY user_a.name, user_a.lastname, balance.type, currency_name, rate_to_usd
-- ORDER BY user_a.name DESC;

-- WITH c AS (
--         SELECT *
--         FROM currency
--         WHERE updated IN (
--                 SELECT
--                     max(updated)
--                 FROM currency
--                 GROUP BY
--                     id
--             )
--     ),
--     n_t AS (
--         SELECT
--             DISTINCT COALESCE(u.name, 'not defined') AS name,
--             COALESCE(u.lastname, 'not defined') AS lastname,
--             b.type,
--             SUM(b.money) OVER (PARTITION BY u.id, b.type) AS volume,
--             CASE
--                 WHEN COUNT(c.name) OVER (PARTITION BY u.id, b.type) = 1 THEN c.name
--                 ELSE 'not defined'
--             END AS currency_name,
--             CASE
--                 WHEN COUNT(c.rate_to_usd) OVER (PARTITION BY u.id, b.type) = 1 THEN c.rate_to_usd
--                 ELSE '1'
--             END AS last_rate_to_usd
--         FROM balance b
--             LEFT JOIN "user" u ON b.user_id = u.id
--             LEFT JOIN c ON b.currency_id = c.id
--     )
-- SELECT
--     *,
--     volume * last_rate_to_usd :: float AS total_volume_in_usd
-- FROM n_t
-- ORDER BY name DESC, lastname, type

----------------------------------------1--------------------------

select * from currency;
select * from "user";
select * from balance;
WITH t1 AS ( 
SELECT
    id AS t1_id,
    name AS t1_name,
    MAX(updated) AS t1_updated
FROM currency
GROUP BY id, name
), t2 AS (
    SELECT
        DISTINCT id,
        name AS currency_name,
        rate_to_usd
    FROM currency
        JOIN t1 ON currency.updated = t1.t1_updated
), t3 AS (
    SELECT
        name,
        lastname,
        type,
        SUM(money) AS summ,
        currency_id
    FROM "user"
        FULL JOIN balance ON "user".id = balance.user_id
    GROUP BY
        name,
        lastname,
        type,
        currency_id
),
t4 AS (
    SELECT
        name,
        lastname,
        type,
        summ AS volume,
        currency_name, (
            CASE
                WHEN rate_to_usd ISNULL THEN 1
                ELSE rate_to_usd
            END
        ) AS last_rate_to_usd
    FROM t3
        FULL JOIN t2 ON t2.id = t3.currency_id
    ORDER BY
        name DESC,
        lastname ASC,
        type ASC
)
SELECT
    COALESCE(name, 'not defined') AS name,
    COALESCE(lastname, 'not defined') AS lastname,
    type,
    volume,
    COALESCE(currency_name, 'not defined') AS currency_name,
    last_rate_to_usd, (volume * last_rate_to_usd) AS total_volume_in_usd
FROM t4
ORDER BY
    name DESC,
    lastname ASC,
    type ASC;

-------------------------------------------2----------------------------
select * from currency;

select * from "user";

select * from balance;
WITH u_volume AS (
    -- получаем таблицу поль
    -- full join 
        SELECT
            COALESCE(u.name, 'not defined') AS name,
            COALESCE(u.lastname, 'not defined') AS lastname,
            b.type AS type,
            SUM(b.money) AS volume,
            b.currency_id
        FROM "user" AS u
            FULL JOIN balance b ON u.id = b.user_id
        GROUP BY
            b.type,
            COALESCE(u.lastname, 'not defined'),
            COALESCE(u.name, 'not defined'),
            currency_id
    ),
    b_cur_name AS (
        SELECT
            uv.name,
            uv.lastname,
            uv.type,
            uv.volume,
            COALESCE(c.name, 'not defined') AS currency_name,
            uv.currency_id
        FROM
            u_volume AS uv
            LEFT JOIN currency AS c ON c.id = uv.currency_id
        GROUP BY
            uv.name,
            uv.lastname,
            uv.type,
            uv.volume,
            COALESCE(c.name, 'not defined'),
            uv.currency_id
    ),
    rtu AS (
        SELECT
            currency.id,
            name,
            rate_to_usd,
            lastdate
        FROM (
                SELECT
                    id,
                    MAX(updated) AS lastdate
                FROM
                    currency
                GROUP BY
                    1
            ) q1
            LEFT JOIN currency ON q1.lastdate = currency.updated
            AND q1.id = currency.id
    )
SELECT
    b_cur_name.name AS name,
    lastname AS lastname,
    type,
    volume,
    currency_name,
    COALESCE(rate_to_usd, 1) AS last_rate_to_usd,
    COALESCE(volume * rate_to_usd, volume) AS total_volume_in_usd
FROM b_cur_name
    LEFT JOIN rtu ON rtu.id = b_cur_name.currency_id
ORDER BY 1 DESC, 2 ASC, 3 ASC;

select user.name from "user";

select * from currency;

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
        GROUP BY name, lastname, type, volume, currency.name, uv.currency_id),
    rtc AS (
        -- получаем курсы обмена
        SELECT currency.id, name, rate_to_usd, date_for_rate
        FROM (SELECT id, MAX(updated) AS date_for_rate FROM currency GROUP BY id) t
        LEFT JOIN currency ON t.date_for_rate  = currency.updated AND t.id = currency.id
    )
SELECT
    uvc.name AS name, lastname AS lastname, type, volume, currency_name, 
    COALESCE(rate_to_usd, 1) AS last_rate_to_usd,
    COALESCE(volume * rate_to_usd, volume) AS total_volume_in_usd
FROM uvc
    LEFT JOIN rtc ON rtc.id = uvc.currency_id
ORDER BY 1 DESC, 2 ASC, 3 ASC;


----------------------------------3-------------------------------------

select
    coalesce(u.name, 'not defined') as name,
    coalesce(u.lastname, 'not defined') as lastname,
    t1.type,
    t1.volume,
    coalesce(c.name, 'not defined') as currency_name,
    coalesce( (
            select rate_to_usd
            from currency c1
            where
                c1.id = c.id
                and c1.updated = c.last_updated
        ),
        1
    ) as last_rate_to_usd,
    t1.volume :: numeric * coalesce( (
            select rate_to_usd
            from currency c1
            where
                c1.id = c.id
                and c1.updated = c.last_updated
        ),
        1
    ) as total_volume_in_usd
from (
        select
            user_id,
            type,
            currency_id,
            sum(money) as volume
        from balance b
        group by
            user_id,
            type,
            currency_id
    ) as t1
    full join "user" u on u.id = t1.user_id
    full join (
        select
            id,
            name,
            max(updated) as last_updated
        from currency c
        group by
            id,
            name
    ) as c on c.id = t1.currency_id
order by 1 desc, 2, 3;