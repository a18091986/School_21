-- Exercise 06 - Lets see on “Hidden” Insights
-- Exercise 06: Lets see on “Hidden” Insights	
-- Turn-in directory	ex06
-- Files to turn-in	day01_ex06.sql
-- Allowed	
-- Language	ANSI SQL

-- Let's return our mind back to exercise #03 and change our SQL statement to return person names instead of person identifiers and change ordering by action_date in ascending mode and then by person_name in descending mode. Please take a look at a data sample below.


(SELECT order_date AS action_date, (SELECT NAME FROM person WHERE person.id = person_order.person_id) AS person_name FROM person_order)
INTERSECT
(SELECT visit_date AS action_date, (SELECT NAME FROM person WHERE person.id = person_visits.person_id) AS person_name FROM person_visits)
ORDER BY action_date, person_name DESC

