insert into person_visits (id, person_id, pizzeria_id, visit_date)
values ((SELECT max(id) + 1 FROM person_visits), 4, 2, '2022-02-24');
insert into person_visits (id, person_id, pizzeria_id, visit_date)
values ((SELECT max(id) + 1 FROM person_visits), 6, 2, '2022-02-24');