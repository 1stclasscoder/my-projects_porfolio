insert into currency values (100, 'EUR', 0.85, '2022-01-01 13:29'); 
insert into currency values (100, 'EUR', 0.79, '2022-01-08 13:29');

SELECT DISTINCT
    COALESCE(u.name, 'not defined') AS name,
    COALESCE(u.lastname, 'not defined') AS lastname,
    currency.name AS name,
     b.money * 
    ( CASE
        WHEN (table1.multiplier_min_date - table1.bal_updated) > (table1.bal_updated - table1.multiplier_max_date) THEN table1.multiplier_max 
        ELSE table1.multiplier_min
    END ) AS calculated_money 
FROM 
(	SELECT 
        b.currency_id,
		b.updated AS bal_updated,
        (	SELECT c.updated
            FROM currency c
            WHERE c.id = b.currency_id AND b.updated < c.updated
            ORDER BY c.updated
            LIMIT 1
        ) AS multiplier_min_date,
	    (	SELECT c.rate_to_usd
            FROM currency c
            WHERE c.id = b.currency_id AND b.updated < c.updated
            ORDER BY c.updated
            LIMIT 1
        ) AS multiplier_min,
        (	SELECT c.updated
            FROM currency c
            WHERE c.id = b.currency_id AND b.updated > c.updated
            ORDER BY c.updated DESC
            LIMIT 1
        ) AS multiplier_max_date,
	    (	SELECT c.rate_to_usd
            FROM currency c
            WHERE c.id = b.currency_id AND b.updated > c.updated
            ORDER BY c.updated DESC
            LIMIT 1
        ) AS multiplier_max
    FROM currency c
    INNER JOIN balance b ON c.id = b.currency_id
    GROUP BY b.currency_id, b.updated
    ORDER BY multiplier_max DESC, multiplier_min
) AS table1
INNER JOIN balance b ON table1.currency_id = b.currency_id AND table1.bal_updated = b.updated
INNER JOIN currency on currency.id = b.currency_id
LEFT JOIN "user" u ON u.id = b.user_id
ORDER BY 1 DESC, 2, 3, 4