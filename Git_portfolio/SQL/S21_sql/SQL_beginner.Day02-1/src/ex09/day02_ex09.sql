WITH 
T AS (SELECT p.name, po.person_id
FROM person_order AS po
INNER JOIN menu AS m ON m.id = po.menu_id
INNER JOIN person AS p ON p.id = po.person_id
WHERE p.gender = 'female'
AND	m.pizza_name = 'pepperoni pizza'),
	
TT AS (SELECT p.name, po.person_id 
FROM person_order AS po
INNER JOIN menu AS m ON m.id = po.menu_id
INNER JOIN person AS p ON p.id = po.person_id
WHERE p.gender = 'female'
AND	m.pizza_name = 'cheese pizza')

SELECT T.name
FROM T INNER JOIN TT ON T.person_id = TT.person_id
ORDER BY T.name;