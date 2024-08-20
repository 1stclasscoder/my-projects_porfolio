WITH 
	T AS (SELECT *
FROM pizzeria),
	TT AS (SELECT *
FROM menu
WHERE pizza_name = 'mushroom pizza' OR 
	pizza_name = 'pepperoni pizza')

SELECT TT.pizza_name AS pizza_name,
	T.name AS pizzeria_name,
	TT.price
FROM TT LEFT OUTER JOIN T ON TT.pizzeria_id = T.id
ORDER BY pizza_name, pizzeria_name;