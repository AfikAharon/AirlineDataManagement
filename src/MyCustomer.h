#ifndef MYCUSTOMER_H
#define MYCUSTOMER_H


#include "interface.h"

class MyCustomer : public Customer {
private:
    string id;
    string fullName;
    list<Reservation *> reservations;
    int priority;

public:
    MyCustomer(string id, string fullName, int priority);

    virtual string getFullName();

    void addReservation(Reservation *reservation);

    void setReservation(list <Reservation *> reservation);

    virtual int getPriority();

    virtual list<Reservation *> getReservations();

    virtual string getID();
};


#endif
