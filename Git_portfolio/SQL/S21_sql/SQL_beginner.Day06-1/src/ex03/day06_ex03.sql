CREATE UNIQUE INDEX idx_person_discounts_unique
ON person_discounts(person_id, pizzeria_id);
SET enable_seqscan = OFF;
EXPLAIN ANALYZE
SELECT pv.person_id, pv.pizzeria_id, pd.discount
FROM person_discounts AS pd 
INNER JOIN person_visits AS pv ON pv.person_id = pd.person_id 
	AND pv.pizzeria_id = pd.pizzeria_id
WHERE pd.pizzeria_id = 1 AND pv.person_id = 1