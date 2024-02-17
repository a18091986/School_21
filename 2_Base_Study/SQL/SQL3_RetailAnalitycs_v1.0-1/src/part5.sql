Написать функцию, определяющую предложения, ориентированные на рост частоты визитов
Параметры функции:
первая и последняя даты периода
добавляемое число транзакций
максимальный индекс оттока
максимальная доля транзакций со скидкой (в процентах)
допустимая доля маржи (в процентах)
Определение условия предложения
Определение периода. Пользователь вручную задает период действия разрабатываемого предложения, указывая первую и конечную его даты.

Определение текущей частоты посещений клиента в заданный период. 
Из конечной даты заданного периода вычитается первая дата, 
после чего полученное значение делится на среднюю интенсивность транзакций клиента 
(поле Customer_Frequency таблицы Клиенты). 
Итоговый результат сохраняется в качестве базовой интенсивности транзакций клиента в течение заданного периода.

Определение транзакции для начисления вознаграждения. 
Система определяет порядковый номер транзакции в рамках заданного периода, 
на которую должно быть начислено вознаграждение. 
Для этого значение, полученное на шаге 2, округляется согласно арифметическим правилам до целого, 
после чего к нему добавляется число транзакций, заданное пользователем. 
Итоговое значение является целевым количеством транзакций, которое должен совершить клиент для получения вознаграждения.

Определение вознаграждения
Определение группы для формирования вознаграждения. Для формирования вознаграждения выбирается группа, отвечающая последовательно следующим критериям:

Индекс востребованности группы – максимальный из всех возможных.
Индекс оттока по данной группе не должен превышать заданного пользователем значения. 
В случае, если коэффициент оттока превышает установленное значение, 
берется следующая по индексу востребованности группа;
Доля транзакций со скидкой по данной группе – менее заданного пользователем значения. 
В случае, если для выбранной группы превышает установленное значение, берется следующая по индексу востребованности группа, 
удовлетворяющая также критерию по оттоку.

Определение максимально допустимого размера скидки для вознаграждения. 
Пользователь вручную определяет долю маржи (в процентах), которую допустимо использовать для предоставления вознаграждения по группе. 
Итоговое значение максимально допустимой скидки рассчитывается путем умножения заданного значения на среднюю маржу клиента по группе.

Определение величины скидки. Значение, полученное на шаге 5, сравнивается с минимальной скидкой, 
которая была зафиксирована для клиента по данной группе, округленной вверх с шагом в 5%. 
В случае, если минимальная скидка после округления меньше значения, получившегося на шаге 5, 
она устанавливается в качестве скидки для группы в рамках предложения для клиента. 
В противном случае данная группа исключается из рассмотрения, и для формирования предложения для клиента процесс повторяется, 
начиная с шага 4 (используются следующая подходящая по описанным критериям группа).

DROP FUNCTION IF EXISTS frequency_of_visits(timestamp, timestamp, bigint, numeric, numeric, numeric);
CREATE FUNCTION frequency_of_visits(
			first_date timestamp DEFAULT '2023-02-01 08:00:00', last_date timestamp DEFAULT '2023-09-01 07:00:00', add_trans bigint DEFAULT 10,
            max_churn_index numeric DEFAULT 10, max_disc_share numeric DEFAULT 85, allow_margin_share numeric DEFAULT 50)
    RETURNS table ("Customer_ID" int, "Start_Date" timestamp, "End_Date" timestamp, "Required_Transactions_Count" numeric, "Group_Name" varchar, "Offer_Discount_Depth" numeric) AS $$
DECLARE
    in_interv int := (last_date::date - first_date::date);
BEGIN
    RETURN QUERY
        WITH group_name AS 
        (SELECT DISTINCT gv."Customer_ID" AS customer_id, FIRST_VALUE(gsku.group_name) OVER (PARTITION BY gv."Customer_ID" ORDER BY gv."Group_Affinity_Index" DESC) AS gr_name, 
        FIRST_VALUE(gv."Group_Minimum_Discount") OVER (PARTITION BY gv."Customer_ID" ORDER BY gv."Group_Affinity_Index" DESC) AS depth_disc
        FROM groups AS gv JOIN sku_groups AS gsku ON gsku.group_id = gv."Group_ID"
        WHERE "Group_Churn_Rate" <= max_churn_index  AND "Group_Discount_Share" < max_disc_share::numeric / 100 AND "Group_Margin" * allow_margin_share::numeric / 100 > (CASE
        WHEN ROUND(gv."Group_Minimum_Discount" / 0.05) * 0.05 < gv."Group_Minimum_Discount" THEN ROUND(gv."Group_Minimum_Discount" / 0.05) * 0.05 + 0.05
        ELSE ROUND(gv."Group_Minimum_Discount" / 0.05) * 0.05 END))
        SELECT cs.customer_id, first_date, last_date, 
        CASE WHEN cs.customer_frequency = 0 THEN add_trans ELSE (ROUND(in_interv::numeric / cs.customer_frequency, 0) + add_trans) END,
        gn.gr_name, 
        CASE WHEN ROUND(gn.depth_disc / 0.05) * 0.05 < gn.depth_disc THEN (ROUND(gn.depth_disc / 0.05) * 0.05 + 0.05) * 100 ELSE (ROUND(gn.depth_disc / 0.05) * 0.05) * 100 END
        FROM customers AS cs JOIN group_name AS gn ON cs.customer_id = gn.customer_id; END;
$$ LANGUAGE plpgsql;

SELECT * FROM frequency_of_visits();