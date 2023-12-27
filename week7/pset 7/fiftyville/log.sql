--checking for description of theft
SELECT description FROM crime_scene_reports WHERE year = 2021 AND month = 7 AND day = 28 AND street='Humphrey Street';
-- Two things happened  Only one is related to theft. Other is related to littering.
--going to ask for name of people in interview and transcript
SELECT name, transcript FROM interviews WHERE day = 28  AND month = 7  AND year = 2021;
 --how do witnesses know the could be amoung thief
 --3 witnesses-Ruth,Eugene,Lily

 --Eugene->((Earlier this morning )serch for account no. of person at atm money withdrawing $ at Leggett Street)
 SELECT account_number  FROM atm_transactions
 WHERE day = 28
   AND month = 7
   AND year = 2021
   AND atm_location = 'Leggett Street'
   AND transaction_type = 'withdraw';
--name assosiated will disclose/join later for simplicity
SELECT name FROM people
JOIN bank_accounts ON people.id=bank_accounts.person_id
JOIN atm_transactions
    ON bank_accounts.account_number = atm_transactions.account_number
 WHERE atm_transactions.day = 28
   AND atm_transactions.month = 7
   AND atm_transactions.year = 2021
   AND atm_transactions.atm_location = 'Leggett Street'
   AND atm_transactions.transaction_type = 'withdraw';

--ruth->saw thief drive away in a car from bakery shop within ten minutes of theft->(searching for bakery shop security)
SELECT name FROM people
JOIN  bakery_security_logs ON  people.license_plate=bakery_security_logs.license_plate
WHERE hour = 10
   AND minute>=15
   AND minute<=25
   AND day = 28
   AND month = 7
   AND year = 2021
   AND activity='exit';
--joining names from previous prospective theifs
SELECT name FROM people
JOIN bakery_security_logs ON people.license_plate = bakery_security_logs.license_plate
WHERE hour = 10
  AND minute >= 15
  AND minute <= 25
  AND day = 28
  AND month = 7
  AND year = 2021
  AND activity = 'exit'
  AND name IN (
    SELECT name FROM people
    JOIN bank_accounts ON people.id = bank_accounts.person_id
    JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
    WHERE atm_transactions.day = 28
    AND atm_transactions.month = 7
    AND atm_transactions.year = 2021
    AND atm_transactions.atm_location = 'Leggett Street'
    AND atm_transactions.transaction_type = 'withdraw'
  );
--Bruce Luca Iman Diana may be thief

--Raymond->heard the phonecall of thief and they were  planning to take the earliest flight out of Fiftyville tomorrow and also asked the person on phone call to purchase ticket->(call records <1min,earliest flight of fiftyvilley )
--first clue ->phone call
SELECT name,phone_calls.caller,phone_calls.duration FROM people
JOIN phone_calls ON people.phone_number=phone_calls.receiver
WHERE day = 28
  AND month = 7
  AND year = 2021
  AND phone_calls.duration <= 60
  ORDER BY phone_calls.duration;
 --call reciever are  Luca       | (609) 555-5876 | 60
 --receiver are  Bruce   | (367) 555-5533 | 45 ;;; Diana   | (770) 555-1861 | 49  ,checked by this
 SELECT name,phone_calls.receiver,phone_calls.duration FROM people
JOIN phone_calls ON people.phone_number=phone_calls.caller
WHERE day = 28
  AND month = 7
  AND year = 2021
  AND phone_calls.duration <= 60
  ORDER BY phone_calls.duration;

--2.> earliest flight to fiftyville ->finding names who are on that flight
--airport name by this i->   8 |  CSF          | Fiftyville Regional Airport

-- flight on 29 ,7 ,2021 from Fiftyville airport ORDER BY time (earliest)
SELECT full_name,city,flights.id,flights.hour, flights.minute FROM airports
JOIN flights ON airports.id=flights.destination_airport_id
WHERE flights.origin_airport_id IN
(
 SELECT id FROM airports
 WHERE city ='Fiftyville'
)
AND flights.year=2021
AND flights.month=7
AND flights.day=29
ORDER BY hour,minute ASC;
--LaGuardia Airport   | New York City | 36 | 8 : 20    <-earliest flight
-- pasengers on that flight
SELECT passengers.flight_id, name, passengers.passport_number, passengers.seat
  FROM people
  JOIN passengers
    ON people.passport_number = passengers.passport_number
  JOIN flights
    ON passengers.flight_id = flights.id
 WHERE flights.year = 2021
   AND flights.month = 7
   AND flights.day = 29
   AND flights.hour = 8
   AND flights.minute = 20
 ORDER BY passengers.passport_number;

-- bruce is in all of the tables/queries so he must be the theif , and escaped to New York City as seen above
---- Robin must be the accomplice who purchased the flight ticket, and helped bruce
