/*
 Walmart: Movie Theater Seating Challenge - 2020
 File: reservation.hpp
 Author: Efrain Rojas
 Date: 3/3/2021
 Description:
    This file is a header file that describes a reservation
 */

#ifndef reservation_h
#define reservation_h


#include <iostream>
#include <sstream>
#include <vector>

#define ROW 10
#define COL 20

using namespace std;

const int BUFFER_SIZE = 3;

struct reservation{
    string reservationNumber;
    int numberOfSeats;
    vector<pair<int, int>> seatNumbers;
        
    reservation(string resNumber, int numOfSeats){
        this->reservationNumber = resNumber;
        this->numberOfSeats = numOfSeats;
    }
    
    void assignSeatNumbers(vector<pair<int, bool>>& emptySeats);
    string getSeatNumbers();
    
    bool checkSides(vector<pair<int, bool>>& emptySeats, int position, int numbSeats, vector<pair<int,int>>& range);
    bool checkTopRow(vector<pair<int, bool>>& emptySeats, int position, int numbSeats, vector<pair<int,int>>& range);
    bool checkBottomRow(vector<pair<int, bool>>& emptySeats, int position, int numbSeats, vector<pair<int,int>>& range);
    
    string getReservationNumber(){return this->reservationNumber;}
    int getNumberOfSeats(){return this->numberOfSeats;}
    
};


#endif /* reservation_h */
