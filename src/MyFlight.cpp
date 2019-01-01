#include "MyFlight.h"

/**
 * Constructor fo MyFLight class.
 *
 * @param modelNumber
 * @param date
 * @param source
 * @param destination
 * @param id
 * @param planeId
 */
MyFlight::MyFlight(int modelNumber, Date *date,
                   string source, string destination,
                   string id, string planeId) {
    this->date = date;
    this->id = id;
    this->modelNumber = modelNumber;
    this->destination = destination;
    this->planeId = planeId;
    this->source = source;
}

string MyFlight::getPlaneID() {
    return this->planeId;
}

void MyFlight::setAssignedCrew(list<Employee *> assignedCrew) {
    this->assignedCrew = assignedCrew;
}

void MyFlight::setReservations(list<Reservation *> reservations) {
    this->reservations = reservations;
}

string MyFlight::getID() {
    return this->id;
}

Date MyFlight::getDate() {
    return *(this->date);
}

Date *MyFlight::getPointerToDate() {
    return this->date;
}

void MyFlight::addEmployee(Employee *employee) {
    this->assignedCrew.push_front(employee);
}

void MyFlight::addReservation(Reservation *reservation) {
    this->reservations.push_front(reservation);
}

int MyFlight::getModelNumber() {
    return this->modelNumber;
}

list<Employee *> MyFlight::getAssignedCrew() {
    return this->assignedCrew;
}

string MyFlight::getDestination() {
    return this->destination;
}

string MyFlight::getSource() {
    return this->source;
}

list<Reservation *> MyFlight::getReservations() {
    return this->reservations;
}