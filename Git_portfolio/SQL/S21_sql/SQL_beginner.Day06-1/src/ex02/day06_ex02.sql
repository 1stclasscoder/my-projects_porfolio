SELECT p.name AS name,
	   m.pizza_name AS pizza_name,
	   m.price AS price,
	   (m.price *(100 - pd.discount)/100)::bigint AS discount_price,
	   piz.name AS pizzeria_name
FROM person AS p 
INNER JOIN person_order AS po ON p.id = po.person_id
INNER JOIN menu AS m ON m.id = po.menu_id
INNER JOIN pizzeria AS piz ON piz.id = m.pizzeria_id
INNER JOIN person_discounts AS pd ON po.person_id = pd.person_id AND m.pizzeria_id = pd. pizzeria_id
ORDER BY name, pizza_name