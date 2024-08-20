SELECT per1.name AS person_name1, 
	per2.name AS person_name2, 
	per1.address AS common_address
FROM person AS per1, person as per2
WHERE per1.address = per2.address
AND per1.id > per2.id
ORDER BY person_name1, person_name2, common_address;