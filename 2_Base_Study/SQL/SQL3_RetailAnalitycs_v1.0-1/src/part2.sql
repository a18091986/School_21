
--Создай скрипт part2.sql, в котором напиши представления, описанные выше в разделе выходные данные. 
--Также внеси в скрипт тестовые запросы для каждого представления. 
--Допустимо для каждого представления создавать отдельный скрипт, начинающийся с part2_.
--Более подробную информацию для получения каждого поля можно найти в папке materials.

--2.1 customers

DROP FUNCTION IF EXISTS checks_cte () CASCADE;

CREATE FUNCTION checks_cte() RETURNS table(customer_id int, customer_average_check decimal, customer_average_check_segment varchar(30)) AS $$
DECLARE
	total_lines int := (SELECT COUNT(*) FROM personal_data);
BEGIN
	  RETURN QUERY WITH 
	  	av_ch AS 
        (SELECT personal_data.customer_id, 
        (CASE 
	        WHEN COUNT(transactions.transaction_summ) = 0 THEN 0 
        	ELSE ROUND(SUM(transactions.transaction_summ) / COUNT(transactions.transaction_summ), 2)
        END) AS customer_average_check 
        FROM personal_data
        	LEFT JOIN cards ON personal_data.customer_id = cards.customer_id 
        	LEFT JOIN transactions ON cards.customer_card_id = transactions.customer_card_id 
       		GROUP BY 1 ORDER BY 2 DESC), 
       	check_segments AS 
       	(SELECT *, 
       	(CASE 
	       	WHEN ROW_NUMBER () OVER () <= ROUND ((total_lines * 0.1 ), 0) THEN 'High' ::varchar(30) 
       		WHEN ROW_NUMBER () OVER () <= ROUND ((total_lines * 0.35) ,0) THEN 'Medium' ::varchar (30) 
       		ELSE 'Low' :: varchar(30) 
       	END) AS customer_average_check_segment FROM av_ch) 
       SELECT * FROM check_segments;
END;
$$ LANGUAGE plpgsql; 

DROP FUNCTION IF EXISTS transactions_cte () CASCADE;

CREATE FUNCTION transactions_cte() RETURNS 
	table(customer_id int, customer_frequency decimal, customer_frequency_segment varchar(30), customer_inactive_period decimal) AS $$
DECLARE
	total_lines numeric := ( SELECT COUNT(*) FROM personal_data );
BEGIN
	  RETURN QUERY WITH 
	  	maxmintr AS 
		  	(SELECT personal_data.customer_id, 
		  	MAX(transactions.transaction_datetime ) AS latest, 
		  	MIN(transactions.transaction_datetime ) AS earliest,
		    COUNT(DISTINCT transactions.transaction_id) AS t_count 
		    FROM personal_data 
		    	LEFT JOIN cards ON personal_data.customer_id = cards.customer_id 
		   		LEFT JOIN transactions ON cards.customer_card_id = transactions.customer_card_id GROUP BY 1),
	   	frequency AS 
		   	(SELECT maxmintr.customer_id,
		   	(CASE WHEN maxmintr.t_count = 0 THEN 0 
		   		  ELSE ROUND (((EXTRACT (EPOCH FROM NOW()) - EXTRACT(EPOCH FROM maxmintr.latest)) / (60 * 60 * 24))::decimal, 2) 
		   	 END) AS customer_inactive_period , 
		   	(CASE WHEN maxmintr.t_count = 0 THEN 0 
		   		  ELSE ROUND (((EXTRACT (EPOCH FROM maxmintr.latest) - EXTRACT(EPOCH FROM maxmintr.earliest)) / maxmintr.t_count / (60 * 60 * 24))::decimal, 2) 
		   		 	END) AS customer_frequency FROM maxmintr ORDER BY 3 ASC), 
		   	t_segments AS 
		   (SELECT frequency.customer_id, frequency.customer_frequency, 
		   (CASE WHEN ROW_NUMBER () OVER () <= ROUND ((total_lines * 0.1), 0) THEN 'Often'::varchar(30) 
		  	WHEN ROW_NUMBER () OVER () <= ROUND ((total_lines * 0.35 ), 0) THEN 'Occasionally'::varchar(30) 
		  	ELSE 'Rarely'::varchar(30) END) AS customer_frequency_segment, 
		    frequency.customer_inactive_period FROM frequency) 
		   SELECT * FROM t_segments;
	END;
$$ LANGUAGE plpgsql; 

DROP FUNCTION IF EXISTS total_segment_cte () CASCADE;

CREATE FUNCTION total_segment_cte() RETURNS 
	table(segment int, average_check varchar(30), frequency_purchases varchar (30), ch_probability varchar(30)) AS $$
BEGIN
	DROP TABLE IF EXISTS temp_table;
	CREATE TABLE temp_table (segment int, average_check varchar(30), frequency_purchases varchar(30), ch_probability varchar(30));
	INSERT INTO temp_table VALUES (1, 'Low', 'Rarely', 'Low');
	INSERT INTO temp_table VALUES (2, 'Low', 'Rarely', 'Medium');
	INSERT INTO temp_table VALUES (3, 'Low', 'Rarely', 'High');
	INSERT INTO temp_table VALUES (4, 'Low', 'Occasionally', 'Low');
	INSERT INTO temp_table VALUES (5, 'Low', 'Occasionally', 'Medium');
	INSERT INTO temp_table VALUES (6, 'Low', 'Occasionally', 'High');
	INSERT INTO temp_table VALUES (7, 'Low', 'Often', 'Low');
	INSERT INTO temp_table VALUES (8, 'Low', 'Often', 'Medium');
	INSERT INTO temp_table VALUES (9, 'Low', 'Often', 'High');
	INSERT INTO temp_table VALUES (10, 'Medium', 'Rarely', 'Low');
	INSERT INTO temp_table VALUES (11, 'Medium', 'Rarely', 'Medium');
	INSERT INTO temp_table VALUES (12, 'Medium', 'Rarely', 'High');
	INSERT INTO temp_table VALUES (13, 'Medium', 'Occasionally', 'Low');
	INSERT INTO temp_table VALUES (14, 'Medium', 'Occasionally', 'Medium');
	INSERT INTO temp_table VALUES (15, 'Medium', 'Occasionally', 'High');
	INSERT INTO temp_table VALUES (16, 'Medium', 'Often', 'Low');
	INSERT INTO temp_table VALUES (17, 'Medium', 'Often', 'Medium');
	INSERT INTO temp_table VALUES (18, 'Medium', 'Often', 'High');
	INSERT INTO temp_table VALUES (19, 'High', 'Rarely', 'Low');
	INSERT INTO temp_table VALUES (20, 'High', 'Rarely', 'Medium');
	INSERT INTO temp_table VALUES (21, 'High', 'Rarely', 'High');
	INSERT INTO temp_table VALUES (22, 'High', 'Occasionally', 'Low');
	INSERT INTO temp_table VALUES (23, 'High', 'Occasionally', 'Medium');
	INSERT INTO temp_table VALUES (24, 'High', 'Occasionally', 'High');
	INSERT INTO temp_table VALUES (25, 'High', 'Often', 'Low');
	INSERT INTO temp_table VALUES (26, 'High', 'Often', 'Medium');
	INSERT INTO temp_table VALUES (27, 'High', 'Often', 'High');
	RETURN QUERY SELECT * FROM temp_table;
END;
$$ LANGUAGE plpgsql; 

DROP FUNCTION IF EXISTS stores_cte () CASCADE;

CREATE FUNCTION stores_cte() RETURNS table(customer_id int, customer_primary_store int) AS $$
DECLARE
BEGIN
	    RETURN QUERY WITH 
	   		alltrans AS 
	   			(SELECT DISTINCT personal_data.customer_id, transactions.transaction_store_id, 
	   			COUNT (transaction_id) OVER (PARTITION BY personal_data.customer_id, transactions.transaction_store_id) AS per_store, 
	   			MAX(transactions.transaction_datetime) OVER (PARTITION BY personal_data.customer_id, transactions.transaction_store_id) max_time 
	   			FROM personal_data 
	   				LEFT JOIN cards ON personal_data.customer_id = cards.customer_id 
	   				LEFT JOIN transactions ON cards.customer_card_id = transactions.customer_card_id 
	   				ORDER BY 1), 
	   		percent_per_store AS 
	   			(SELECT alltrans.customer_id, alltrans.transaction_store_id, alltrans.max_time, 
	   			(CASE WHEN alltrans.per_store = 0 THEN 0 
	   			ELSE ROUND ((alltrans.per_store / (SUM(alltrans.per_store) OVER (PARTITION BY alltrans.customer_id)))::decimal, 2) 
	   			END) AS store_val FROM alltrans), 
	   		max_per_store AS 
	   			(SELECT percent_per_store.customer_id, percent_per_store.transaction_store_id, percent_per_store.max_time, percent_per_store.store_val, 
	   			RANK () OVER (PARTITION BY percent_per_store.customer_id 
	   			ORDER BY percent_per_store.store_val DESC, percent_per_store.max_time DESC) max_store FROM percent_per_store), 
	   		ranked_stores AS 
	   			(SELECT personal_data.customer_id, transactions.transaction_store_id, transactions.transaction_datetime, 
	   			RANK () OVER (PARTITION BY personal_data.customer_id ORDER BY transactions.transaction_datetime DESC) AS last_stores, 
	   			LAG (transaction_store_id) OVER (PARTITION BY personal_data.customer_id ORDER BY transactions.transaction_datetime DESC) AS prev_store 
	   			FROM personal_data 
	   			LEFT JOIN cards ON personal_data.customer_id = cards.customer_id 
	   			LEFT JOIN transactions ON cards.customer_card_id = transactions.customer_card_id ORDER BY 1), 
	   		max_three_stores AS 
	   			(SELECT ranked_stores.customer_id, ranked_stores.transaction_store_id, ranked_stores.transaction_datetime, 
	   			SUM(CASE WHEN ranked_stores.transaction_store_id = prev_store THEN 0 ELSE 1 END) 
	   			OVER (PARTITION BY ranked_stores.customer_id ORDER BY ranked_stores.customer_id, ranked_stores.transaction_datetime) check_col 
	   			FROM ranked_stores WHERE last_stores <= 3), 
	   		fin AS 
	   			(SELECT max_three_stores.customer_id, 
	   			(CASE WHEN SUM(max_three_stores.check_col) OVER (PARTITION BY max_three_stores.customer_id) = 3 
	   			THEN MAX (max_three_stores.transaction_store_id) OVER (PARTITION BY max_three_stores.customer_id) 
	   			ELSE COALESCE (t.transaction_store_id, 0) 
	   			END) store 
	   			FROM max_three_stores 
	   				JOIN (SELECT * FROM max_per_store WHERE max_per_store.max_store = 1) t ON max_three_stores.customer_id = t.customer_id) 
	   			SELECT DISTINCT fin.customer_id , fin.store FROM fin ORDER BY 1;
	   		END;
$$ LANGUAGE plpgsql; 

SELECT * FROM stores_cte ();


DROP VIEW IF EXISTS customers;

CREATE VIEW customers AS
WITH
    main AS 
    	(SELECT
        ch.customer_id, ch.customer_average_check, ch.customer_average_check_segment, q.customer_frequency, q.customer_frequency_segment, q.customer_inactive_period, 
        (CASE WHEN q.customer_frequency = 0 THEN 0
        ELSE ROUND(q.customer_inactive_period / q.customer_frequency, 2)
        END) AS customer_churn_rate
        FROM checks_cte () ch
        JOIN (SELECT * FROM transactions_cte ()) q ON ch.customer_id = q.customer_id),
    churn_probability AS 
    (SELECT *, 
    (CASE WHEN customer_churn_rate <= 2 THEN 'Low'
    WHEN customer_churn_rate <= 5 THEN 'Medium'
    ELSE 'High' END) AS customer_churn_segment
    FROM main),
    last_segment AS 
    (SELECT DISTINCT
    cp.customer_id, cp.customer_average_check, cp.customer_average_check_segment, cp.customer_frequency, cp.customer_frequency_segment, cp.customer_inactive_period, cp.customer_churn_rate, cp.customer_churn_segment, q.segment AS customer_segment
    FROM churn_probability cp JOIN 
    (SELECT * FROM total_segment_cte ()) q 
    ON (cp.customer_average_check_segment = q.average_check 
    	AND cp.customer_frequency_segment = q.frequency_purchases AND cp.customer_churn_segment = q.ch_probability)),
    fin AS 
    (SELECT DISTINCT last_segment.customer_id, last_segment.customer_average_check, last_segment.customer_average_check_segment, last_segment.customer_frequency, last_segment.customer_frequency_segment, last_segment.customer_inactive_period, last_segment.customer_churn_rate, last_segment.customer_churn_segment, last_segment.customer_segment, q_last.customer_primary_store
    FROM last_segment JOIN (SELECT * FROM stores_cte ()) q_last ON last_segment.customer_id = q_last.customer_id)
SELECT * FROM fin;
--
--SELECT * FROM customers;
--
--select * from temp_table tt ;

--2.2 purchase_history

DROP MATERIALIZED VIEW IF EXISTS main CASCADE;
CREATE MATERIALIZED VIEW main AS
SELECT cards.customer_id, transactions.transaction_id, transactions.transaction_datetime, checks.sku_id, goods_grid.group_id, 
	   checks.sku_amount, checks.sku_summ, checks.sku_summ_paid, checks.sku_discount, stores.sku_purchase_price, stores.sku_purchase_price * checks.sku_amount AS sku_cost, stores.sku_retail_price
FROM transactions 
	JOIN cards ON cards.customer_card_id = transactions.customer_card_id
	JOIN checks ON checks.transaction_id = transactions.transaction_id
    JOIN goods_grid ON goods_grid.sku_id = checks.sku_id
    JOIN stores ON stores.transaction_store_id = transactions.transaction_store_id AND stores.sku_id = goods_grid.sku_id;
   

DROP VIEW IF EXISTS purchase_history;
CREATE VIEW purchase_history AS
SELECT customer_id AS "Customer_ID", transaction_id AS "Transaction_ID", transaction_datetime AS "Transaction_DateTime", group_id AS "Group_ID",
     ROUND(SUM(sku_cost), 2) AS "Group_Cost", ROUND(SUM(sku_summ), 2) AS "Group_Summ", ROUND(SUM(sku_summ_paid), 2) AS "Group_Summ_Paid"
FROM main GROUP BY customer_id, transaction_id, transaction_datetime, group_id;

-- select * from purchase_history

-- 2.3 periods

DROP VIEW IF EXISTS periods CASCADE;
CREATE VIEW periods AS 
	SELECT customer_id AS "Customer_ID", group_id AS "Group_ID", MIN(transaction_datetime) AS "First_Group_Purchase_Date",
    	   MAX(transaction_datetime) AS "Last_Group_Purchase_Date", COUNT(*) AS "Group_Purchase", 
    	   ((MAX(transaction_datetime)::date - MIN(transaction_datetime)::date) + 1) / COUNT(*) AS "Group_Frequency", 
    	   ROUND(COALESCE(MIN(CASE
                              WHEN sku_discount = 0 THEN NULL ELSE sku_discount / sku_summ END), 0), 2) AS "Group_Min_Discount"
FROM main GROUP BY customer_id, group_id;

-- select * from periods;

-- 2.4 groups

DROP MATERIALIZED VIEW IF EXISTS affinity_index;
CREATE MATERIALIZED VIEW affinity_index AS SELECT p."Customer_ID" AS customer_id, p."Group_ID" AS group_id, 
	   ROUND((p."Group_Purchase"::numeric / COUNT(DISTINCT "Transaction_ID")), 2) AS group_affinity_index
FROM periods AS p JOIN purchase_history AS ph ON ph."Customer_ID" = p."Customer_ID"
                  AND ph."Transaction_DateTime" >= p."First_Group_Purchase_Date" AND ph."Transaction_DateTime" <= p."Last_Group_Purchase_Date"
GROUP BY p."Customer_ID", p."Group_ID", p."Group_Purchase";

DROP MATERIALIZED VIEW IF EXISTS churn_rate;
CREATE MATERIALIZED VIEW churn_rate AS SELECT p."Customer_ID" AS customer_id, p."Group_ID" AS group_id, 
		   CASE WHEN p."Group_Frequency" = 0 THEN 0
           ELSE ROUND(((SELECT * FROM analysis_form_date ORDER BY 1 DESC LIMIT 1)::date - p."Last_Group_Purchase_Date"::date)::numeric / p."Group_Frequency", 2) 
           END AS churn_rate
FROM periods AS p JOIN purchase_history AS ph ON ph."Customer_ID" = p."Customer_ID" GROUP BY p."Customer_ID", p."Group_ID", p."Last_Group_Purchase_Date", p."Group_Frequency";


DROP MATERIALIZED VIEW IF EXISTS stability_index;
CREATE MATERIALIZED VIEW stability_index AS WITH stability_temp AS 
	(SELECT ph."Customer_ID" AS customer_id, ph."Group_ID" AS group_id, ph."Transaction_DateTime" AS tr_date, 
	COALESCE((ph."Transaction_DateTime"::date - LAG(ph."Transaction_DateTime") 
	OVER (PARTITION BY ph."Customer_ID", ph."Group_ID" ORDER BY ph."Transaction_DateTime")::date), 0) AS intervals,
    p."Group_Frequency" AS gr_frequency
    FROM purchase_history AS ph JOIN periods AS p ON p."Customer_ID" = ph."Customer_ID" AND p."Group_ID" = ph."Group_ID")
SELECT customer_id, group_id, 
	   ROUND(AVG(CASE WHEN gr_frequency = 0 THEN 0
	   ELSE (CASE WHEN (gr_frequency > intervals) THEN gr_frequency - intervals
       ELSE intervals - gr_frequency END)::numeric / gr_frequency END), 2) AS stability_index FROM stability_temp AS st
GROUP BY customer_id, group_id;


DROP MATERIALIZED VIEW IF EXISTS discount_share_min;
CREATE MATERIALIZED VIEW discount_share_min AS 
	WITH discount_transaction AS 
		(SELECT m.customer_id, m.group_id, COUNT(DISTINCT transaction_id) AS qty_dis_tr
        FROM main AS m WHERE m.sku_discount > 0 GROUP BY m.customer_id, m.group_id)
SELECT p."Customer_ID" AS customer_id, p."Group_ID" AS group_id, 
ROUND(COALESCE(dt.qty_dis_tr, 0)::numeric / p."Group_Purchase", 2) AS group_discount_share, 
p."Group_Min_Discount" AS group_min_discount 
FROM discount_transaction AS dt RIGHT JOIN periods AS p ON p."Customer_ID" = dt.customer_id AND p."Group_ID" = dt.group_id;


DROP MATERIALIZED VIEW IF EXISTS group_average_discount;
CREATE MATERIALIZED VIEW group_average_discount AS 
	SELECT "Customer_ID" AS customer_id, "Group_ID" AS group_id, 
	ROUND(SUM("Group_Summ_Paid") / SUM("Group_Summ"), 2) AS group_average_discount
	FROM purchase_history GROUP BY "Customer_ID", "Group_ID";


DROP FUNCTION IF EXISTS group_margin(int, int) CASCADE;
CREATE FUNCTION group_margin(mode_margin int DEFAULT 3, in_value int DEFAULT 100)
    RETURNS table(customer_id  int, group_id int, group_margin numeric) AS $$
BEGIN
    IF mode_margin = 1 THEN RETURN QUERY
            SELECT "Customer_ID" AS customer_id, "Group_ID" AS group_id, 
            ROUND((SUM("Group_Summ_Paid") - SUM("Group_Cost")) / SUM("Group_Summ_Paid"), 2) AS group_margin
            FROM purchase_history
            WHERE "Transaction_DateTime"::date >= ((SELECT * FROM analysis_form_date ORDER BY 1 DESC LIMIT 1)::date - in_value)
            GROUP BY "Customer_ID", "Group_ID";
    ELSIF mode_margin = 2 THEN RETURN QUERY
            SELECT lph.customer_id, lph.group_id, ROUND(SUM(lph.margin / lph.group_paid), 2) AS group_margin
            FROM (SELECT "Customer_ID" AS customer_id, "Group_ID" AS group_id, "Group_Summ_Paid" - "Group_Cost" AS margin,
            "Group_Summ_Paid" AS group_paid 
            FROM purchase_history ORDER BY "Transaction_DateTime" DESC LIMIT 1000) AS lph
            GROUP BY lph.customer_id, lph.group_id;
    ELSE RETURN QUERY
        	SELECT "Customer_ID" AS customer_id, "Group_ID" AS group_id, 
        	ROUND((SUM("Group_Summ_Paid") - SUM("Group_Cost")) / SUM("Group_Summ_Paid"), 2) AS group_margin
            FROM purchase_history GROUP BY "Customer_ID", "Group_ID";
    END IF;
END;
$$ LANGUAGE plpgsql;


DROP VIEW IF EXISTS groups;
CREATE VIEW groups AS 
	SELECT gm.customer_id AS "Customer_ID", gm.group_id AS "Group_ID", ai.group_affinity_index AS "Group_Affinity_Index",
     	   cr.churn_rate AS "Group_Churn_Rate", si.stability_index AS "Group_Stability_Index", gm.group_margin AS "Group_Margin",
     	   dsm.group_discount_share AS "Group_Discount_Share", dsm.group_min_discount AS "Group_Minimum_Discount",
     	   gad.group_average_discount AS "Group_Average_Discount"
	FROM group_margin() AS gm 
		 JOIN affinity_index AS ai ON ai.customer_id = gm.customer_id AND ai.group_id = gm.group_id
         JOIN churn_rate AS cr ON cr.customer_id = gm.customer_id AND cr.group_id = gm.group_id
         JOIN stability_index AS si ON si.customer_id = gm.customer_id AND si.group_id = gm.group_id
         JOIN discount_share_min AS dsm ON dsm.customer_id = gm.customer_id AND dsm.group_id = gm.group_id
         JOIN group_average_discount AS gad ON gad.customer_id = gm.customer_id AND gad.group_id = gm.group_id;
        

select * from groups;
select * from periods p ;
select * from purchase_history ph ;
select * from customers;
