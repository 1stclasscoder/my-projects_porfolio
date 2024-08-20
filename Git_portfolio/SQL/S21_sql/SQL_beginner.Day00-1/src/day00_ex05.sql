SELECT
	(SELECT name 
	 FROM person 
	 where id = person_order.person_id)
FROM person_order
WHERE menu_id in (13,14,18) 
	and order_date = '2022-01-07'