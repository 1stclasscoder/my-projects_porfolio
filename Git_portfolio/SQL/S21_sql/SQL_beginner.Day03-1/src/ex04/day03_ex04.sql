WITH T AS (
	SELECT piz.name AS pizzeria_name, 
	p.gender AS gender
	FROM person_order AS po
	INNER JOIN person AS p ON po.person_id = p.id
	INNER JOIN menu AS m ON m.id = po.menu_id
	INNER JOIN pizzeria AS piz ON piz.id = m.pizzeria_id
),
T_MALE AS (
	SELECT T.pizzeria_name AS pizzeria_name
	FROM T
	WHERE T.gender = 'male'),
T_FEMALE AS (
	SELECT T.pizzeria_name AS pizzeria_name
	FROM T
	WHERE T.gender = 'female')

(SELECT T_MALE.pizzeria_name
FROM T_MALE
EXCEPT
SELECT T_FEMALE.pizzeria_name
FROM T_FEMALE)
UNION
(SELECT T_FEMALE.pizzeria_name
FROM T_FEMALE
EXCEPT
SELECT T_MALE.pizzeria_name
FROM T_MALE)
ORDER BY pizzeria_name;