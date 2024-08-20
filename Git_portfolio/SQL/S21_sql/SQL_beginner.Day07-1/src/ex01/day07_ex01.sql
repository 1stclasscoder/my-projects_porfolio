SELECT DISTINCT(p.name) AS name,
       COUNT(*) OVER(PARTITION BY person_id) AS count_of_visits
FROM person_visits AS PV
INNER JOIN person AS p ON p.id = pv.person_id
ORDER BY count_of_visits DESC, name
LIMIT 4;