SELECT
	(SELECT name 
	 FROM person 
	 where id = person_order.person_id),
		CASE
			 WHEN (SELECT name 
	 			   FROM person 
	 			   where id = person_order.person_id) = 'Denis' THEN true
			 WHEN (SELECT name 
	 			   FROM person 
	 			   where id = person_order.person_id) != 'Denis' THEN false
		END AS check_name
FROM person_order
WHERE menu_id in (13,14,18) 
	and order_date = '2022-01-07'