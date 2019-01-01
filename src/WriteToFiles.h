#ifndef WRITETOFILES_H
#define WRITETOFILES_H

#include <fstream>
#include <fcntl.h>
#include "interface.h"
#include "MyEmployee.h"
#include "MyPlane.h"
#include "MyCustomer.h"

class WriteToFiles {
public:
    WriteToFiles();

    void writeEmployee(MyEmployee *employee);

    void writePlane(Plane *plane);

    void writeFlight(MyFlight *flight);

    void writeCustomer(MyCustomer *customer);

    void writeReservation(Reservation *reservation);

    void writeEmployeeAtWork(string id, vector<MyFlight *> flights);

    void writeId(int customer, int employee, int flight,
                 int plane, int reservation);

    void writeFlightsOfPlane(string planeId, vector<MyFlight *> flights);

    void writePlanesModel(string id, string model);
};


#endif
