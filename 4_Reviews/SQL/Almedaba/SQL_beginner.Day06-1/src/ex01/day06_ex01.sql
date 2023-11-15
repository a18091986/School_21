WITH quantity AS (
    SELECT 
        person_id, 
        pizzeria_id, 
        COUNT(*)
    FROM person_order
    JOIN menu
    ON menu.id = person_order.menu_id
    GROUP BY person_id, pizzeria_id
)
INSERT INTO person_discounts
  SELECT  
      ROW_NUMBER() OVER() as id,
      person_id,
      pizzeria_id,
      CASE
          WHEN count = 1 THEN 10.5
          WHEN count = 2 THEN 22
          ELSE 30
      END AS discount
  FROM quantity;


  select count(*) > 0 as check from person_discounts 