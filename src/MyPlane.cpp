#include "MyPlane.h"

/**
 * Constructor for MyPlane Class.
 *
 * @param modelNumber
 * @param crewNeeded
 * @param maxFirstClass
 * @param maxEconomyClass
 * @param id
 */
MyPlane::MyPlane(int modelNumber, map<Jobs, int> crewNeeded,
                 int maxFirstClass, int maxEconomyClass, string id) {
    this->id = id;
    this->crewNeeded = crewNeeded;
    this->maxEconomyClass = maxEconomyClass;
    this->maxFirstClass = maxEconomyClass;
    this->modelNumber = modelNumber;
}

map<Jobs, int> MyPlane::getCrewNeeded() {
    return this->crewNeeded;
}

void MyPlane::addFlight(MyFlight *flight) {
    this->flights.push_back(flight);
}

void MyPlane::setFlights(vector<MyFlight *> flights) {
    this->flights = flights;
}

vector<MyFlight*> MyPlane::getFlight() {
    return this->flights;
}

int MyPlane::getMaxEconomyClass() {
    return this->maxEconomyClass;
}

int MyPlane::getModelNumber() {
    return this->modelNumber;
}

int MyPlane::getMaxFirstClass() {
    return this->maxFirstClass;
}

string MyPlane::getID() {
    return this->id;
}