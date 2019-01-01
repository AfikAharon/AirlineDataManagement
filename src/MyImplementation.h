#ifndef MYIMPLEMENTATION_H
#define MYIMPLEMENTATION_H

#include "interface.h"
#include "WriteToFiles.h"
#include "ReadFromFiles.h"


class MyImplementation : public Ex2 {
    WriteToFiles *writeToFiles;
    ReadFromFiles *readFromFiles;
    map<string, MyFlight *> flights;
    map<string, MyEmployee *> employees;
    map<string, MyPlane *> planes;
    map<string, MyCustomer *> customers;
    map<string, MyReservation *> reservation;
    map<int, vector<string>> modelPlanes;
    map<string, vector<MyFlight *>> updatePlaneFlightFile;
    map<string, vector<MyFlight *>> updateEmployeeAtWorkFile;
    int flightId;
    int employeeId;
    int planeId;
    int customerId;
    int reservationId;

public:
    MyImplementation();

    ~MyImplementation();

    vector<MyEmployee *> checkAvailableEmployee(map<Jobs, int> crewNeeded,
                                                Date date);

    void writeObjectsToFileAndFreeObjects(Indication indicationIfToFreeData);

    virtual Flight *addFlight(
            int model_number,
            Date date,
            string source,
            string destination);

    Flight *createFlight(vector<MyPlane *> listOfAvailablePlanes,
                         Date date, int model_number, string source,
                         string destination, bool planeFromFile);

    virtual Plane *addPlane(
            int model_number,
            map<Jobs, int> crew_needed,
            map<Classes, int> max_passangers);

    virtual Customer *addCustomer(
            string full_name,
            int priority);

    virtual Reservation *addResevation(
            string customerId,
            string flightId,
            Classes cls,
            int max_baggage);

    virtual Employee *addEmployee(
            int seniority,
            int birth_year,
            string employer_id,
            Jobs title);

    virtual Employee *getEmployee(string id);

    virtual Plane *getPlane(string id);

    virtual Flight *getFlight(string id);

    MyFlight *getMyFlight(string id);


    virtual Customer *getCustomer(string id);

    MyCustomer *getMyCustomer(string id);


    virtual Reservation *getReservation(string id);


    virtual void exit();
};


#endif
