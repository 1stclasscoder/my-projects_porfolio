WITH 
T AS (SELECT visit_date
FROM person_visits
WHERE (person_id = 1 OR person_id = 2)
	AND visit_date between '2022-01-01' AND '2022-01-10'
GROUP BY visit_date)

SELECT pv.visit_date AS missing_date
FROM person_visits AS pv 
LEFT OUTER JOIN T ON T.visit_date = pv.visit_date
WHERE T.visit_date is NULL
GROUP BY pv.visit_date
ORDER BY pv.visit_date;