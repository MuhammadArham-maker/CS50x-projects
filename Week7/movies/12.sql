-- Lists the titles of all movies in which both Bradley Cooper and Jennifer Lawrence starred
SELECT movies.title
FROM movies
WHERE movies.id IN (
    SELECT stars.movie_id
    FROM stars
    JOIN people ON stars.person_id = people.id
    WHERE people.name = 'Bradley Cooper'
)
AND movies.id IN (
    SELECT stars.movie_id
    FROM stars
    JOIN people ON stars.person_id = people.id
    WHERE people.name = 'Jennifer Lawrence'
);
