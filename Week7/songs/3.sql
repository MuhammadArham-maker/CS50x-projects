-- List the names of top 5 longest songs, in descending order
SELECT name
FROM songs
ORDER BY duration_ms DESC
LIMIT 5;
