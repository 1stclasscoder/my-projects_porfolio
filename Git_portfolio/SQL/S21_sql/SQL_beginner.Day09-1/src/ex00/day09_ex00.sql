create table person_audit
( created timestamp with time zone NOT NULL DEFAULT current_timestamp,
  type_event char(1) NOT NULL default 'I',
  row_id bigint NOT NULL,
  name varchar,
  age integer,
  gender varchar,
  address varchar,
  constraint ch_type_event check (type_event IN ('I', 'D', 'U'))
  );

CREATE OR REPLACE FUNCTION fnc_trg_person_insert_audit() 
	RETURNS TRIGGER AS $trg_person_insert_audit$
	BEGIN
		IF (TG_OP = 'INSERT') THEN
			INSERT INTO person_audit(created, type_event, row_id, name, age, gender, address)
			VALUES (current_timestamp, 'I', NEW.id, NEW.name, NEW.age, NEW.gender, NEW.address);
		END IF;
		RETURN NULL;
	END;
$trg_person_insert_audit$ LANGUAGE plpgsql;

	
CREATE TRIGGER trg_person_insert_audit 
	AFTER INSERT ON person
FOR EACH ROW EXECUTE FUNCTION fnc_trg_person_insert_audit();

INSERT INTO person(id, name, age, gender, address) 
	VALUES (10,'Damir', 22, 'male', 'Irkutsk');