-- Keep a log of any SQL queries you execute as you solve the mystery.

--Find scene crime description
SELECT description
FROM crime_scene_reports
WHERE month = 7 AND day = 28
AND street = 'Humphrey Street';
-- Result:  Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery.
--Interviews were conducted today with three witnesses who were present at the time
--each of their interview transcripts mentions the bakery.
--Littering took place at 16:36. No known witnesses.

--Take a look of the witnesess
 SELECT *
FROM interviews
WHERE month = 7 AND day = 28;
--| 163 | Raymond | 2021 | 7     | 28  | As the thief was leaving the bakery, they called someone who talked to them for less than a minute.
--In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow.
--The thief then asked the person on the other end of the phone to purchase the flight ticket.
--| 162 | Eugene  | 2021 | 7     | 28  | I don't know the thief's name, but it was someone I recognized.
--Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing
--some money.
--| 161 | Ruth    | 2021 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot
--and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot
--in that time frame

--HINTS: Flight Ticket buy 28/7 to fly 29/7
        --Withdrew some money in ATM before robbery in Leggett Street
        --Car in the bakery parking and ten minutes after the robbery left
        --Phone call after leaving the bakery

-- Take a look at bakery security to look for cars that left the parking ten minutes after the robbery (10:25 more o less)
SELECT *
FROM bakery_security_logs
WHERE day = 28 AND month = 7 and hour = 10
AND activity = 'exit';
--Principal suspects:
    -- exit 10:18: 94KL13X
    -- exit 10:18: 6P58WS2
    -- exit 10:19: 4328GD8
    -- exit 10:20: G412CB7
    -- exit 10:21: L93JTIZ
    -- exit 10:23: 322W7JE
    -- exit 10:23: 0NTHK55
    -- exit 10:35: 1106N58

--Take a look at atm transaction to look for withdrae transaction in an ATM located in Leggett Street
SELECT *
FROM atm_transactions
WHERE day = 28 AND month = 7 AND year = 2021
AND transaction_type = 'withdraw'
AND atm_location = 'Leggett Street';

--Take a look at phone calls less than 60 seconds
SELECT *
FROM phone_calls
WHERE day = 28 AND month = 7 AND year = 2021
AND duration <= 60;

--Take a look at the flights in the next day of the robbery
SELECT *
FROM flights
WHERE day = 29 AND month = 7 AND year = 2021;


--People, their seats and their destination in the flights the day after the robbery
SELECT
    people.name,
    passengers.seat,
    origin_airport.full_name AS Origin_Airport,
    destination_airport.full_name AS Arrive_Airport
FROM
    people
JOIN
    passengers ON passengers.passport_number = people.passport_number
JOIN
    flights ON flights.id = passengers.flight_id
JOIN
    airports AS origin_airport ON origin_airport.id = flights.origin_airport_id
JOIN
    airports AS destination_airport ON destination_airport.id = flights.destination_airport_id
WHERE
    day = 29 AND month = 7 AND year = 2021
    AND origin_airport.full_name LIKE 'Fiftyville%'
ORDER BY
    destination_airport.full_name;

--Finding destination airport
SELECT * FROM airports
WHERE id IN
    (SELECT flights.destination_airport_id FROM flights
JOIN airports ON flights.origin_airport_id = airports.id
WHERE flights.day = 29 AND flights.month = 7 AND airports.city = 'Fiftyville'
ORDER BY flights.hour, flights.minute
LIMIT 1);

-- name of the person who made the phone call
SELECT * FROM people
WHERE phone_number IN
    (SELECT phone_calls.caller FROM phone_calls
WHERE caller IN
   (
    SELECT people.phone_number FROM people
    WHERE id IN
    (SELECT bank_accounts.person_id FROM bank_accounts
        WHERE account_number IN
        (SELECT atm_transactions.account_number FROM atm_transactions
        WHERE day = 28 AND month = 7 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'
        )
    )
    AND name IN
    (SELECT people.name FROM people
    JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
    WHERE passport_number IN
        (SELECT passengers.passport_number FROM passengers
        WHERE flight_id IN
            (SELECT flights.id FROM flights
            JOIN airports ON flights.origin_airport_id = airports.id
            WHERE flights.day = 29 AND flights.month = 7 AND airports.city = 'Fiftyville'ORDER BY flights.hour, flights.minute
LIMIT 1
            )
        )
    AND bakery_security_logs.day = 28 AND bakery_security_logs.month = 7 AND bakery_security_logs.hour = 10 AND bakery_security_logs.minute > 15 AND bakery_security_logs.minute < 25
    GROUP BY people.license_plate
    )
   )
   AND month = 7 AND day = 28
    );

-- Bruce talked for 45 seconds on 7/28 with this number  (375) 555-8161
SELECT * FROM people WHERE phone_number = '(375) 555-8161';
-- Robin

