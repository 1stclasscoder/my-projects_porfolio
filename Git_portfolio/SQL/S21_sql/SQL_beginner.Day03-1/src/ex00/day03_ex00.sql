WITH
	T AS (
SELECT pv.pizzeria_id AS pizzeria_id, pv.visit_date AS visit_date
FROM person_visits AS pv
INNER JOIN person AS per ON per.id = pv.person_id
WHERE per.name = 'Kate'
)
	
SELECT m.pizza_name AS pizza_name,
	m.price AS price,
	piz.name AS name,
	m.pizzeria_id AS pizzeria_id,
	T.visit_date
FROM menu AS m
INNER JOIN pizzeria AS piz ON piz.id = m.pizzeria_id
INNER JOIN T ON T.pizzeria_id = m.pizzeria_id
WHERE m.price BETWEEN 800 AND 1000
ORDER BY pizza_name, price, name;