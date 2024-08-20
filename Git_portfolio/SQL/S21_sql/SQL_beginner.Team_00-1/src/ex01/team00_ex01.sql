WITH RECURSIVE rec AS (
  SELECT point1,
    point2,
    cost,
    array [point1] AS mat,
    0::numeric AS sum_cost,
    false AS flag
  FROM nodes as n
  WHERE point1 = 'a'
  UNION
  SELECT nod.point1,
    nod.point2,
    nod.cost,
    rec.mat || nod.point1,
    rec.sum_cost + rec.cost,
    nod.point1 = any(rec.mat) AS flag
  FROM nodes AS nod
    INNER JOIN rec ON nod.point1 = rec.point2
  WHERE flag != true
),
result AS (
  SELECT DISTINCT(mat) AS tour,
    sum_cost AS total_cost
  FROM rec
  WHERE length(mat::varchar) = 11
    AND mat [1] = mat [5]
)
SELECT total_cost,
  tour
FROM result
WHERE total_cost = (
    SELECT min(total_cost)
    FROM result
  )
  OR total_cost = (
    SELECT max(total_cost)
    FROM result
  )
ORDER BY total_cost,
  tour