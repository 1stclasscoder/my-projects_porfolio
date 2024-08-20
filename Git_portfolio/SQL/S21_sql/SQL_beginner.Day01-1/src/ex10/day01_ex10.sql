SELECT per.name AS person_name,
	   m.pizza_name AS pizza_name,
       piz.name AS pizzeria_name
FROM person_order as po 
	INNER JOIN person AS per ON po.person_id = per.id
	INNER JOIN menu as m ON po.menu_id = m.id
	INNER JOIN pizzeria as piz ON m.pizzeria_id = piz.id
ORDER BY person_name, pizza_name, pizzeria_name;