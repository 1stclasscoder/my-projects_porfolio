WITH pv AS (
	SELECT *
	FROM person_visits
	WHERE visit_date between '2022-01-01' and '2022-01-03'
)

SELECT
	CASE 
		WHEN (T.name is NULL) THEN '-'
		ELSE T.name
	END AS person_name,
	pv.visit_date AS visit_date,
	CASE 
		WHEN (TT.name is NULL) THEN '-'
		ELSE TT.name
	END AS pizzeria_name
FROM pv
	FULL JOIN pizzeria as TT ON TT.id = pv.pizzeria_id
	FULL JOIN person as T ON T.id = pv.person_id
ORDER BY person_name, visit_date, pizzeria_name;
