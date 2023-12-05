--In 13.sql, write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.
--Your query should output a table with a single column for the name of each person.
--There may be multiple people named Kevin Bacon in the database. Be sure to only select the Kevin Bacon born in 1958.
--Kevin Bacon himself should not be included in the resulting list.
SELECT DISTINCT p.name
FROM people p
JOIN stars s1 ON p.id = s1.person_id
JOIN movies m1 ON s1.movie_id = m1.id
JOIN stars s2 ON m1.id = s2.movie_id
JOIN people kevin ON s2.person_id = kevin.id
WHERE kevin.name = 'Kevin Bacon' AND kevin.birth = 1958 AND p.name != 'Kevin Bacon';
