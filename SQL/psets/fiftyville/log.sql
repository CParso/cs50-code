-- Keep a log of any SQL queries you execute as you solve the mystery.
-- Theft took place on 28th July
-- Theft took place on Humphrey Street

-- Find the report of the crime relevant to our case
SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND street = 'Humphrey Street';
-- Took place at 10:15am at the bakery

-- Find license plates of car activity at the bakery around the time of the crime
SELECT activity, license_plate, minute FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10;

-- 1 Interviews say a car left the bakery within ten minutes of the theft
-- 2 Some time before the theft the thief was seen withdrawing cash at an ATM on Leggett Street
-- 3 As the thief was leaving the bakery, they called someone who talked to them for less than a minute,
-- 4 In that call they said they were planning to take the earliest flight tomorrow (29th)
SELECT name, day, transcript FROM interviews WHERE month = 7 AND day = 28;

-- 1 Check cars leaving bakery within ten minutes of theft
SELECT license_plate, activity, minute
FROM bakery_security_logs
WHERE day = 28
AND month = 7
AND hour = 10
AND minute
BETWEEN 15 and 25;

-- Find the name and number of those people who left the bakery within the timeframe
SELECT name, phone_number, license_plate
FROM people
WHERE license_plate IN (
    SELECT license_plate
    FROM bakery_security_logs
    WHERE day = 28
    AND month = 7
    AND hour = 10
    AND minute
    BETWEEN 15 and 25);

-- Find the numbers of people who made a call for less than a minute within timeframe
SELECT caller, receiver, duration
FROM phone_calls
WHERE caller IN (
    SELECT phone_number
    FROM people
    WHERE license_plate IN (
        SELECT license_plate
        FROM bakery_security_logs
        WHERE day = 28
        AND month = 7
        AND hour = 10
        AND minute
        BETWEEN 15 and 25))
        AND duration < 60;

-- Find the names of people who accessed the atm and also made a phone call within paramaters
SELECT name
FROM people
WHERE phone_number IN (
    SELECT phone_number
    FROM people
    WHERE id IN (
        SELECT person_id
        FROM bank_accounts
        WHERE account_number IN (
                SELECT account_number
                FROM atm_transactions
                WHERE month = 7
                AND day = 28
                AND atm_location = 'Leggett Street'
            )
    )
)
AND phone_number IN (
    SELECT caller
    FROM phone_calls
    WHERE caller IN (
        SELECT phone_number
        FROM people
        WHERE license_plate IN (
            SELECT license_plate
            FROM bakery_security_logs
            WHERE day = 28
            AND month = 7
            AND hour = 10
            AND minute
            BETWEEN 15 and 25))
        AND duration < 60
);
-- Diana and Bruce

-- Find flights that Diana and Bruce boarded
SELECT flight_id
FROM passengers
WHERE passport_number IN (
    SELECT passport_number
    FROM people
    WHERE name = 'Diana'
    OR name = 'Bruce'
);

-- Find who boarded the earliest flight on the 28th
SELECT id, hour
FROM flights
WHERE month = 7
AND day = 29
AND id IN (
    SELECT flight_id
    FROM passengers
    WHERE passport_number IN (
        SELECT passport_number
        FROM people
        WHERE name = 'Diana'
        OR name = 'Bruce'
    )
);
-- Bruce

-- Find who Bruce called
SELECT name
FROM people
WHERE phone_number IN (
    SELECT receiver
    FROM phone_calls
    WHERE caller = (
        SELECT phone_number
        FROM people
        WHERE name = 'Bruce'
    )
    AND month = 7
    AND day = 28
    AND duration < 60
);
-- Robin

-- Find the destination of the flight Bruce boarded on 29th
SELECT city
FROM airports
WHERE id = (
    SELECT destination_airport_id
    FROM flights
    WHERE month = 7
    AND day = 29
    AND id IN (
        SELECT flight_id
        FROM passengers
        WHERE passport_number IN (
            SELECT passport_number
            FROM people
            WHERE name = 'Bruce'
        )
    )
);