-- session 1
BEGIN;

-- session 2
BEGIN;

-- session 1
SET TRANSACTION ISOLATION LEVEL READ COMMITTED;

-- session 2
SET TRANSACTION ISOLATION LEVEL READ COMMITTED;

-- session 1
SELECT SUM(rating) 
FROM pizzeria;

-- session 2
insert into pizzeria values (10,'Kazan Pizza', 5);

-- session 2
COMMIT;

-- session 1
SELECT SUM(rating) 
FROM pizzeria;

-- session 1
COMMIT;

-- session 1
SELECT SUM(rating) 
FROM pizzeria;


-- session 2
SELECT SUM(rating) 
FROM pizzeria;
