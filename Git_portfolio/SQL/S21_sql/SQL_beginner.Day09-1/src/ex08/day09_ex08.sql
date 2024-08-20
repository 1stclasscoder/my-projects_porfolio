CREATE OR REPLACE FUNCTION fnc_fibonacci
	(pstop integer default 10)
	RETURNS SETOF numeric AS $$ 
	DECLARE 
	number_1 numeric = 1;
	number_2 numeric = 1;
    number_3 numeric = 0;
		BEGIN
			return NEXT 1;
			return NEXT 1;
	    FOR i IN 4 ..pstop BY 1
			-- Число фабионачи на счетчику не строгое меньше
			LOOP
			number_3 := number_1 + number_2;
			number_1 := number_2;
			number_2 := number_3;
			return NEXT number_3;
			END LOOP;
		END;
$$ LANGUAGE plpgsql;

select * from fnc_fibonacci(100);
select * from fnc_fibonacci();