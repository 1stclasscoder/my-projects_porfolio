CREATE VIEW v_price_with_discount AS
SELECT p.name AS name, 
	   m.pizza_name AS pizza_name, 
	   m.price AS price, 
	   (m.price * 0.9) :: int AS discount_price
FROM person_order AS po
INNER JOIN person AS p ON po.person_id = p.id
INNER JOIN menu AS m ON po.menu_id = m.id
ORDER BY name, pizza_name;