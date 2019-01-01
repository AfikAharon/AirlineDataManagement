#ifndef MYRESERVATION_H
#define MYRESERVATION_H


#include "interface.h"
#include "MyCustomer.h"
#include "MyFlight.h"

class MyReservation : public Reservation {
private:
    MyCustomer *customer;
    MyFlight *flight;
    Classes cla;
    int maxBaggage;
    string id;

public:
    MyReservation(MyCustomer *customer, MyFlight *flight, Classes cla,
                  int maxBaggage, string id);

    virtual Customer *getCustomer();

    MyCustomer *getMyCustomer();

    virtual Flight *getFlight();

    MyFlight *getMyFlight();

    virtual Classes getClass();

    virtual int getMaxBaggage();

    virtual string getID();
};


#endif
