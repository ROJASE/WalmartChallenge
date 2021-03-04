/*
 Walmart: Movie Theater Seating Challenge - 2020
 File: main.cpp
 Author: Efrain Rojas
 Date: 3/3/2021
 Description:
    This file will fullfill reservation request based on the given input.
 */

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "reservation.hpp"

using namespace std;

int main() {
    
    // Initialize Vectors
    vector<reservation> allReservations;
    vector<pair<int, bool>> emptySeats(ROW * COL);
    
    // Label possible seat as empty
    for(int i = 0; i < emptySeats.size(); i++){
        emptySeats[i].first = i;
        emptySeats[i].second = true;
    }

    // Reading in reservation requests
    string singleLine;
    while( getline(cin, singleLine)){
        // Parse String
        string resNumber, quantSeats;
        stringstream ss(singleLine);
        ss >> resNumber >> quantSeats;
        
        // Create reservation request and add to vector
        allReservations.push_back(reservation(resNumber, stoi(quantSeats)));
    }
    
    // Evaluate every request
    for( reservation x : allReservations){
        // Assign a seat number if possible
        x.assignSeatNumbers(emptySeats);
        // Print Reservation Number
        cout << x.getReservationNumber() << " ";
        // Print Reserved Seat Numbers
        cout << x.getSeatNumbers() << "\n";
    }

    return 0;
}
