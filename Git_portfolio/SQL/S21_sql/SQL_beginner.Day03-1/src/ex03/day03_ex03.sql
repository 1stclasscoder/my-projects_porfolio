WITH T AS (
	SELECT piz.name AS pizzeria_name, 
	p.gender AS gender
	FROM person_visits AS pv
	INNER JOIN person AS p ON pv.person_id = p.id
	INNER JOIN pizzeria AS piz ON piz.id = pv.pizzeria_id
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
EXCEPT ALL 
SELECT T_FEMALE.pizzeria_name
FROM T_FEMALE)
UNION ALL
(SELECT T_FEMALE.pizzeria_name
FROM T_FEMALE
EXCEPT ALL 
SELECT T_MALE.pizzeria_name
FROM T_MALE)
ORDER BY pizzeria_name;