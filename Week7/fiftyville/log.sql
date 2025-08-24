-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Lists all the tables in the database
.tables

-- Lists all the columns in a table
.schema

-- Step 1: Get the crime scene reports (theft at 10:55 in the bakery)
SELECT *
FROM crime_scene_reports
WHERE year = 2024
AND month = 7
AND day = 28
AND street = 'Humphrey Street';

-- Step 2: Get more info from the Interviews (witness hints)
SELECT *
FROM interviews
WHERE year = 2024
AND month = 7
AND day = 28
AND transcript LIKE '%bakery%';

-- Step 3: onwards Narrow suspects list step by step
WITH
-- exit records from the bakery (as said by 1st witness)
people_suspects AS (
    SELECT *
    FROM bakery_security_logs b
    WHERE b.year = 2024
    AND b.month = 7
    AND b.day = 28
    AND b.hour = 10
    AND b.activity = 'exit'
    AND b.minute BETWEEN 16 AND 25
),
-- Getting the bakery suspects list
bakery_suspects AS (
    SELECT p.id, p.name, p.phone_number, p.passport_number, p.license_plate
    FROM people_suspects ps
    JOIN people p ON ps.license_plate = p.license_plate
),
-- Getting atm suspects list (as said by 2nd witness)
atm_suspects AS (
    SELECT bs.id, bs.name, bs.phone_number, bs.passport_number
    FROM bakery_suspects bs
    JOIN bank_accounts ba ON bs.id = ba.person_id
    JOIN atm_transactions at ON ba.account_number = at.account_number
    WHERE at.year = 2024
    AND at.month = 7
    AND at.day = 28
    AND at.atm_location = 'Leggett Street'
    AND at.transaction_type = 'withdraw'
),
-- Getting phone calls suspect lists (as said by 3rd witness)
phone_suspects AS (
    SELECT a.id, a.name, a.phone_number, a.passport_number
    FROM atm_suspects a
    JOIN phone_calls pc ON a.phone_number = pc.caller
    WHERE pc.year = 2024
    AND pc.month = 7
    AND pc.day = 28
    AND pc.duration < 60
),
-- Getting flight suspects lists
flights_suspects AS (
    SELECT ps.id, ps.name, ps.phone_number, ps.passport_number, f.destination_airport_id
    FROM phone_suspects ps
    JOIN passengers p ON ps.passport_number = p.passport_number
    JOIN flights f ON p.flight_id = f.id
    JOIN airports a ON f.origin_airport_id = a.id
    WHERE f.year = 2024
    AND f.month = 7
    AND f.day = 29
    AND a.city = 'Fiftyville'
    ORDER BY f.hour, f.minute
    LIMIT 1
)
-- Thief, escaped to & Accomplice
SELECT fs.name AS thief, a.city AS escaped_to, p.name AS accomplice
FROM flights_suspects fs
JOIN airports a ON fs.destination_airport_id = a.id
JOIN phone_calls pc ON fs.phone_number = pc.caller
JOIN people p ON pc.receiver = p.phone_number
WHERE pc.year = 2024
AND pc.month = 7
AND pc.day = 28
AND pc.duration < 60;
