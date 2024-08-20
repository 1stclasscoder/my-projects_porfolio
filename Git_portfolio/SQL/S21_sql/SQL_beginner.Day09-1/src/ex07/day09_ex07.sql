CREATE OR REPLACE FUNCTION func_minimum
	(arr VARIADIC numeric[] default '{0}') 
	RETURNS numeric AS $$ 
	SELECT MIN(a1)
	FROM unnest(arr) AS a1;
$$ LANGUAGE SQL;

SELECT func_minimum(VARIADIC arr => ARRAY[10.0, -1.0, 5.0, 4.4]);