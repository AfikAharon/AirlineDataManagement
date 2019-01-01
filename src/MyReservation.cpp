#include "MyReservation.h"
#include "MyCustomer.h"

/**
 * Constructor for MyReservation Class.
 *
 * @param customer
 * @param flight
 * @param cla
 * @param maxBaggage
 * @param id
 */
MyReservation::MyReservation(MyCustomer *customer, MyFlight *flight, Classes cla,
                             int maxBaggage, string id) {
    this->id = id;
    this->cla = cla;
    this->flight = flight;
    this->customer = customer;
    this->maxBaggage = maxBaggage;
}

Classes MyReservation::getClass() {
    return this->cla;
}

Customer *MyReservation::getCustomer() {
    return getMyCustomer();
}

MyCustomer *MyReservation::getMyCustomer() {
    return this->customer;
}

MyFlight* MyReservation::getMyFlight() {
    return this->flight;
}

Flight *MyReservation::getFlight() {
    return this->flight;
}

int MyReservation::getMaxBaggage() {
    return this->maxBaggage;
}

string MyReservation::getID() {
    return this->id;
}