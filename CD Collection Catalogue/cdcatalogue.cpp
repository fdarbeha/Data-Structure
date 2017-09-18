// File:        cd.cpp
// Author:      Fatemeh/Neggyn
// Date:        2016-01-07
// Description: Implementation of CDCatalogue class

#include "cdcatalogue.h"
#include <iostream>
using namespace std;
///////////////////////////////
// Constructors / Destructor //
///////////////////////////////

// Default constructor
// Creates an empty CDCatalogue with default array size (4)
CDCatalogue::CDCatalogue()
{
    maxsize =   4;                  //Size of the array holding CDs
    cds     =   new CD[maxsize];    //Creating a dynamic array of size maxsize
    numcds  =   0;                  //Number of CDs in the list
}

// Copy constructor
// Creates a new CDCatalogue object,
// Performs a deep copy of the cat parameter's fields
CDCatalogue::CDCatalogue(const CDCatalogue& cat)
{
    CopyArray(cat);
}

// Destructor
// Releases all memory allocated to private pointer members
CDCatalogue::~CDCatalogue()
{
    delete[] cds;        //release memory assciated
    //with dynamic array (cds)
}

//////////////////////////
// Mutators / Accessors //
//////////////////////////
bool CDCatalogue::Insert(CD disc)
{
    
    if (disc.GetAlbum() != "" && disc.GetArtist() != ""){
        
        if (Find(disc) == -1){                //if disk does not match
                                              //any existing cd in the catalogue
            if(numcds == maxsize){            //insert the CD
                CD* old_cds = cds;            //Else, return false
                maxsize = maxsize * 2;        //If array is full
                cds = new CD[maxsize];        //create a bigger array of size maxsize*2
                
                for(int i = 0; i < numcds; i++)
                    cds[i] = old_cds[i];
                    delete[] old_cds;
                }
            cds[numcds] = disc;
            numcds++;
            return true;
        }
    }
    return false;
}
bool CDCatalogue::Remove(CD disc)
{
    int index = Find(disc);
    if(index == -1)
        return false;
    else
    {
        for(int i = index; i < numcds-1; i++)
            cds[i] = cds[i + 1];
        numcds--;
        return true;
    }
}

int CDCatalogue:: Find(CD disc) const
{
    if(disc.GetArtist() != "" || disc.GetAlbum() != "")
    {
        for(int i = 0; i < numcds; i++)
        {
            if(cds[i] == disc)
                return i;
        }
    }
    return -1;
}
bool CDCatalogue:: Boycott(string dontlikeanymore)
{
    bool removed = false;
    int index = 0;
    if(dontlikeanymore != "")
    {
        while(index < numcds)
        {
            if(cds[index].GetArtist() == dontlikeanymore)
            {
                removed = Remove(cds[index]);
                index--;        //CDs are shifted to the left after remove
            }                   //need to check the current index again
            index++;
        }
    }
    return removed;
}
int CDCatalogue:: Count() const
{
    return numcds;
}
CDCatalogue CDCatalogue:: Join(const CDCatalogue& cat) const
{
    CDCatalogue joint = cat;
    for(int i = 0; i < numcds; i++)
        joint.Insert(cds[i]);
    return joint;
}
CDCatalogue CDCatalogue:: Common(const CDCatalogue& cat) const
{
    CDCatalogue common;
    for(int i = 0; i < numcds; i++)
    {
        if(cat.Find(cds[i]) != -1)
            common.Insert(cds[i]);
    }
    return common;
}
CDCatalogue CDCatalogue:: Split(const CDCatalogue& cat) const
{
    CDCatalogue diff = *this;
    for(int i = 0; i < cat.Count(); i++)
    {
        if(diff.Find(cat.cds[i]) != -1)
            diff.Remove(cat.cds[i]);
    }
    return diff;
}
// Helper method for copy constructor
// Performs deep copy of dynamic array
void CDCatalogue::CopyArray(const CDCatalogue& cat)
{
    maxsize = cat.maxsize;
    numcds = cat.numcds;
    cds = new CD[maxsize];
    for(int i = 0; i < maxsize; i++ )
        cds[i] = cat.cds[i];
}
void CDCatalogue::PrintCollection() const
{
    cout << "+++++++++++++++++++++++++++++++++++++++++++++++" << endl;
    cout << "+          Printing the Collection            +" << endl;
    for(int i = 0; i < numcds; i++){
        cout << "CD# " << i << " -> " << cds[i].GetArtist() << "/" << cds[i].GetAlbum() << endl;
    }
}
