// File:        a1simpledriver.cpp
// Author:      (your name here) / Geoffrey Tien
// Date:        January 19, 2016
// Description: Basic test driver
//              This file tests some functions of the CCQueue and DLinkedList classes.
//              Note that only functions which are called will be compiled, therefore you must
//                ensure that every function in your classes is called at least once.
//              Not all special cases have been tested; you will be responsible for adding
//                your own test code and function calls to this file in order to thoroughly
//                test all general and boundary cases for your functions.
//              In general, please ensure that you test:
//               1. invalid parameter(s)
//               2. valid parameter(s), boundary case
//               3. valid parameter(s), general case

#include <cstdlib>
#include <iostream>
#include <string>

#include "ccqueue.h"
#include "dlinkedlist.h"
#include "ticket.h"

using namespace std;

// forward function declarations
void LLTest();
void CCQTest();

// program entry point
int main()
{
    cout << "Entering DLinkedList test function... " << endl;
    LLTest();
    cout << "... DLinkedList test function complete!\n" << endl;
    
    cout << "Entering CCQueue test function... " << endl;
    CCQTest();
    cout << "... CCQueue test function complete!\n" << endl;
    
    system("pause");
    return 0;
}

void LLTest()
{
    // default constructor, InsertFront, InsertBack, ElementAt
    DLinkedList<int> lla;
    lla.InsertBack(0);
    lla.InsertFront(1);
    lla.InsertBack(2);
    lla.InsertBack(3);
    lla.InsertBack(4);
    lla.InsertAt(5, 0);
    lla.InsertAt(6, 5);
    lla.InsertFront(7);
    lla.InsertFront(8);
    lla.PrintList();
    cout << "lla contains " << lla.ElementAt(0) << " at index 0." << endl;
    
    // copy constructor, InsertAt, RemoveAt (with exception)
    DLinkedList<int> llb(lla);
    llb.InsertAt(7, 1);
    try
    {
        int temp; //= llb.RemoveAt(12345);
        temp = llb.RemoveAt(0);
        temp = llb.RemoveAt(8);
        //temp = llb.RemoveAt(9);
        llb.PrintList();
    }
    catch (exception e)
    {
        cout << "Exception in RemoveAt(): " << e.what() << endl;
    }
    
    // assignment operator, IsEmpty, Size, RemoveDuplicates, Contains
    DLinkedList<int> llc;
    if (llc.IsEmpty())
        cout << "llc is empty." << endl;
    else
        cout << "llc is not empty." << endl;
    lla.InsertBack(10);
    llc = lla;
    llc.InsertBack(13);
    llc.InsertBack(13);
    llc.InsertBack(13);
    llc.PrintList();
    cout << "llc contains " << llc.Size() << " items." << endl;
    llc.RemoveDuplicates();
    llc.PrintList();
    lla.PrintList();
    if (llc.Contains(10))
        cout << "10 found in llc." << endl;
    else
        cout << "10 not found in llc." << endl;
    if (llc.Contains(13))
        cout << "13 found in llc." << endl;
    else
        cout << "13 not found in llc." << endl;
}

void CCQTest()
{
    CCQueue ccq;
    ccq.Add("Alrikr", "Video card smoked");
    ccq.Add("Blrikr", "Video card smoked");
    ccq.Add("Clrikr", "Video card smoked");
    ccq.Add("Djornstjerne", "Received wrong colour cable");
    ccq.Add("Cyprianus", "Motherboard DOA");
    ccq.Add("Dietrich", "Order not received");
    ccq.Add("Elisaeus", "Only 931GB on 1TB hard drive");
    cout << "Size of ticket queue: " << ccq.Size() << endl;
    ccq.Service();
    cout << ccq.PrintStatus() << endl;
    ccq.MoveUp(3);
    cout << ccq.PrintStatus() << endl;
    ccq.MoveUp(1);
    cout << ccq.PrintStatus() << endl;
    ccq.MoveDown(3);
    cout << ccq.PrintStatus() << endl;
    ccq.Service();
    cout << ccq.PrintStatus() << endl;
}