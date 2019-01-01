#ifndef MYFLIGHT_H
#define MYFLIGHT_H

#include "interface.h"

class MyFlight : public Flight {
private:
    int modelNumber;
    list<Reservation *> reservations;
    list<Employee *> assignedCrew;
    Date *date;
    string source;
    string destination;
    string id;
    string planeId;

public:
    MyFlight(int modelNumber,
             Date *date, string source,
             string destination, string id, string planeId);

    virtual int getModelNumber();

    string getPlaneID();

    virtual list<Reservation *> getReservations();

    virtual list<Employee *> getAssignedCrew();

    void setReservations(list<Reservation *> reservations);

    void setAssignedCrew(list<Employee *> assignedCrew);

    void addEmployee(Employee *employee);

    void addReservation(Reservation *reservation);

    virtual Date getDate();

    Date *getPointerToDate();

    virtual string getSource();

    virtual string getDestination();

    virtual string getID();

};


#endif
