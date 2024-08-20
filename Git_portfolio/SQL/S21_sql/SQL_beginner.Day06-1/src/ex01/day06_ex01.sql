INSERT INTO person_discounts (id, person_id, pizzeria_id, discount)
WITH 
T1 AS (SELECT 
				p.id AS person_id, 
				piz.id AS pizzeria_id
		FROM person AS p, pizzeria AS piz
		ORDER BY p.id, piz.id),

T2 AS (SELECT DISTINCT (person_id) AS person_id, 
			   piz.id AS pizzeria_id,
			   COUNT(po.person_id) OVER (PARTITION BY po.person_id, piz.id) AS visit_count
		FROM person_order AS po
		INNER JOIN menu AS m ON m.id = po.menu_id
		INNER JOIN pizzeria AS piz ON piz.id = m.pizzeria_id
		ORDER BY person_id)

SELECT ROW_NUMBER( ) OVER ( ) AS id,
	   T1.person_id,
	   T1.pizzeria_id,
	   CASE 
		WHEN T2.visit_count = 1 THEN 10.5
		WHEN T2.visit_count = 2 THEN 22
		ELSE 30
	   END AS discount
FROM T1 
	INNER JOIN T2 ON T1.person_id = T2.person_id 
	AND T1.pizzeria_id = T2.pizzeria_id
ORDER BY id, T1.person_id, T1.pizzeria_id, discount
