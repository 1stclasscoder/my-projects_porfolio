WITH T1 AS (
SELECT DISTINCT(piz.name) AS name,
	   COUNT(*) OVER(PARTITION BY pv.pizzeria_id) AS count
FROM person AS p
INNER JOIN	person_visits AS pv ON p.id = pv.person_id
INNER JOIN pizzeria AS piz ON pv.pizzeria_id = piz.id
ORDER BY count DESC),
	
	T2 AS (
SELECT DISTINCT(piz.name) AS name,
	   COUNT(*) OVER(PARTITION BY m.pizzeria_id) AS count
FROM person AS p
INNER JOIN person_order AS po ON p.id = po.person_id
INNER JOIN menu AS m ON po.menu_id = m.id
INNER JOIN pizzeria AS piz ON m.pizzeria_id = piz.id
ORDER BY count DESC),
	
T3 AS (SELECT T2.name, T2.count
FROM T2
UNION ALL
SELECT T1.name, T1.count
FROM T1)

SELECT DISTINCT(T3.name) AS name, 
	   SUM(T3.count) OVER(PARTITION BY T3.name) AS total_count
FROM T3
ORDER BY total_count DESC, name;