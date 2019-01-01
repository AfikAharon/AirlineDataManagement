#include "MyCustomer.h"

/**
 * Constructor for MyCustomer class.
 *
 * @param id customer id.
 * @param fullName the customer name.
 * @param priority the priority number between 1 to 5.
 */
MyCustomer::MyCustomer(string id, string fullName, int priority) {
    this->fullName = fullName;
    this->id = id;
    this->priority = priority;
}

/**
 *  The function add reservation to the customer.
 *
 * @param reservation the customer reservation.
 */
void MyCustomer::addReservation(Reservation *reservation) {
    this->reservations.push_front(reservation);
}

 void MyCustomer::setReservation(list<Reservation *> reservation) {
    this->reservations = reservation;
}

list<Reservation *> MyCustomer::getReservations() {
    return this->reservations;
}

string MyCustomer::getFullName() {
    return this->fullName;
}

int MyCustomer::getPriority() {
    return this->priority;
}

string MyCustomer::getID() {
    return this->id;
}