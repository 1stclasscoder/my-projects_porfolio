-- session 1
BEGIN;

-- session 2
BEGIN;

-- session 1
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;

-- session 2
SET TRANSACTION ISOLATION LEVEL REPEATABLE READ;

-- session 1
SELECT * 
FROM pizzeria 
WHERE name = 'Pizza Hut';

-- session 2
SELECT * 
FROM pizzeria 
WHERE name = 'Pizza Hut';

-- session 1
UPDATE pizzeria 
SET rating = 4 
WHERE name = 'Pizza Hut';

-- session 2
UPDATE pizzeria 
SET rating = 3.6 
WHERE name = 'Pizza Hut';

-- session 1
COMMIT;

-- session 2
COMMIT;

-- session 1
SELECT * 
FROM pizzeria 
WHERE name = 'Pizza Hut';

-- session 2
SELECT * 
FROM pizzeria 
WHERE name = 'Pizza Hut';