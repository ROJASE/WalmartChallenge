/*
 Walmart: Movie Theater Seating Challenge - 2020
 File: reservation.cpp
 Author: Efrain Rojas
 Date: 3/3/2021
 Description:
    This file implements function that were in the header file.
 */
#include "reservation.hpp"


/* assignValues
    
    This function assigns the second part of a pair in vector of pair<int, bool>
    to passed in value for a range of elements.
 
    input: given vector, start and end locations, value to be assigned
    output: void, but elements modified
 */
void assignValues(vector<pair<int, bool>>& emptySeats, int start, int stop, bool value){
    for(int i = start; i <= stop; i++){
        // Assign value to second part of pair
        emptySeats[i].second = value;
    }
}


/* assignSeatNumbers
    
    This function assigns seat numbers to requests as well as eliminating
    reserved seats from given vector.
    
    input: given vector with empty seats
    output: void, but vectors modified
 */
void reservation::assignSeatNumbers(vector<pair<int, bool>>& emptySeats){
    bool seatAssigned = false;
    bool topBool, sideBool, bottomBool;
    topBool = sideBool = bottomBool = false;
    vector<pair<int, int>> invalidSeats;

    
    if(!emptySeats.empty() && numberOfSeats <= COL){
        
        for (int i = 0; i < emptySeats.size() && !seatAssigned; i++){
            if(emptySeats[i].second){
                if(i < COL){ // First Row
                    
                    // Check Sides
                    sideBool = checkSides(emptySeats, emptySeats[i].first, this->getNumberOfSeats(), invalidSeats);
                    
                    // Check Bottom Row
                    bottomBool = checkBottomRow(emptySeats, emptySeats[i].first, this->getNumberOfSeats(), invalidSeats);
                    
                                    
                    // Erase Elements
                    if(bottomBool && sideBool){
                        seatAssigned = true;
                        // Seat Numbers
                        seatNumbers.push_back(invalidSeats[0]);
                        assignValues(emptySeats, invalidSeats[0].first, invalidSeats[0].second, false);
                           
                    }
                    
                    invalidSeats.clear();
                    topBool = sideBool = bottomBool = false;
                    
                }else if(i >= COL && i < ROW*COL - COL){ // Middle Rows
                    
                    // Check Sides
                    sideBool = checkSides(emptySeats, emptySeats[i].first, this->getNumberOfSeats(), invalidSeats);
                    
                    // Check Bottom Row
                    bottomBool = checkBottomRow(emptySeats, emptySeats[i].first, this->getNumberOfSeats(), invalidSeats);
                    
                    // Check Top Row
                    topBool = checkTopRow(emptySeats, emptySeats[i].first, this->getNumberOfSeats(), invalidSeats);
                    
                                    
                    // Erase Elements
                    if(bottomBool && sideBool && topBool){
                        seatAssigned = true;
                        // Seat Numbers
                        seatNumbers.push_back(invalidSeats[0]);
                        assignValues(emptySeats, invalidSeats[0].first, invalidSeats[0].second, false);
                    }
                    
                    invalidSeats.clear();
                    topBool = sideBool = bottomBool = false;
                    
                }else{ // Last Row
                    // Check Sides
                    sideBool = checkSides(emptySeats, emptySeats[i].first, this->getNumberOfSeats(), invalidSeats);
                                    
                    // Check Top Row
                    topBool = checkTopRow(emptySeats, emptySeats[i].first, this->getNumberOfSeats(), invalidSeats);
                    
                                    
                    // Erase Elements
                    if(topBool && sideBool){
                        seatAssigned = true;
                        // Seat Numbers
                        seatNumbers.push_back(invalidSeats[0]);
                        assignValues(emptySeats, invalidSeats[0].first, invalidSeats[0].second, false);
                        
                    }
                    
                    invalidSeats.clear();
                    topBool = sideBool = bottomBool = false;
                }
            }
            
        }
    }else{
        this->seatNumbers.clear();
    }
}

/* getSeatNumbers
    
    This function returns a string of seats that were assigned to request and
    are comman-delimited.
 
    input: void
    output: assigned seats
 */
string reservation::getSeatNumbers(){
    // Default Message
    string returnString = "No Availabe To Fullfill Request";
    
    if(!this->seatNumbers.empty()){
        // Clear Default Message
        returnString.clear();
        
        // Calculate Letter representation of Row
        int intRow = seatNumbers[0].first / COL;
        char currentRow = 'A' + intRow;
        
        // Add assigned seats with comma-delimiter
        for(int i = 0; i < numberOfSeats - 1; i++){
            int tempCol = (seatNumbers[0].first + i) % 20;
            returnString += currentRow;
            returnString += to_string(tempCol);
            returnString += ',';
        }
        
        // Add last assigned seat to string
        int tempCol = (seatNumbers[0].first + numberOfSeats - 1) % 20;
        returnString += currentRow;
        returnString += to_string(tempCol);
        
    }else{
        return returnString;
    }
    
    return returnString;
}


/* checkSides
    This function checks to make sure there is at least a 3 seat buffer on either
    side of request.
 
    input: vector of available seats, the position of seat being evaluated,
            the number of seats for request, and a vector of seat that are
            potentially unavailable now.
    ouput: true if there is a 3 seat buffer, otherwise false. Range vector is
            also modified.
 */
bool reservation::checkSides(vector<pair<int, bool>>& emptySeats, int position, int numbSeats, vector<pair<int,int>>& range){
    // Initialize Variables
    bool valid = true;
    int currentRow = position / COL;
    
    // Check it has consequetive seats in same row
    for(int i = 0; i < numbSeats; i++){
        auto x = make_pair(position + i, true);
        if (emptySeats.end() != find(emptySeats.begin(), emptySeats.end(), x)){
            if (currentRow != (position + i)/COL){
                return false;
            }
        }else{
            return false;
        }
    }
    
    // Check Left Side
    for(int i = 1; i <= BUFFER_SIZE; i++){
        if((position - i)% COL >= 0){
            auto x = make_pair(position - i, true);
            if (emptySeats.end() == find(emptySeats.begin(), emptySeats.end(), x)){
                return false;
            }
        }
    }
    
    // Check Right Side
    for(int i = 1; i <= BUFFER_SIZE && ((position + numbSeats + i)% COL <= 19); i++){
        auto x = make_pair(position + numbSeats - 1 + i, true);
        if (emptySeats.end() == find(emptySeats.begin(), emptySeats.end(), x)){
            return false;
        }
    }
    
    // Range
    range.push_back(make_pair(position, position + numbSeats - 1));
    
    return valid;
}


/* checkTopRow
    This function check to make sure there is no one seated directly in front of
    reserved seats
 
    input: vector of available seats, the position of seat being evaluated,
            the number of seats for request.
    ouput: true if there on one in front of reserved seats, otherwise false.
 */
bool reservation::checkTopRow(vector<pair<int, bool>>& emptySeats, int position, int numbSeats, vector<pair<int,int>>& range){
    bool valid = true;
    int currentRow = position / COL;    
    
    // Check it has consequetive seats in same row
    for(int i = 0; i < numbSeats; i++){
        // Checks Current Row
        auto x = make_pair(position + i, true);
        if (emptySeats.end() != find(emptySeats.begin(), emptySeats.end(), x)){
            if (currentRow != (position + i)/COL){
                return false;
            }
        }else{
            return false;
        }
        // Checks Row in Front
        auto x1 = make_pair(position + i - COL, true);
        if(emptySeats.end() == find(emptySeats.begin(), emptySeats.end(), x1)){
            return false;
        }
    }
        
    return valid;
}

/* checkBottomRow
    This function check to make sure there is no one seated directly in behind
    reserved seats
 
    input: vector of available seats, the position of seat being evaluated,
            the number of seats for request.
    ouput: true if there on one in behind of reserved seats, otherwise false.
 */
bool reservation::checkBottomRow(vector<pair<int, bool>>& emptySeats, int position, int numbSeats, vector<pair<int,int>>& range){
    bool valid = true;
    int currentRow = position / COL;
    
    // Check it has consequetive seats in same row and bottom row
    for(int i = 0; i < numbSeats; i++){
        //Checks Current Row
        auto x = make_pair(position + i, true);
        if (emptySeats.end() != find(emptySeats.begin(), emptySeats.end(), x)){
            if (currentRow != (position + i)/COL){
                return false;
            }
        }else{
            return false;
        }
        // Checks Row Behind
        auto x1 = make_pair(position + i + COL, true);
        if(emptySeats.end() == find(emptySeats.begin(), emptySeats.end(), x1)){
            return false;
        }
    }
    
    return valid;
}
