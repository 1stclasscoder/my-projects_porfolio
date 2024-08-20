SELECT id, name,
	CASE
		WHEN age between 10 and 20 THEN 'interval #1'
		WHEN age between 21 and 23 THEN 'interval #2'
		ELSE 'interval #3'
	END AS interval_info
FROM person
ORDER BY interval_info