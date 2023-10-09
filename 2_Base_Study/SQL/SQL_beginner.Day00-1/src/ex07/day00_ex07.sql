-- Let’s apply data intervals for the person table.
-- Please make a SQL statement which returns a person's identifiers, person's names and interval of person’s ages (set a name of a new calculated column as ‘interval_info’) based on pseudo code below.
-- if (age >= 10 and age <= 20) then return 'interval #1'
-- else if (age > 20 and age < 24) then return 'interval #2'
-- else return 'interval #3'
-- and yes...please sort a result by ‘interval_info’ column in ascending mode.


SELECT id, name
	(CASE 
		when age >=10 AND age <=20 then 'interval #1' 
		when age > 20 AND age < 24 then 'interval #2'
        else 'interval #3' 
     END) AS interval_info
FROM person p
ORDER BY interval_info;

