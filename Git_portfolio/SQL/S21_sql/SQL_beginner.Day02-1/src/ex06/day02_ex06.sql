WITH

T AS (SELECT *
FROM person
WHERE name = 'Denis' OR name = 'Anna'),

TT AS  (
SELECT *
FROM person_order AS po INNER JOIN T ON T.id = po.person_id),

TTT AS (
SELECT *
FROM menu AS m INNER JOIN TT ON TT.menu_id = m.id),

TTTT AS (
SELECT TTT.pizza_name, p.name AS pizzeria_name
FROM pizzeria AS p INNER JOIN TTT ON TTT.pizzeria_id = p.id)

SELECT *
FROM TTTT
ORDER BY pizza_name, pizzeria_name;
