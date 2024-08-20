WITH T1_user AS
(SELECT 
	id, 
	CASE 
		WHEN name IS NULL THEN 'not defined'
		ELSE name
	END AS name, 
	CASE 
		WHEN lastname IS NULL THEN 'not defined'
		ELSE lastname
	END AS lastname
FROM "user"),

T2_balance AS
(SELECT b.user_id, 
		CASE 
			WHEN T1_user.name IS NULL THEN 'not defined'
			ELSE T1_user.name
		END AS name,
		CASE 
			WHEN T1_user.lastname IS NULL THEN 'not defined'
			ELSE T1_user.lastname
		END AS lastname,
		b.type AS type,
		SUM(b.money) AS volume,
		b.currency_id AS currency_id
FROM T1_user
FULL OUTER JOIN balance AS b ON b.user_id = T1_user.id
GROUP BY b.user_id, T1_user.name, T1_user.lastname, b.type, b.currency_id
ORDER BY b.user_id),

T3_currency AS 
(SELECT T2_balance.name AS name, 
		T2_balance.lastname AS lastname,
		T2_balance.type AS type,
		T2_balance.volume AS volume,
		CASE 
			WHEN c.name IS NULL THEN 'not defined'
			ELSE c.name
		END AS currency_name,
		T2_balance.currency_id AS currency_id
FROM T2_balance 
LEFT OUTER JOIN currency AS c ON T2_balance.currency_id = c.id
	GROUP BY T2_balance.name, T2_balance.lastname, T2_balance.type, T2_balance.volume, c.name, T2_balance.currency_id),

T4_currency_rate AS 
(SELECT id, name, rate_to_usd, updated
FROM currency
WHERE updated IN 
	(SELECT MAX(updated) AS updated
	FROM currency
	GROUP BY id, name)
GROUP BY id, name, rate_to_usd, updated),

T5_UNION_T3_T4 AS 
(SELECT T3_currency.name AS name, 
	    T3_currency.lastname AS lastname,
	    T3_currency.type AS type,
	    T3_currency.volume AS volume,
	    T3_currency.currency_name AS currency_name,
	    CASE 
			WHEN T4_currency_rate.rate_to_usd IS NULL THEN 1
			ELSE T4_currency_rate.rate_to_usd
		END AS last_rate_to_usd
FROM T3_currency 
LEFT OUTER JOIN T4_currency_rate ON T4_currency_rate.id = T3_currency.currency_id)

SELECT *, last_rate_to_usd * volume AS total_volume_in_usd
FROM T5_UNION_T3_T4
ORDER BY name DESC, lastname, type