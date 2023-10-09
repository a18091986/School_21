SELECT DISTINCT generated_date as missing_date
from v_generated_dates
LEFT JOIN person_visits as ps
on v_generated_dates.generated_date = ps.visit_date
where ps.visit_date IS NULL
ORDER BY missing_date;