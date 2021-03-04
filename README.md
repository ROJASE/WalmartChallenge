# WalmartChallenge
Walmart: Movie Theater Seating Challenge - 2020
 File: README.txt
 Author: Efrain Rojas
 Date: 3/3/2021



Assumptions:

    1.  File given in terminal is valid. Input file is in same directory.
    
    2.  There are not repeating request numbers. Seat numbers for a row start at
        0 and end at 19.
    
    3.  Customer Satisfaction means that all members of request are able to
        sit next to each other unless greater than one row length. If greater
        than one row length, request will not be fullfilled. To maximize
        customer satisfaction, requests will be processed based on first come
        first served.
        
    4.  For Customer Safety, for every request there will be a 3 seat buffer
        along with a 1 row buffer. Meaning no one can sit directly behind or in
        front of someone.

Solution:

    1.  Read in all Reservation Request
    2.  One at a time based on which order came first. Determine the seat
        location
            a.  All Seats are in emptySeats vector. Int represents position (1D)
                while bool represents if seat is empty or not(false: not empty).
            b.  We use emptySeats to evaluate first available seat in vector to
                determine if it can fullfill the next reservation request.
            c.  We ensure that we have a 3 seat buffer in the same row as well
                as ensuring no one is seated in front or behind of someone.
    3.  Print out Reservation Request
    4.  Print out Seat Number(s).



How to Run Program on Terminal:
    1.  Navigate to file location on terminal (cd ../..)
    2.  Compile Code through comand: g++ -std=c++17 *.cpp
    3.  Run the code: ./a.out < input_file > ouput_file

