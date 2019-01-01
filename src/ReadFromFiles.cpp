#include <fstream>
#include <unistd.h>
#include <fcntl.h>
#include <sstream>
#include <vector>
#include <iostream>
#include "ReadFromFiles.h"

/**
 * Constructor ReadFromFiles class
 */
ReadFromFiles::ReadFromFiles() {
    readId();
    readModelPlanes();
}

/**
 * Destructor for MyImplementation class.
 */
ReadFromFiles::~ReadFromFiles() {
    map<string, MyEmployee *>::iterator itEm = this->employees.begin();
    while (itEm != this->employees.end()) {
        delete (itEm->second);
        itEm++;
    }
    map<string, MyCustomer *>::iterator itCu = this->customers.begin();
    while (itCu != this->customers.end()) {
        delete (itCu->second);
        itCu++;
    }
    map<string, MyPlane *>::iterator itPl = this->planes.begin();
    while (itPl != this->planes.end()) {
        delete (itPl->second);
        itPl++;
    }
    map<string, MyFlight *>::iterator itFl = this->flights.begin();
    while (itFl != this->flights.end()) {
        delete (itFl->second->getPointerToDate());
        delete (itFl->second);
        itFl++;
    }
    map<string, MyReservation *>::iterator itRe = this->reservation.begin();
    while (itRe != this->reservation.end()) {
        delete (itRe->second);
        itRe++;
    }
}


/**
 * The function check if there is a file with a given name.
 *
 * @param fileName the given name.
 * @return true or false
 */
bool fexists(const string &fileName) {
    ifstream ifile(fileName.c_str());
    return (bool) ifile;
}

/**
 * The function read from a given file line and split the line if the id math.
 *
 * @param file the given file.
 * @param id the given id.
 * @param splitBy :
 *        GET_BY_OBJECT_ID - check the line by the object id
 *                           (at the beginning of the line).
 *        GET_BY_CUSTOMER_ID - check the line by the customer id
 *                           (at the second split).
 *        GET_BY_FLIGHT_ID -   check the line by the flight id
 *                          (at the third split)
 * @return  the split line.
 */
vector<string> readAndSplitsLine(ifstream &file,
                                 string id, Indication splitBy) {
    vector<string> splits;
    string buffer = "";
    string temp = "";
    getline(file, buffer);
    stringstream tempSplit(buffer);
    getline(tempSplit, temp, ',');
    if (temp == id && temp != "" && splitBy == GET_BY_OBJECT_ID) {
        splits.push_back(temp);
        while (getline(tempSplit, temp, ',')) {
            splits.push_back(temp);
        }
    } else if (splitBy == GET_BY_CUSTOMER_ID) {
        string prevString = "";
        prevString = temp;
        getline(tempSplit, temp, ',');
        if (temp == id && temp != "") {
            splits.push_back(prevString);
            splits.push_back(temp);
        }
        while (getline(tempSplit, temp, ',')) {
            splits.push_back(temp);
        }
    } else if (splitBy == GET_BY_FLIGHT_ID) {
        string prevPrevString = "";
        string prevString = "";
        prevPrevString = temp;
        getline(tempSplit, temp, ',');
        prevString = temp;
        getline(tempSplit, temp, ',');
        if (temp == id && temp != "") {
            splits.push_back(prevPrevString);
            splits.push_back(prevString);
            splits.push_back(temp);
        }
        while (getline(tempSplit, temp, ',')) {
            splits.push_back(temp);
        }
    }
    return splits;
}

/**
 * The function search the employee in the files.
 * first check if the employee have been read from the files.
 *
 * @param id the given id.
 * @return employee.
 */
MyEmployee *ReadFromFiles::getEmployee(string id) {
    unsigned long check = this->employees.count(id);
    // check if the employee have benn readed.
    if (check == 1) {
        return this->employees[id];
    }
    if (!fexists("Employees.txt")) {
        return NULL;
    }
    ifstream employeeFile;
    employeeFile.open("Employees.txt");
    vector<string> splits;
    while (!employeeFile.eof()) {
        splits = readAndSplitsLine(employeeFile, id, GET_BY_OBJECT_ID);
        // if the splits empty read the next line.
        if (!splits.empty()) {
            int seniority = atoi(splits[1].c_str());
            int birthYear = atoi(splits[2].c_str());
            string employer = splits[3];
            MyEmployee *e = NULL;
            if (!(employer == "NULL")) {
                e = getEmployee(employer);
            }
            Jobs title = MANAGER;
            int titleValue = atoi(splits[4].c_str());
            if (titleValue == 0) {
                title = MANAGER;
            } else if (titleValue == 1) {
                title = NAVIGATOR;
            } else if (titleValue == 2) {
                title = FLY_ATTENDANT;
            } else if (titleValue == 3) {
                title = PILOT;
            } else if (titleValue == 4) {
                title = OTHER;
            }
            MyEmployee *employee = new MyEmployee(seniority, birthYear, e,
                                                  title, id);
            vector<string> flightsId = getEmployeeAtWork(id, "", GET_FLIGHT_ID);
            for (int i = 0; i < flightsId.size(); i++) {
                MyFlight *flight = getFlight(flightsId[i]);
                if (flight != NULL) {
                    employee->addFlights(flight);
                }
            }
            this->employees.insert(pair<string, MyEmployee *>(id, employee));
            employeeFile.close();
            return employee;
        }
    }
    employeeFile.close();
    return NULL;
}

/**
 * The function read plane from the files:
 * first check if the plane have been read from the files.
 *
 * @param id the given id
 * @return Plane
 */
MyPlane *ReadFromFiles::getPlane(string id) {
    unsigned long check = this->planes.count(id);
    if (check == 1) {
        return this->planes[id];
    }
    if (!fexists("Planes.txt")) {
        return NULL;
    }
    ifstream planeFile;
    planeFile.open("Planes.txt");
    vector<string> splits;
    string buffer = "";
    string temp = "";
    int counter = 0;
    /**
     * the loop split the correct line by check the
     * id at the beginning of the line
     *
     */
    while (!planeFile.eof()) {
        getline(planeFile, buffer);
        stringstream tempSplit(buffer);
        getline(tempSplit, temp, ',');
        if (temp == id) {
            counter++;
            splits.push_back(temp);
            while (getline(tempSplit, temp, ',')) {
                // read the crewNeeded.
                if (counter == 2) {
                    stringstream crewSplit(temp);
                    while (getline(crewSplit, temp, '+')) {
                        stringstream amount(temp);
                        getline(amount, temp, ' ');
                        getline(amount, temp, ' ');
                        splits.push_back(temp);
                    }
                }
                splits.push_back(temp);
                counter++;
            }
        }
    }
    // The block create a MyPlane object.
    if (!splits.empty()) {
        int modelNumber = atoi(splits[1].c_str());
        map<Jobs, int> crewNeeded;
        crewNeeded.insert(pair<Jobs, int>(MANAGER, atoi(splits[2].c_str())));
        crewNeeded.insert(pair<Jobs, int>(NAVIGATOR, atoi(splits[3].c_str())));
        crewNeeded.insert(
                pair<Jobs, int>(FLY_ATTENDANT, atoi(splits[4].c_str())));
        crewNeeded.insert(pair<Jobs, int>(PILOT, atoi(splits[5].c_str())));
        crewNeeded.insert(pair<Jobs, int>(OTHER, atoi(splits[6].c_str())));
        int maxFirstClass = atoi(splits[7].c_str());
        int maxEconomyClass = atoi(splits[8].c_str());
        MyPlane *myPlane = new MyPlane(modelNumber, crewNeeded, maxFirstClass,
                                       maxEconomyClass, id);
        myPlane->setFlights(getFlightOfPlane(id));
        this->planes.insert(pair<string, MyPlane *>(id, myPlane));
        planeFile.close();
        return myPlane;
    }
    planeFile.close();
    return NULL;
}

/**
 * The function search the Customer in the files.
 * first check if the Customer have been read from the files.
 *
 * @param id the given id.
 * @return Customer.
 */
MyCustomer *ReadFromFiles::getCustomer(string id) {
    unsigned long check = this->customers.count(id);
    if (check == 1) {
        return this->customers[id];
    }
    if (!fexists("Customers.txt")) {
        return NULL;
    }
    ifstream customerFile;
    customerFile.open("Customers.txt");
    vector<string> splits;
    while (!customerFile.eof()) {
        splits = readAndSplitsLine(customerFile, id, GET_BY_OBJECT_ID);
        if (!splits.empty()) {
            string fullName = splits[1];
            int priority = atoi(splits[2].c_str());
            MyCustomer *customer = new MyCustomer(id, fullName, priority);
            this->customers.insert(pair<string, MyCustomer *>(id, customer));
            customerFile.close();
            return customer;
        }
    }
    customerFile.close();
    return NULL;
}

/**
 * The function search the Reservation in the files.
 * first check if the Reservation have been read from the files.
 *
 * @param id the given id.
 * @return Reservation.
 */
MyReservation *ReadFromFiles::getReservation(string id) {
    unsigned long check = this->reservation.count(id);
    if (check == 1) {
        return this->reservation[id];
    }
    if (!fexists("Reservations.txt")) {
        return NULL;
    }
    ifstream reservationFile;
    reservationFile.open("Reservations.txt");
    vector<string> splits;
    while (!reservationFile.eof()) {
        splits = readAndSplitsLine(reservationFile, id, GET_BY_OBJECT_ID);
        if (!splits.empty()) {
            MyCustomer *customer = getCustomer(splits[1]);
            MyFlight *flight = getFlight(splits[2]);
            Classes classes;
            if (splits[3] == "FIRST_CLASS") {
                classes = FIRST_CLASS;
            } else {
                classes = SECOND_CLASS;
            }
            int maxBaggage = atoi(splits[4].c_str());
            MyReservation *myReservation = new MyReservation(customer, flight,
                                                             classes,
                                                             maxBaggage, id);
            this->reservation.insert(
                    pair<string, MyReservation *>(id, myReservation));
            reservationFile.close();
            return myReservation;
        }
    }
    reservationFile.close();
    return NULL;
}

/**
 * The function search the Flight in the files.
 * first check if the Flight have been read from the files.
 *
 * @param id the given id.
 * @return Flight.
 */
MyFlight *ReadFromFiles::getFlight(string id) {
    unsigned long check = this->flights.count(id);
    if (check == 1) {
        return this->flights[id];
    }
    if (!fexists("Flights.txt")) {
        return NULL;
    }
    ifstream flightFile;
    flightFile.open("Flights.txt");
    vector<string> splits;
    while (!flightFile.eof()) {
        splits = readAndSplitsLine(flightFile, id, GET_BY_OBJECT_ID);
        if (!splits.empty()) {
            int modelNumber = atoi(splits[1].c_str());
            Date *date = new Date(splits[2]);
            string source = splits[3];
            string destination = splits[4];
            string plane = splits[5];
            MyFlight *myFlight = new MyFlight(modelNumber, date, source,
                                              destination, id, plane);
            this->flights.insert(pair<string, MyFlight *>(id, myFlight));
            flightFile.close();
            return myFlight;
        }
    }
    flightFile.close();
    return NULL;
}

/**
 * The function read the employees that are at work:
 * 1. read by flight id.
 * 2. read by employee id.
 *
 * @param employeeId the given employee id.
 * @param flightId  the given flight id.
 * @param indi:
 *         GET_FLIGHT_ID - get the flights id
 *         GET_EMPLOYEE_ID - get the employees ud
 * @return vector<string> employees id or flights id.
 */
vector<string> ReadFromFiles::getEmployeeAtWork(string employeeId,
                                                string flightId,
                                                Indication indi) {
    vector<string> employeeAtWork;
    if (!fexists("EmployeeAtWork.txt")) {
        return employeeAtWork;
    }
    ifstream employeeAtWorkFile;
    employeeAtWorkFile.open("EmployeeAtWork.txt");
    string buffer = "";
    string temp = "";
    string prevString = "";
    // read by employee id.
    while (!employeeAtWorkFile.eof() && (indi == GET_FLIGHT_ID)) {
        getline(employeeAtWorkFile, buffer);
        stringstream tempSplit(buffer);
        getline(tempSplit, temp, ',');
        if (temp == employeeId) {
            getline(tempSplit, temp, ',');
            employeeAtWork.push_back(temp);
        }
    }
    // read by flight id.
    while (!employeeAtWorkFile.eof() && (indi == GET_EMPLOYEE_ID)) {
        getline(employeeAtWorkFile, buffer);
        stringstream tempSplit(buffer);
        getline(tempSplit, temp, ',');
        prevString = temp;
        getline(tempSplit, temp, ',');
        if (temp == flightId) {
            employeeAtWork.push_back(prevString);
        }
    }
    employeeAtWorkFile.close();
    return employeeAtWork;
}

/**
 * The function reads the ID of the objects.
 */
void ReadFromFiles::readId() {
    if (fexists("countId.txt")) {
        vector<string> split;
        ifstream idFile;
        idFile.open("countId.txt");
        string buffer = "";
        string temp = "";
        getline(idFile, buffer);
        stringstream tempSplit(buffer);
        getline(tempSplit, temp, ',');
        split.push_back(temp);
        while (getline(tempSplit, temp, ',')) {
            split.push_back(temp);
        }
        this->customerId = atoi(split[0].substr(2, split[0].size()).c_str());
        this->employeeId = atoi(split[1].substr(2, split[1].size()).c_str());
        this->flightId = atoi(split[2].substr(2, split[2].size()).c_str());
        this->planeId = atoi(split[3].substr(2, split[3].size()).c_str());
        this->reservationId = atoi(split[4].substr(2, split[4].size()).c_str());
        idFile.close();
    } else {
        this->customerId = 0;
        this->employeeId = 0;
        this->flightId = 0;
        this->planeId = 0;
        this->reservationId = 0;
    }
}

/**
 * The function get the crew member from the files, by get the employees id
 * (call the function getEmployeeAtWork) and after that get the employee from
 * the files.
 *
 * @param id the flight id
 * @return the crew member.
 */
list<Employee *> ReadFromFiles::getAssignedCrew(string id) {
    vector<string> assignedCrewId = getEmployeeAtWork("", id, GET_EMPLOYEE_ID);
    list<Employee *> assignedCrew;
    MyEmployee *tempEmployee;
    for (int i = 0; i < assignedCrewId.size(); ++i) {
        tempEmployee = getEmployee(assignedCrewId[i]);
        if (tempEmployee != NULL) {
            assignedCrew.push_front(tempEmployee);
        }
    }
    return assignedCrew;
}

/**
 * The function get the flight reservations from the files:
 * 1. search by customer id.
 * 2. search by flight id.
 *
 * @param flightID
 * @param customerId
 * @param indi GET_BY_CUSTOMER_ID, GET_BY_FLIGHT_ID
 * @return the flight reservation
 */
list<Reservation *> ReadFromFiles::getFlightReservations(string flightID,
                                                         string customerId,
                                                         Indication indi) {
    list<Reservation *> reservation;
    if (!fexists("Reservations.txt")) {
        return reservation;
    }
    Reservation *tempR = NULL;
    ifstream reservationFile;
    reservationFile.open("Reservations.txt");
    vector<string> splits;
    while (!reservationFile.eof()) {
        if (indi == GET_BY_CUSTOMER_ID) {
            splits = readAndSplitsLine(reservationFile, customerId,
                                       GET_BY_CUSTOMER_ID);
        } else if (indi == GET_BY_FLIGHT_ID) {
            splits = readAndSplitsLine(reservationFile, flightID,
                                       GET_BY_FLIGHT_ID);
        }
        if (!splits.empty()) {
            tempR = getReservation(splits[0]);
        }
        if (tempR != NULL) {
            reservation.push_front(tempR);
        }
        tempR = NULL;
    }
    reservationFile.close();
    return reservation;
}

/**
 * The function get the flights from the files by given plane id.
 *
 * @param id the plane id
 * @return the flights
 */
vector<MyFlight *> ReadFromFiles::getFlightOfPlane(string id) {
    vector<MyFlight *> planeFlights;
    if (!fexists("FlightOfPlanes.txt")) {
        return planeFlights;
    }
    ifstream planeFlightsFile;
    planeFlightsFile.open("FlightOfPlanes.txt");
    string buffer = "";
    string temp = "";
    string prevString = "";
    while (!planeFlightsFile.eof()) {
        getline(planeFlightsFile, buffer);
        stringstream tempSplit(buffer);
        getline(tempSplit, temp, ',');
        if (temp == id) {
            getline(tempSplit, temp, ',');
            MyFlight *myFlight = getFlight(temp);
            // get the crew member
            if (myFlight->getAssignedCrew().empty()) {
                myFlight->setAssignedCrew(getAssignedCrew(myFlight->getID()));

            }
            // get the flight reservations.
            if (myFlight->getReservations().empty()) {
                myFlight->setReservations(
                        getFlightReservations(myFlight->getID(), "",
                                              GET_BY_FLIGHT_ID));
            }
            planeFlights.push_back(myFlight);
        }
    }
    planeFlightsFile.close();
    return planeFlights;
}

/**
 * The function read the PLaneModel file and update the modelPlanes member.
 * key - model plan, value - vector of flights id.
 *
 */
void ReadFromFiles::readModelPlanes() {
    if (fexists("PlaneModels.txt")) {
        ifstream modelPlaneFile;
        modelPlaneFile.open("PlaneModels.txt");
        string buffer = "";
        string temp = "";
        while (!modelPlaneFile.eof()) {
            getline(modelPlaneFile, buffer);
            if (buffer == "") {
                break;
            }
            stringstream tempSplit(buffer);
            getline(tempSplit, temp, ',');
            int model = atoi(temp.c_str());
            getline(tempSplit, temp, ',');
            this->modelPlanes[model].push_back(temp);
        }
        modelPlaneFile.close();
    }
}

/**
 * The function return a list of flights id by given model plane.
 *
 * @param model the model plane.
 * @return list of flights id.
 */
vector<string> ReadFromFiles::getPlanesModel(int model) {
    vector<string> temp;
    if (this->modelPlanes.count(model) == 1) {
        return this->modelPlanes[model];
    }
    return temp;
}

int ReadFromFiles::getFlightId() {
    return this->flightId;
}

int ReadFromFiles::getCustomerId() {
    return this->customerId;
}

int ReadFromFiles::getEmployeeId() {
    return this->employeeId;
}

int ReadFromFiles::getPlaneId() {
    return this->planeId;
}

int ReadFromFiles::getReservationId() {
    return this->reservationId;
}