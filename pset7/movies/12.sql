SELECT title
FROM movies
    JOIN stars ON movies.id = stars.movie_id
    JOIN people ON people.id = stars.person_id
WHERE name IN ("Johnny Depp", "Helena Bonham Carter")   -- in the list of two names
GROUP BY movie_id       -- group rows with the same movie_id
HAVING COUNT(*) = 2;    -- and only list the ones with 2 count (because both names were in it)