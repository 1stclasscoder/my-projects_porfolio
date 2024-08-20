WITH T1 AS (
SELECT DISTINCT(p.name) AS name,
	   COUNT(*) OVER(PARTITION BY p.name) AS count
FROM person AS p
INNER JOIN	person_visits AS pv ON p.id = pv.person_id
ORDER BY count DESC)

SELECT name
FROM T1
WHERE count > 3;