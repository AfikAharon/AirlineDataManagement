#ifndef READFROMFILES_H
#define READFROMFILES_H

#include "interface.h"
#include "MyFlight.h"
#include "MyEmployee.h"
#include "MyPlane.h"
#include "MyCustomer.h"
#include "MyReservation.h"

enum Indication {
    GET_FLIGHT_ID,
    GET_EMPLOYEE_ID,
    GET_BY_FLIGHT_ID,
    GET_BY_CUSTOMER_ID,
    GET_BY_OBJECT_ID,
    YES,
    NO
};

class ReadFromFiles {
private:
    map<string, MyFlight *> flights;
    map<string, MyEmployee *> employees;
    map<string, MyPlane *> planes;
    map<string, MyCustomer *> customers;
    map<string, MyReservation *> reservation;
    map<int, vector<string>> modelPlanes;
    int flightId;
    int employeeId;
    int planeId;
    int customerId;
    int reservationId;

public:
    ReadFromFiles();

    MyEmployee *getEmployee(string id);

    MyPlane *getPlane(string id);

    MyCustomer *getCustomer(string id);

    MyReservation *getReservation(string id);

    MyFlight *getFlight(string id);

    vector<string> getEmployeeAtWork(string employeeId, string flightId,
                                     Indication indi);

    list<Reservation *> getFlightReservations(string flightID,
                                              string customerId,
                                              Indication indi);

    list<Employee *> getAssignedCrew(string id);

    vector<MyFlight *> getFlightOfPlane(string id);

    void readModelPlanes();

    vector<string> getPlanesModel(int model);

    void readId();

    int getFlightId();

    int getEmployeeId();

    int getPlaneId();

    int getCustomerId();

    int getReservationId();

    ~ReadFromFiles();
};


#endif
