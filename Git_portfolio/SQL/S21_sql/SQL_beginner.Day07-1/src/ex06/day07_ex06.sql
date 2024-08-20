SELECT DISTINCT(piz.name) AS name,
	   COUNT(*) OVER(PARTITION BY piz.name) AS count,
	   ROUND(AVG(m.price) OVER(PARTITION BY piz.name), 2) AS average_price,
	   MAX(m.price) OVER(PARTITION BY piz.name) AS max_price,
	   MIN(m.price) OVER(PARTITION BY piz.name)AS min_price
FROM person AS p
INNER JOIN person_order AS po ON p.id = po.person_id
INNER JOIN menu AS m ON po.menu_id = m.id
INNER JOIN pizzeria AS piz ON m.pizzeria_id = piz.id
ORDER BY name;