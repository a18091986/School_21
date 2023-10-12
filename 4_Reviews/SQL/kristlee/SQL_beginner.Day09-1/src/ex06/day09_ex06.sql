CREATE FUNCTION fnc_person_visits_and_eats_on_date(pperson varchar default 'Dmitriy',pprice numeric default 500,pdate date default '2022-01-08')
RETURNS TABLE(name varchar) AS
$$
BEGIN
    RETURN QUERY select pizzeria.name from menu
join pizzeria on pizzeria.id = menu.pizzeria_id
join person_visits on menu.pizzeria_id = person_visits.pizzeria_id
join person on person.id = person_visits.person_id
WHERE menu.price < pprice and person.name = pperson and visit_date = pdate;
END
$$ LANGUAGE plpgsql;
