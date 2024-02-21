--Написать функцию, определяющую предложения, ориентированные на рост среднего чека
--
--Параметры функции:
--метод расчета среднего чека (1 - за период, 2 - за количество)
--первая и последняя даты периода (для 1 метода)
--количество транзакций (для 2 метода)
--коэффициент увеличения среднего чека
--максимальный индекс оттока
--максимальная доля транзакций со скидкой (в процентах)
--допустимая доля маржи (в процентах)
--Определение условия предложения
--
--Выбор метода расчета среднего чека. 
--Существует возможность выбора метода расчета среднего чека – за определенный период времени или за определенное количество последних транзакций. 
--Метод расчета вручную определяется пользователем.
--Пользователь выбирает методику расчета по периоду, после чего указывает первую и последнюю даты периода, 
--за который необходимо рассчитать средний чек для всей совокупности клиентов, попавших в выборку. 
--При этом последняя дата указываемого периода должна быть позже первой, а указанный период должен быть внутри общего анализируемого периода. 
--В случае указания слишком ранней или слишком поздней даты система автоматически подставляет дату, соответственно, начала или окончания анализируемого периода. 
--Для расчета учитываются все транзакции, совершенные каждым конкретным клиентом в течение заданного периода.
--
--Пользователь выбирает методику расчета по количеству последних транзакций, 
--после чего вручную указывает количество транзакций, по которым необходимо рассчитать средний чек. 
--Для расчета среднего чека берется заданное пользователем количество транзакций, начиная с самой последней в обратном хронологическом порядке. 
--В случае, если каким-либо клиентом из выборки за весь анализируемый период совершено меньше указанного количества транзакций, 
--для анализа используется имеющееся количество транзакций.
--
--Определение среднего чека. Для каждого клиента определяется текущее значение его среднего чека согласно выбранному в рамках шага 1 методу. 
--Для этого общий товарооборот по всем попавшим в выборку транзакциям клиента делится на количество этих транзакций. 
--Итоговое значение сохраняется в таблице как текущее значение среднего чека.
--
--Определение целевого значения среднего чека. Рассчитанное значение среднего чека умножается на коэффициент заданный пользователем. 
--Получившееся значение сохраняется в системе как целевое значение среднего чека клиента и в дальнейшем используется для формирования условия предложения, 
--которое должен выполнить клиент для получения вознаграждения.
--
--Определение вознаграждения
--Определение группы для формирования вознаграждения. 
--Для формирования вознаграждения выбирается группа, отвечающая последовательно следующим критериям:
--Индекс востребованности группы – максимальный из всех возможных.
--Индекс оттока по данной группе не должен превышать заданного пользователем значения. 
--В случае, если коэффициент оттока превышает установленное значение, берется следующая по индексу востребованности группа;
--Доля транзакций со скидкой по данной группе – менее заданного пользователем значения. 
--В случае, если для выбранной группы превышает установленное значение, берется следующая по индексу востребованности группа, удовлетворяющая также критерию по оттоку.
--
--Определение максимально допустимого размера скидки для вознаграждения. 
--Пользователь вручную определяет долю маржи (в процентах), которую допустимо использовать для предоставления вознаграждения по группе. 
--Итоговое значение максимально допустимой скидки рассчитывается путем умножения заданного значения на среднюю маржу клиента по группе.
--
--Определение величины скидки. Значение, полученное на шаге 5, 
--сравнивается с минимальной скидкой, которая была зафиксирована для клиента по данной группе, 
--округленной вверх с шагом в 5%. В случае, если минимальная скидка после округления меньше значения, получившегося на шаге 5, 
--она устанавливается в качестве скидки для группы в рамках предложения для клиента. 
--В противном случае данная группа исключается из рассмотрения, и для формирования предложения для клиента процесс повторяется, 
--начиная с шага 4 (используются следующая подходящая по описанным критериям группа).


DROP FUNCTION IF EXISTS average_count(int, decimal) CASCADE;
CREATE FUNCTION average_count(transactions_num int, koeff_up decimal)
    RETURNS table(customer_id int, required_check_measure decimal) AS $$
BEGIN
    RETURN QUERY
        SELECT DISTINCT q.customer_id, 
        ROUND((SUM(q.transaction_summ) OVER (PARTITION BY q.customer_id)) / (COUNT(q.transaction_id) OVER (PARTITION BY q.customer_id)) * koeff_up, 2) avg_check
        FROM (SELECT pd.customer_id, t.*, ROW_NUMBER() OVER w AS check_count
              FROM personal_data pd LEFT JOIN cards ON pd.customer_id = cards.customer_id LEFT JOIN transactions t ON cards.customer_card_id = t.customer_card_id
              WINDOW w AS (PARTITION BY pd.customer_id ORDER BY t.transaction_datetime DESC) ORDER BY 1) q
        WHERE q.check_count <= transactions_num AND q.transaction_id IS NOT NULL ORDER BY 1;
END;
$$ LANGUAGE plpgsql;

DROP FUNCTION IF EXISTS average_period(date, date, decimal) CASCADE;
CREATE FUNCTION average_period(first_date date, last_date date, koeff_up decimal)
    RETURNS table (customer_id int, required_check_measure decimal) AS $$
BEGIN
    RETURN QUERY
        SELECT DISTINCT pd.customer_id,
        ROUND((SUM(q.transaction_summ) OVER (PARTITION BY pd.customer_id)) / (COUNT(q.transaction_id) OVER (PARTITION BY pd.customer_id)) * koeff_up, 2) avg_check
        FROM personal_data pd JOIN cards ON pd.customer_id = cards.customer_id JOIN 
        (SELECT * FROM transactions WHERE transaction_datetime BETWEEN first_date AND last_date) q ON cards.customer_card_id = q.customer_card_id ORDER BY 1;
END;
$$ LANGUAGE plpgsql;



DROP FUNCTION IF EXISTS best_group(decimal, decimal, decimal) CASCADE;
CREATE FUNCTION best_group(max_churn decimal, max_transitions_with_discount decimal, max_margin_share decimal)
    RETURNS table (customer_id int, group_name varchar(30), offer_discount_depth decimal) AS $$
BEGIN
    RETURN QUERY
        WITH main AS 
        (SELECT grv."Customer_ID", grv."Group_ID", grv."Group_Affinity_Index", 
        (CASE WHEN ROUND(grv."Group_Minimum_Discount" / 0.05) * 0.05 < grv."Group_Minimum_Discount" THEN ROUND(grv."Group_Minimum_Discount" / 0.05) * 0.05 + 0.05
        ELSE ROUND(grv."Group_Minimum_Discount" / 0.05) * 0.05 END) AS round_discount, grv."Group_Margin" * max_margin_share AS max_margin,
        grv."Group_Minimum_Discount", ROW_NUMBER() OVER (PARTITION BY grv."Customer_ID" ORDER BY grv."Group_Affinity_Index" DESC) AS check_priority
        FROM groups grv WHERE grv."Group_Churn_Rate" <= max_churn AND grv."Group_Discount_Share" < max_transitions_with_discount ORDER BY 1),
        final_group AS (SELECT DISTINCT ON (m."Customer_ID") m."Customer_ID", gs.group_name::varchar(30), m.round_discount
        FROM main m JOIN sku_groups gs ON m."Group_ID" = gs.group_id WHERE m.round_discount < m.max_margin ORDER BY m."Customer_ID", m.check_priority)
        SELECT * FROM final_group ORDER BY 1;

END;
$$ LANGUAGE plpgsql;

DROP FUNCTION IF EXISTS average_check_growth(int, date, date, int, decimal, decimal, decimal, decimal) CASCADE;
CREATE FUNCTION average_check_growth(calc_method int DEFAULT 1, first_date date DEFAULT CURRENT_DATE, last_date date DEFAULT CURRENT_DATE, transactions_num int DEFAULT 5, 
				koeff_up decimal DEFAULT 2, max_churn decimal DEFAULT 100, max_transitions_with_discount decimal DEFAULT 0.7, max_margin_share decimal DEFAULT 0.3)
    RETURNS table (customer_id int, required_check_measure decimal, group_name varchar(30), offer_discount_depth decimal) AS $$
DECLARE
    upper_bound date := (SELECT MAX(transaction_datetime) FROM transactions);
    lower_bound date := (SELECT MIN(transaction_datetime) FROM transactions);
BEGIN
    IF last_date < first_date THEN last_date = upper_bound; END IF;
    IF last_date > upper_bound THEN last_date = upper_bound; END IF;
    IF first_date < lower_bound THEN first_date = lower_bound; END IF;
    IF calc_method = 1 THEN RETURN QUERY
            SELECT q1.customer_id, q1.required_check_measure, q2.group_name, round(q2.offer_discount_depth * 100) as offer_discount_depth
            FROM 
            (SELECT * FROM average_period(first_date, last_date, koeff_up)) q1
             JOIN (SELECT * FROM best_group(max_churn, max_transitions_with_discount, max_margin_share)) q2 ON q1.customer_id = q2.customer_id;   
    ELSIF calc_method = 2 THEN RETURN QUERY
            SELECT q1.customer_id, q1.required_check_measure, q2.group_name, round(q2.offer_discount_depth * 100) as offer_discount_depth
            FROM 
            (SELECT * FROM average_count(transactions_num, koeff_up)) q1 
            JOIN (SELECT * FROM best_group(max_churn, max_transitions_with_discount, max_margin_share)) q2 ON q1.customer_id = q2.customer_id;
    ELSE RAISE EXCEPTION 'Select 1 or 2 as calc method parameter'; END IF;
END;
$$ LANGUAGE plpgsql;

SELECT * FROM average_check_growth(1, '2020-01-01'::date, '2021-01-01'::date);

SELECT * FROM average_check_growth(2, '2020-01-01'::date, '2020-01-01'::date, 10);