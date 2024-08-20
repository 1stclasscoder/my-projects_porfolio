insert into person_order (id, person_id, menu_id, order_date)
SELECT id + (SELECT max(id) FROM person_order) AS id, 
	id AS person_id,
	(SELECT id FROM menu WHERE pizza_name = 'greek pizza') AS menu_id,
	CAST ('2022-02-25' AS DATE) AS order_date
FROM person;

