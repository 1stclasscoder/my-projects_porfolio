COMMENT ON TABLE person_discounts IS 'Таблица с рамерами скидок пользователей в определенных пиццериях';
COMMENT ON COLUMN person_discounts.id IS 'Нумерация скидок';
COMMENT ON COLUMN person_discounts.person_id IS 'id клиента';
COMMENT ON COLUMN person_discounts.pizzeria_id IS 'id пиццерии';
COMMENT ON COLUMN person_discounts.discount IS 'Размер скидки клиента в определенной пиццерии';