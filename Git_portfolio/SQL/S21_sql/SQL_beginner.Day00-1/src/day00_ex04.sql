SELECT name || ' (age:' || age || ',gender:''' || gender || ''',address:''' || address || ''')' AS person_information
FROM person
order by person_information DESC