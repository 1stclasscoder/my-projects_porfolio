SELECT piz.name
FROM person_visits AS pv
INNER JOIN person AS per ON per.id = pv.person_id
INNER JOIN menu AS m ON m.pizzeria_id = pv.pizzeria_id
INNER JOIN pizzeria as piz ON piz.id = pv.pizzeria_id
WHERE per.name = 'Dmitriy'
AND visit_date = '2022-01-08'
AND m.price < 800;