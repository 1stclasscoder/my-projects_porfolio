SELECT piz.name AS pizzeria_name 
FROM person AS p
INNER JOIN person_visits AS pv ON pv.person_id = p.id
INNER JOIN pizzeria AS piz ON pv.pizzeria_id = piz.id
WHERE p.name = 'Andrey'
AND piz.name NOT IN (
SELECT piz.name
FROM person AS p
INNER JOIN person_order AS po ON po.person_id = p.id
INNER JOIN menu AS m ON m.id = po.menu_id
INNER JOIN pizzeria AS piz ON m.pizzeria_id = piz.id
WHERE p.name = 'Andrey')
ORDER BY pizzeria_name;