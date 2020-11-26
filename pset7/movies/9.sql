SELECT name
FROM movies
    JOIN stars ON movies.id = stars.movie_id
    JOIN people ON people.id = stars.person_id
WHERE year == "2004"
GROUP BY name
ORDER BY birth;