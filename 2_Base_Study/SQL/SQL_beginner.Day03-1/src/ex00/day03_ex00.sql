-- Exercise 00 - Let’s find appropriate prices for Kate
-- Exercise 00: Let’s find appropriate prices for Kate	
-- Turn-in directory	ex00
-- Files to turn-in	day03_ex00.sql
-- Allowed	
-- Language	ANSI SQL

-- Please write a SQL statement which returns a list of pizza names, pizza prices, pizzerias names and dates of visit for Kate and for prices in range from 800 to 1000 rubles. Please sort by pizza, price and pizzeria names. Take a look at the sample of data below.

SELECT pizza_name, price, pizzeria.name AS pizzeria_name, visit_date FROM
    person
JOIN
    person_visits
ON person.id = person_visits.person_id
JOIN
    pizzeria
ON pizzeria.id = person_visits.pizzeria_id
JOIN
    menu
ON menu.pizzeria_id = pizzeria.id
WHERE person.name = 'Kate' AND price BETWEEN 800 AND 1000
ORDER BY pizza_name, price, pizzeria_name;