insert into menu (id, pizzeria_id, pizza_name, price)
values ((SELECT max(id)+1 FROM menu), 2, 'sicilian pizza', 900);