CREATE OR REPLACE FUNCTION fnc_person_visits_and_eats_on_date(IN pperson varchar DEFAULT 'Dmitriy',
                                                              IN pprice numeric DEFAULT 500,
                                                              IN pdate date DEFAULT '2022-01-08')
RETURNS TABLE(name varchar) AS $$
BEGIN
    RETURN QUERY(
        SELECT pz.name AS pizzeria_name
        FROM person_visits pv
        JOIN pizzeria pz ON pv.pizzeria_id = pz.id
        JOIN menu m on pz.id = m.pizzeria_id
        JOIN person p ON pv.person_id = p.id
        WHERE p.name = pperson AND m.price < pprice
          AND pv.visit_date = pdate
);
END;
$$ LANGUAGE plpgsql;

SELECT *
FROM fnc_person_visits_and_eats_on_date(pprice := 800);

SELECT *
FROM fnc_person_visits_and_eats_on_date(pperson := 'Anna',pprice := 1300,pdate := '2022-01-01');

-- DROP FUNCTION fnc_person_visits_and_eats_on_date(pperson varchar, pprice numeric, pdate date) CASCADE;