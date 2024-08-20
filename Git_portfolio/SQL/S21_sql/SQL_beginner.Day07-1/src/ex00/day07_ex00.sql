SELECT DISTINCT(person_id) AS person_id,
       COUNT(*) OVER(PARTITION BY person_id) AS count_of_visits
FROM person_visits
ORDER BY count_of_visits DESC, person_id;