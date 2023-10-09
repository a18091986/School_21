SELECT name from v_persons_female
UNION
SELECT name from v_persons_male
ORDER by name;