CREATE OR REPLACE FUNCTION fnc_person_visits_and_eats_on_date
	(pperson varchar default 'Dmitriy', pprice numeric default 500, pdate date default '2022-01-08') 
	RETURNS TABLE (
				  name varchar
					) AS $$ 
	SELECT DISTINCT(piz.name)
	FROM person AS p
	INNER JOIN person_visits AS pv ON p.id = pv.person_id
	INNER JOIN pizzeria AS piz ON pv.pizzeria_id = piz.id
	INNER JOIN menu AS m ON m.pizzeria_id = piz.id
	WHERE p.name = pperson 
	AND m.price < pprice
	AND pv.visit_date = pdate;
	
$$ LANGUAGE SQL;

SELECT *
FROM fnc_person_visits_and_eats_on_date(pprice := 800);

SELECT *
FROM fnc_person_visits_and_eats_on_date
	(pperson := 'Anna',pprice := 1300,pdate := '2022-01-01');