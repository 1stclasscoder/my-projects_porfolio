WITH T AS (SELECT id AS menu_id
FROM menu
WHERE id NOT IN (
	SELECT menu_id
	FROM person_order))
	
SELECT m.pizza_name AS pizza_name,
	m.price AS price, 
	piz.name AS pizzeria_name
FROM pizzeria AS piz
INNER JOIN menu AS m ON m.pizzeria_id = piz.id
INNER JOIN T ON T.menu_id = m.id
ORDER BY m.pizza_name, m.price;