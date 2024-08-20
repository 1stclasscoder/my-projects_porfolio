WITH T1 AS (
SELECT DISTINCT(piz.name) AS name,
	   COUNT(*) OVER(PARTITION BY pv.pizzeria_id) AS count,
	   'visit' AS action_type
FROM person AS p
INNER JOIN	person_visits AS pv ON p.id = pv.person_id
INNER JOIN pizzeria AS piz ON pv.pizzeria_id = piz.id
ORDER BY action_type, count DESC
LIMIT 3),
	
	T2 AS (
SELECT DISTINCT(piz.name) AS name,
	   COUNT(*) OVER(PARTITION BY m.pizzeria_id) AS count,
	   'order' AS action_type
FROM person AS p
INNER JOIN person_order AS po ON p.id = po.person_id
INNER JOIN menu AS m ON po.menu_id = m.id
INNER JOIN pizzeria AS piz ON m.pizzeria_id = piz.id
ORDER BY action_type, count DESC
LIMIT 3)
	
SELECT *
FROM T2
UNION ALL
SELECT *
FROM T1;