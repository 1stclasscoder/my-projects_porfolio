WITH T AS (SELECT m.pizza_name AS pizza_name, 
	piz.name AS pizzeria_name, 
	m.price AS price,
	m.pizzeria_id AS pizzeria_id
FROM menu AS m
INNER JOIN pizzeria AS piz ON m.pizzeria_id = piz.id)

SELECT T1.pizza_name AS pizza_name, 
	T1.pizzeria_name AS pizzeria_name_1, 
	T2.pizzeria_name AS pizzeria_name_2,
	T1.price AS price
FROM T AS T1,T AS T2
WHERE T1.pizzeria_name != T2.pizzeria_name
AND T1.pizza_name = T2.pizza_name
AND T1.price = T2.price
AND T1.pizzeria_id > T2.pizzeria_id;

