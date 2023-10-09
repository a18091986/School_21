-- Please make a select statement which returns one calculated field with name ‘person_information’ in one string like described in the next sample:
-- Anna (age:16,gender:'female',address:'Moscow')
-- Finally, please add the ordering clause by calculated column in ascending mode.
-- Please pay attention to quote symbols in your formula!

SELECT CONCAT(name, ' (age:', age,',gender:''',gender,''',address:''',address,''')') AS person_information FROM person p ORDER BY person_information ASC;

