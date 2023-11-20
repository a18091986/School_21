CREATE OR REPLACE FUNCTION fnc_person_visits_and_eats_on_date(
    IN pperson VARCHAR DEFAULT 'Dmitriy',
    IN pprice INT DEFAULT 500,
    IN pdate DATE DEFAULT '2022-01-08'
)
RETURNS TABLE (
    pizzeria_name VARCHAR
) AS $$
BEGIN
    RETURN QUERY
		SELECT DISTINCT pizzeria.name AS pizzeria_name
		FROM pizzeria
		JOIN person_visits ON person_visits.pizzeria_id = pizzeria.id
		JOIN person ON person.id = person_visits.person_id
		JOIN menu ON menu.pizzeria_id = pizzeria.id
		WHERE person.name = pperson AND person_visits.visit_date = pdate AND menu.price < pprice;
END;
$$ LANGUAGE plpgsql;

SELECT * FROM fnc_person_visits_and_eats_on_date(pprice := 800);
SELECT * FROM fnc_person_visits_and_eats_on_date(pperson := 'Anna', pprice := 1300, pdate := '2022-01-01');
