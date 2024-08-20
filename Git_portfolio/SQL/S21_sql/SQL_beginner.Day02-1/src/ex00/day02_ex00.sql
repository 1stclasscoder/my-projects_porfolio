SELECT p.name, p.rating
FROM pizzeria AS p
    LEFT OUTER JOIN person_visits AS pv 
    ON pv.pizzeria_id = p.id
WHERE pv.pizzeria_id is NULL;