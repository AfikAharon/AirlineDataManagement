#include "MyEmployee.h"

/**
 * Constructor for MyEmployee class
 *
 * @param seniority
 * @param birthYear
 * @param employer
 * @param title
 * @param id
 */
MyEmployee::MyEmployee(int seniority, int birthYear,
                       MyEmployee *employer, Jobs title,
                       string id) {
    this->birthYear = birthYear;
    this->employer = employer;
    this->title = title;
    this->seniority = seniority;
    this->id = id;
    this->flights;
}

vector<MyFlight *> MyEmployee::getFlights() {
    return this->flights;
}

void MyEmployee::addFlights(MyFlight *s) {
    this->flights.push_back(s);
}

Employee *MyEmployee::getEmployer() {
    return this->employer;
}

int MyEmployee::getBirthYear() {
    return this->birthYear;
}

int MyEmployee::getSeniority() {
    return this->seniority;
}

Jobs MyEmployee::getTitle() {
    return this->title;
}

string MyEmployee::getID() {
    return this->id;
}