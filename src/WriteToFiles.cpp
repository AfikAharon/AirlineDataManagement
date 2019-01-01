#include "WriteToFiles.h"

/**
 * Constructor WriteToFiles class
 */
WriteToFiles::WriteToFiles() {}

/**
 * The function writes the MyEmployee objects in the file (Employees.txt).
 * The pattern - ID,Seniority,BirthYear,Employer Id,Title.
 *
 * @param employee the given employee to write.
 */
void WriteToFiles::writeEmployee(MyEmployee *employee) {
    ofstream employeeFile;
    employeeFile.open("Employees.txt", ios_base::app);
    employeeFile << employee->getID() + ",";
    employeeFile << to_string(employee->getSeniority()) + ",";
    employeeFile << to_string(employee->getBirthYear()) + ",";
    Employee *employer = employee->getEmployer();
    if (employer == NULL) {
        employeeFile << "NULL,";
    } else {
        employeeFile << employer->getID() + ",";
    }
    employeeFile << to_string(employee->getTitle()) + "\n";
    employeeFile.close();
}

/**
 * The function writes the Plane objects in the file (Planes.txt).
 * The pattern - ID,ModelNumber,
 *      MANAGER x-NAVIGATOR y-FLY_ATTENDANT z-PILOT c-OTHER a,Employer Id,Title.
 *
 * @param plane the given plane to write.
 */
void WriteToFiles::writePlane(Plane *plane) {
    ofstream planeFile;
    planeFile.open("Planes.txt", ios_base::app);
    planeFile << plane->getID() + ",";
    planeFile << to_string(plane->getModelNumber()) + ",";
    map<Jobs, int> crewNeeded = plane->getCrewNeeded();
    planeFile << "MANAGER " + to_string(crewNeeded[MANAGER]) + "+";
    planeFile << "NAVIGATOR " + to_string(crewNeeded[NAVIGATOR]) + "+";
    planeFile << "FLY_ATTENDANT " + to_string(crewNeeded[FLY_ATTENDANT]) + "+";
    planeFile << "PILOT " + to_string(crewNeeded[PILOT]) + "+";
    planeFile << "OTHER " + to_string(crewNeeded[OTHER]) + ",";
    planeFile << to_string(plane->getMaxFirstClass()) + ",";
    planeFile << to_string(plane->getMaxEconomyClass()) + "\n";
    planeFile.close();
    writePlanesModel(plane->getID(), to_string(plane->getModelNumber()));
}

/**
 * The function writes the MyFlight objects in the file (Flights.txt).
 * The pattern - ID,ModelNumber,Date,Source Destination,PlaneID.
 *
 * @param flight the given MyFlight to write.
 */
void WriteToFiles::writeFlight(MyFlight *flight) {
    ofstream flightFile;
    flightFile.open("Flights.txt", ios_base::app);
    flightFile << flight->getID() + ",";
    flightFile << to_string(flight->getModelNumber()) + ",";

    flightFile << flight->getDate().getDate() + ",";
    flightFile << flight->getSource() + ",";
    flightFile << flight->getDestination() + ",";
    flightFile << flight->getPlaneID() + "\n";
    flightFile.close();
}

/**
 * The function writes the MyCustomer objects in the file (Customers.txt).
 * The pattern - ID,FullName,Priority.
 *
 * @param customer the given MyCustomer to write.
 */
void WriteToFiles::writeCustomer(MyCustomer *customer) {
    ofstream customerFile;
    customerFile.open("Customers.txt", ios_base::app);
    customerFile << customer->getID() + ",";
    customerFile << customer->getFullName() + ",";
    customerFile << to_string(customer->getPriority()) + "\n";
    customerFile.close();
}

/**
 * The function writes the Reservation objects in the file (Reservations.txt).
 * The pattern -
 *     ID,Customer ID,Flight ID, FIRST_CLASS or SECOND_CLASS, MaxBaggage.
 *
 * @param reservation the given Reservations to write.
 */
void WriteToFiles::writeReservation(Reservation *reservation) {
    ofstream reservationFile;
    reservationFile.open("Reservations.txt", ios_base::app);
    reservationFile << reservation->getID() + ",";
    reservationFile << reservation->getCustomer()->getID() + ",";
    reservationFile << reservation->getFlight()->getID() + ",";
    if (reservation->getClass() == FIRST_CLASS) {
        reservationFile << "FIRST_CLASS,";
    } else {
        reservationFile << "SECOND_CLASS,";
    }
    reservationFile << to_string(reservation->getMaxBaggage()) + "\n";
    reservationFile.close();
}

/**
 * The function writes the current id counter int the file (countId.txt).
 * The pattern - C:x,E:y,F:z,P:c,R:t.
 *
 * @param customer id counter.
 * @param employee id counter.
 * @param flight id counter.
 * @param plane id counter.
 * @param reservation id counter.
 */
void WriteToFiles::writeId(int customer, int employee, int flight, int plane,
                           int reservation) {
    ofstream idFile;
    idFile.open("countId.txt");
    idFile << "C:" + to_string(customer) + ",";
    idFile << "E:" + to_string(employee) + ",";
    idFile << "F:" + to_string(flight) + ",";
    idFile << "P:" + to_string(plane) + ",";
    idFile << "R:" + to_string(reservation) + "\n";
    idFile.close();
}

/**
 * The function writes the flights in which the employee works.
 * the pattern - E:x,F:y.
 *
 * @param id the employee id
 * @param flights the filghts.
 */
void WriteToFiles::writeEmployeeAtWork(string id, vector<MyFlight *> flights) {
    ofstream employeeAtWorkFile;
    employeeAtWorkFile.open("EmployeeAtWork.txt", ios_base::app);
    int i = 0;
    while (i < flights.size()) {
        employeeAtWorkFile << id + "," + flights[i]->getID() + "\n";
        i++;
    }
    employeeAtWorkFile.close();
}

/**
 * The function writes flights of a particular model plane in
 *  file (FlightOfPlanes.txt).
 * The pattern - P:x,F:y;
 *
 * @param planeId th plane id.
 * @param flights the flights of the plane.
 */
void WriteToFiles::writeFlightsOfPlane(string planeId,
                                       vector<MyFlight *> flights) {
    ofstream planeFlightsFile;
    planeFlightsFile.open("FlightOfPlanes.txt", ios_base::app);
    int i = 0;
    while (i < flights.size()) {
        string flightId = flights[i]->getID();
        planeFlightsFile << planeId + "," + flightId + "\n";
        i++;
    }
    planeFlightsFile.close();
}

/**
 * The function writes for each model plane the flights id.
 *
 * pattern - x,F:y
 *
 * @param id The flight id.
 * @param model The plane model.
 */
void WriteToFiles::writePlanesModel(string id, string model) {
    ofstream modelPlane;
    modelPlane.open("PlaneModels.txt", ios_base::app);
    modelPlane << model + "," + id + '\n';
    modelPlane.close();
}