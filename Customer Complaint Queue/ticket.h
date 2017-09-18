// File:        ticket.h
// Author:      Geoffrey Tien
// Date:        January 18, 2016
// Description: Definition of a customer complaint ticket class

//#pragma once
#ifndef _TICKET_
#define _TICKET_
#include <string>

using namespace std;

class Ticket
{
  private:
    unsigned int ticketid;
    string customername;
    string complaint;

  public:
    // default constructor
    Ticket();
    // parameterized constructor
    Ticket(unsigned int tid, string cname, string compl);

    // MUTATORS

    // ACCESSORS
    unsigned int GetID() const;
    string GetCustomer() const;
    string GetComplaint() const;

    // overloaded operators
    // equality returns true if either ticketid matches,
    //   or customername and complaint match
    bool operator==(const Ticket& tick) const;
    bool operator!=(const Ticket& tick) const;
};
#endif