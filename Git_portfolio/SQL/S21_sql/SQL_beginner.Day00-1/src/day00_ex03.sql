SELECT DISTINCT (person_id)
FROM person_visits
WHERE pizzeria_id = 2 
    or visit_date between '2022-01-06' and '2022-01-09'
order by person_id DESC