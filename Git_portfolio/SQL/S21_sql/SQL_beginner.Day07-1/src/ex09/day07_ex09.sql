WITH T1 AS (
SELECT address AS address,
	   ROUND(MAX(age)-(MIN(age)/MAX(age)::NUMERIC),2) AS formula,
	   ROUND(AVG(age),2) AS average
FROM person 
GROUP BY address
ORDER BY address)

SELECT *,
	CASE 
		WHEN formula > average THEN true
		ELSE false
	END
FROM T1;
