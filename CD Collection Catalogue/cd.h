//
//  cd.h
//  Assignment#1
//
//  Created by fatemeh darbehani on 2016-01-10.
//  Copyright © 2016 DEVELOPED BY SFU COMPUTER SCIENSE STUDENTS. All rights reserved.
//
// File:        cd.h
// Author:      Geoffrey Tien
// Date:        2016-01-07
// Description: Declaration of a CD class

//#ifndef cd_h
//#define cd_h
#pragma once
#include <string>
using namespace std;

class CD
{
private:
    string artist;
    string albumtitle;
    
public:
    // Default constructor
    CD();
    
    // Parameterized constructor
    CD(string artistname, string title);
    
    // Destructor not required.
    // Class does not contain any member variables in dynamic memory
    
    // MUTATORS
    // Methods for updating CD's private fields
    // Update will only occur if parameter is not empty string
    // Returns true if update is successful, false otherwise.
    bool UpdateArtist(string artistname);
    bool UpdateAlbum(string title);
    bool Update(string artistname, string title);
    
    // ACCESSORS
    // Methods for retrieving CD information
    string GetArtist() const;
    string GetAlbum() const;
    
    // OVERLOADED OPERATORS
    // equality is true if all fields match
    // not-equals is true if any field does not match
    bool operator==(const CD& disc) const;
    bool operator!=(const CD& disc) const;
};

//#endif /* cd_h */
