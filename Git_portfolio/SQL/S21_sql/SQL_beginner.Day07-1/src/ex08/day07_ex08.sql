SELECT p.address AS address,
	   piz.name AS name,
	   COUNT(*) AS count_of_orders
FROM person AS p
INNER JOIN person_order AS po ON p.id = po.person_id
INNER JOIN menu AS m ON po.menu_id = m.id
INNER JOIN pizzeria AS piz ON m.pizzeria_id = piz.id
GROUP by p.address, piz.name
ORDER BY address, name;