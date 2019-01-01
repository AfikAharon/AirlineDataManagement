#include <iostream>
#include "MyImplementation.h"

/*
 * Constructor for MyImplementation Class.
 */
MyImplementation::MyImplementation() {
    this->writeToFiles = new WriteToFiles();
    this->readFromFiles = new ReadFromFiles();
    this->flightId = readFromFiles->getFlightId();
    this->planeId = readFromFiles->getPlaneId();
    this->customerId = readFromFiles->getCustomerId();
    this->reservationId = readFromFiles->getReservationId();
    this->employeeId = readFromFiles->getEmployeeId();
}

/**
 * Destructor for MyImplementation class.
 */
MyImplementation::~MyImplementation() {
    writeObjectsToFileAndFreeObjects(YES);
}

/**
 * The function the amount of reservation in the given reservations list.
 *
 * @param reservations The given reservation list.
 * @param cla The Class of the reserveation.
 * @return The amount of the reservation.
 */
int countAmountReservation(list<Reservation *> reservations, Classes cla) {
    list<Reservation *>::iterator it = reservations.begin();
    int counter = 0;
    for (it; it != reservations.end(); it++) {
        if (it.operator*()->getClass() == cla) {
            counter++;
        }
    }
    return counter;
}

/**
 * The function check for available crew member.
 *
 * @param crewNeeded the amount of the crew.
 * @param date The flight fate.
 * @return Return vector of pointers to MyEmployee object.
 */
vector<MyEmployee *>
MyImplementation::checkAvailableEmployee(map<Jobs, int> crewNeeded,
                                         Date date) {
    int amountManager = crewNeeded[MANAGER];
    int amountNavigator = crewNeeded[NAVIGATOR];
    int amountFly = crewNeeded[FLY_ATTENDANT];
    int amountPilot = crewNeeded[PILOT];
    int amountOther = crewNeeded[OTHER];
    bool flag = false;
    bool pushFlag = false;
    int amountEmployeesNeeded = amountManager + amountNavigator + amountFly
                                + amountPilot + amountOther;
    vector<MyEmployee *> availableEmployees;
    MyEmployee *myEmployee = NULL;
    Jobs title;
    for (int i = 0; i < this->employeeId; ++i) {
        unsigned long check = this->employees.count("E:" + to_string(i));
        if (check == 1) {
            myEmployee = this->employees["E:" + to_string(i)];
        } else if (check == 0) {
            myEmployee = this->readFromFiles->getEmployee("E:" + to_string(i));
        }
        // If myEmployee equal to null there is no employee with this id.
        if (myEmployee == NULL) {
            continue;
        }
        title = myEmployee->getTitle();
        vector<MyFlight *> flights = myEmployee->getFlights();
        // Check if the employee available in the given date.
        for (int j = 0; j < flights.size(); ++j) {
            if (flights[j]->getDate() == date) {
                // Indication if the employee are not available.
                flag = true;
                break;
            }
        }
        if (flag) {
            flag = false;
            continue;
        }
        /* Check the title job of the employee
         * and decrease the amount of title job
         */
        if (title == NAVIGATOR && amountNavigator > 0) {
            amountNavigator--;
            pushFlag = true;
        } else if (title == MANAGER && amountManager > 0) {
            amountManager--;
            pushFlag = true;
        } else if (title == FLY_ATTENDANT && amountFly > 0) {
            amountFly--;
            pushFlag = true;
        } else if (title == OTHER && amountOther > 0) {
            amountOther--;
            pushFlag = true;
        } else if (title == PILOT && amountPilot > 0) {
            amountPilot--;
            pushFlag = true;
        } else if (amountFly == 0 && amountManager == 0 &&
                   amountNavigator == 0 && amountOther == 0 &&
                   amountPilot == 0) {
            break;
        }
        if (pushFlag) {
            availableEmployees.push_back(myEmployee);
            pushFlag = false;
        }
    }
    if (amountEmployeesNeeded != availableEmployees.size()) {
        vector<MyEmployee *> temp;
        return temp;
    } else {
        return availableEmployees;
    }
}

/**
 * The function add employee :
 * first check if the employer in the MyImplementation member list,
 * if not check in the files.
 *
 * @param seniority
 * @param birth_year
 * @param employer_id
 * @param title
 * @return
 */
Employee *MyImplementation::addEmployee(int seniority, int birth_year,
                                        string employer_id, Jobs title) {
    unsigned long check = this->employees.count(employer_id);
    MyEmployee *employer = NULL;
    // if check equal to 1 the employer in the MyImplementation member list.
    if (check == 1) {
        employer = this->employees[employer_id];
    // Otherwise check in the files.
    } else if (check == 0 && employer_id != "") {
        employer = this->readFromFiles->getEmployee(employer_id);
    }
    string id = "E:" + to_string(this->employeeId);
    this->employeeId = this->employeeId + 1;
    MyEmployee *employee = new MyEmployee(seniority, birth_year,
                                          employer, title, id);
    this->employees.insert(pair<string, MyEmployee *>(id, employee));
    return employee;
}

/**
 * The function search the employee:
 * first check if the employee in the MyImplementation member list,
 * if not check in the files.
 * @param id
 * @return
 * @throw string exception ig the employee does not exist.
 */
Employee *MyImplementation::getEmployee(string id) {
    unsigned long check = this->employees.count(id);
    MyEmployee *myEmployee = NULL;
    if (check == 1) {
        myEmployee = this->employees[id];
    } else {
        myEmployee = this->readFromFiles->getEmployee(id);
    }
    if (myEmployee == NULL) {
        throw "The Employee does not exist";
    }
    return myEmployee;
}

Plane *MyImplementation::addPlane(int model_number, map<Jobs, int> crew_needed,
                                  map<Classes, int> max_passangers) {
    string id = "P:" + to_string(this->planeId);
    this->planeId = this->planeId + 1;
    int maxFirstClass = max_passangers[FIRST_CLASS];
    int maxSecondClass = max_passangers[SECOND_CLASS];
    MyPlane *myPlane = new MyPlane(model_number, crew_needed, maxFirstClass,
                                   maxSecondClass, id);
    this->planes.insert(pair<string, MyPlane *>(id, myPlane));
    this->modelPlanes[model_number].push_back(id);
    return myPlane;
}

/**
 * The function search the plane in the runtime object or in the files.
 *
 * @param id the plane id
 * @return Plane by given id
 * @throw if there is no plane with the given id.
 */
Plane *MyImplementation::getPlane(string id) {
    unsigned long check = this->planes.count(id);
    MyPlane *myPlane = NULL;
    if (check == 1) {
        myPlane = this->planes[id];
    } else {
        myPlane = this->readFromFiles->getPlane(id);
    }
    if (myPlane == NULL) {
        throw "The Plane does not exist";
    }
    return myPlane;
}

/**
 * The function search the flight in the runtime object or in the files,
 * by call the function getMyFlight.
 *
 * @param id the given id.
 * @return Flight by given id.
 */
Flight *MyImplementation::getFlight(string id) {
    return getMyFlight(id);
}

/**
 * The function search the flight in the runtime object or in the files,
 *
 * @param id the given id.
 * @return Flight by given id.
 */
MyFlight *MyImplementation::getMyFlight(string id) {
    unsigned long check = this->flights.count(id);
    MyFlight *myFlight = NULL;
    // if check equal to 1 the flight not in the runtime objects.
    if (check == 1) {
        myFlight = this->flights[id];
    } else {
        myFlight = this->readFromFiles->getFlight(id);
        // If the crew member is empty get the crew member from the files.
        if (myFlight != NULL && myFlight->getAssignedCrew().empty()) {
            myFlight->setAssignedCrew(this->readFromFiles->getAssignedCrew(id));
        }
        /*
         *  If the Reservations member is empty get the Reservations
         *  member from the files.
         */
        if (myFlight != NULL && myFlight->getReservations().empty()) {
            myFlight->setReservations(
                    this->readFromFiles->getFlightReservations(id, "",
                            GET_BY_FLIGHT_ID));
        }
    }
    if (myFlight == NULL) {
        throw "The flight does not exist";
    }
    return myFlight;
}

/**
 * The function add flight to the runtime objects.
 * The operation:
 * 1. check if there is a available plane.
 * 2. check if there is a available crew
 * (The test is carried out in createFlight function).
 *
 * @param model_number
 * @param date
 * @param source
 * @param destination
 * @return Flight by given id
 */
Flight *MyImplementation::addFlight(int model_number, Date date,
                                    string source,
                                    string destination) {
    bool flag = false;
    bool planeFromFile = false;
    unsigned long check = this->modelPlanes.count(model_number);
    // id of plane by given model number.
    vector<string> planes;
    // check if the the model plane in the runtime objects.
    if (check == 1) {
        planes = this->modelPlanes[model_number];
    } else if (check == 0) {
        // read the plane from the files.
        planes = this->readFromFiles->getPlanesModel(model_number);
        planeFromFile = true;
    }
    if (planes.empty()) {
        throw "There is no available plane";
    }
    vector<MyPlane *> listOfAvailablePlanes;
    MyPlane *tempP = NULL;
    // the loop check if there is a available plane in the given date.
    for (int i = 0; i < planes.size(); ++i) {
        unsigned long check = this->planes.count(planes[i]);
        if (check == 1) {
            tempP = this->planes[planes[i]];
        }
        if (check == 0) {
            tempP = this->readFromFiles->getPlane(planes[i]);
            if (tempP != NULL) {
                // get the plane flight from the files.
                tempP->setFlights(
                        readFromFiles->getFlightOfPlane(tempP->getID()));
            }
        }
        if (tempP != NULL) {
            vector<MyFlight *> flights = tempP->getFlight();
            // if flights list are empty the plane available.
            if (flights.empty()) {
                flag = true;
            } else {
                // otherwise check the flights date.
                for (int j = 0; j < flights.size(); ++j) {
                    if (date == flights[j]->getDate()) {
                        break;
                    } else if (j == flights.size() - 1) {
                        // indication that the plane available.
                        flag = true;
                    }
                }
            }
        }
        if (flag) {
            flag = false;
            listOfAvailablePlanes.push_back(tempP);
        }
    }
    if (listOfAvailablePlanes.empty()) {
        throw "There is no available plane";
    }
    Flight *myFlight = createFlight(listOfAvailablePlanes, date,
                                    model_number, source, destination,
                                    planeFromFile);
    return myFlight;
}

/**
 * The function check if there is a available crew by call the function
 * checkAvailableEmployee, create a new flight and add the flight to the
 * runtime objects.
 *
 * @param listOfAvailablePlanes
 * @param date
 * @param model_number
 * @param source
 * @param destination
 * @param planeFromFile indication if the plane come from the files
 * @return a new flight
 */
Flight* MyImplementation::createFlight(vector<MyPlane *> listOfAvailablePlanes,
        Date date, int model_number, string source, string destination,
        bool planeFromFile) {
    MyPlane* tempP =NULL;
    MyFlight *myFlight = NULL;
    long int check = 0;
    // the loop create a new flight and check if there is available crew.
    for (int l = 0; l < listOfAvailablePlanes.size(); ++l) {
        tempP = listOfAvailablePlanes[l];
        vector<MyEmployee *> availableEmployee = checkAvailableEmployee(
                tempP->getCrewNeeded(), date);
        if (availableEmployee.empty()) {
            throw "There is no available crew";
        }
        string id = "F:" + to_string(this->flightId);
        this->flightId = this->flightId + 1;
        Date *dateP = new Date(date.getDate());
        myFlight = new MyFlight(model_number, dateP, source,
                                destination, id, tempP->getID());
        /*
         * The loop update the list of flight in the employee object and
         * the list of employee int the flight object.
         */
        for (int k = 0; k < availableEmployee.size(); ++k) {
            myFlight->addEmployee(availableEmployee[k]);
            availableEmployee[k]->addFlights(myFlight);
            check = this->employees.count(availableEmployee[k]->getID());
            // check if the employee come from the files , to update the files
            if (check == 0) {
                this->updateEmployeeAtWorkFile[availableEmployee[k]->getID()].push_back(
                        myFlight);
            }
        }
        this->flights.insert(pair<string, MyFlight *>(id, myFlight));
        tempP->addFlight(myFlight);
        // check if the flight come from the files , to update the files.
        if (planeFromFile) {
            this->updatePlaneFlightFile[tempP->getID()].push_back(myFlight);
        }
        if (myFlight != NULL) {
            break;
        }
    }
    return myFlight;
}

/**
 * The function return a reservation by given id:
 * first check if the Reservation in the runtime objects
 * otherewise serach the Reservation in the files.
 *
 * @param id the given id
 * @return Reservation by given id.
 * @throw exception if there is no Reservation.
 */
Reservation *MyImplementation::getReservation(string id) {
    unsigned long check = this->reservation.count(id);
    MyReservation *myReservation = NULL;
    if (check == 1) {
        myReservation = this->reservation[id];
    } else if (check == 0) {
        myReservation = this->readFromFiles->getReservation(id);
        if (myReservation != NULL) {
            MyFlight *myFlight = myReservation->getMyFlight();
            MyCustomer *myCustomer = myReservation->getMyCustomer();
            // check if the program need to update the reservation customer.
            if (myCustomer->getReservations().empty()) {
                myCustomer->setReservation(
                        this->readFromFiles->getFlightReservations("",
                                                     myCustomer->getID(),
                                                     GET_BY_CUSTOMER_ID));
            }
            // check if the program need to update the reservation flight.
            if (myFlight->getReservations().empty()) {
                myFlight->setReservations(
                        this->readFromFiles->getFlightReservations(
                                myFlight->getID(), "", GET_BY_FLIGHT_ID));
            }
            // check if the program need to update the assignedCrew flight.
            if (myFlight->getAssignedCrew().empty()) {
                myFlight->setAssignedCrew(this->readFromFiles->getAssignedCrew(
                        myFlight->getID()));
            }
        }
    }
    if (myReservation == NULL) {
        throw "The reservation does not exist";
    }
    return myReservation;
}

/**
 * The function add a new reservation, check if there is
 * a available seat in the given class.
 *
 * @param customerId
 * @param flightId
 * @param cls
 * @param max_baggage
 * @return a new reservation
 */
Reservation *MyImplementation::addResevation(string customerId, string flightId,
                                          Classes cls, int max_baggage) {
    MyCustomer *customer = getMyCustomer(customerId);
    MyFlight *flight = getMyFlight(flightId);
    list<Reservation *> reservations = flight->getReservations();
    int checkAvailability = countAmountReservation(reservations, cls);
    int amountMaxReservation = 0;
    Plane *plane = getPlane(flight->getPlaneID());
    if (cls == FIRST_CLASS) {
        amountMaxReservation = plane->getMaxFirstClass();
    } else if (cls = SECOND_CLASS) {
        amountMaxReservation = plane->getMaxEconomyClass();
    }
    // check if there is a available seat.
    if (checkAvailability >= amountMaxReservation) {
        throw "There is no available seat";
    }
    string id = "R:" + to_string(this->reservationId);
    this->reservationId = this->reservationId + 1;
    MyReservation *reservation = new MyReservation(customer, flight, cls,
                                                   max_baggage, id);
    flight->addReservation(reservation);
    customer->addReservation(reservation);
    this->reservation[id] = reservation;
    return reservation;
}


/**
 * The function add a new customer, check if the priority between 1-5.
 *
 * @param full_name
 * @param priority
 * @return a new customer
 * @throw exception if the priority is illegal.
 */
Customer *MyImplementation::addCustomer(string full_name, int priority) {
    if (priority < 1 || priority > 5) {
        throw "Illegal priority";
    }
    string id = "C:" + to_string(this->customerId);
    this->customerId = this->customerId + 1;
    MyCustomer *myCustomer = new MyCustomer(id, full_name, priority);
    this->customers[id] = myCustomer;
    return myCustomer;
}

/**
 * The function call the function get MyCustomer that search the customer
 * in the runtime object or in the file and return the customer.
 * @param id
 * @return
 */
Customer *MyImplementation::getCustomer(string id) {
    return getMyCustomer(id);
}

/**
 * To avoid downcast i create a function that return a MyCustomer object.
 * The function search the customer in the runtime object or in the
 * file and return the customer.
 *
 * @param id the given id
 * @return the customer by given id
 * @throw exception if the customer does not exist.
 */
MyCustomer *MyImplementation::getMyCustomer(string id) {
    unsigned long check = this->customers.count(id);
    MyCustomer *myCustomer = NULL;
    if (check == 1) {
        myCustomer = this->customers[id];
    } else {
        myCustomer = this->readFromFiles->getCustomer(id);
        if (myCustomer != NULL && myCustomer->getReservations().empty()) {
            list<Reservation *> reservations =
                    this->readFromFiles->getFlightReservations("", id,
                                                               GET_BY_CUSTOMER_ID);
        }
    }
    if (myCustomer == NULL) {
        throw "The Customer does not exist";
    }
    return myCustomer;
}

/**
 * The function write the objects in the files or free the allocate data.
 *
 * @param indicationIfToFreeData YES or NO
 */
void MyImplementation::writeObjectsToFileAndFreeObjects(
        Indication indicationIfToFreeData) {
    // write or free the employees.
    map<string, MyEmployee *>::iterator itEm = this->employees.begin();
    while (itEm != this->employees.end()) {
        if (indicationIfToFreeData == YES) {
            delete (itEm->second);
        } else if (indicationIfToFreeData == NO) {
            this->writeToFiles->writeEmployee(itEm->second);
            this->writeToFiles->writeEmployeeAtWork(itEm->second->getID(),
                                                   itEm->second->getFlights());
        }
        itEm++;
    }
    // write or free the customers.
    map<string, MyCustomer *>::iterator itCu = this->customers.begin();
    while (itCu != this->customers.end()) {
        if (indicationIfToFreeData == YES) {
            delete (itCu->second);
        } else if (indicationIfToFreeData == NO) {
            this->writeToFiles->writeCustomer(itCu->second);
        }
        itCu++;
    }
    // write or free the planes.
    map<string, MyPlane *>::iterator itPl = this->planes.begin();
    while (itPl != this->planes.end()) {
        if (indicationIfToFreeData == YES) {
            delete (itPl->second);
        } else if (indicationIfToFreeData == NO) {
            this->writeToFiles->writeFlightsOfPlane(itPl->second->getID(),
                                                  itPl->second->getFlight());
            this->writeToFiles->writePlane(itPl->second);
        }
        itPl++;
    }
    // write or free the flights.
    map<string, MyFlight *>::iterator itFl = this->flights.begin();
    while (itFl != this->flights.end()) {
        if (indicationIfToFreeData == YES) {
            delete (itFl->second->getPointerToDate());
            delete (itFl->second);
        } else if (indicationIfToFreeData == NO) {
            this->writeToFiles->writeFlight(itFl->second);
        }
        itFl++;
    }
    // write or free the reservations.
    map<string, MyReservation *>::iterator itRe = this->reservation.begin();
    while (itRe != this->reservation.end()) {
        if (indicationIfToFreeData == YES) {
            delete (itRe->second);
        } else if (indicationIfToFreeData == NO) {
            this->writeToFiles->writeReservation(itRe->second);
        }
        itRe++;
    }
    // write the new flights of plane that located in the files.
    map<string, vector<MyFlight *>>::iterator itUpdateP =
                              this->updatePlaneFlightFile.begin();
    while (itUpdateP != this->updatePlaneFlightFile.end() &&
           indicationIfToFreeData == NO) {
        this->writeToFiles->writeFlightsOfPlane(itUpdateP->first,
                                              itUpdateP->second);
        itUpdateP++;
    }
    // write the new flights of employee that located in the files.
    map<string, vector<MyFlight *>>::iterator itUpdateE =
            this->updateEmployeeAtWorkFile.begin();
    while (itUpdateE != this->updateEmployeeAtWorkFile.end() &&
           indicationIfToFreeData == NO) {
        this->writeToFiles->writeEmployeeAtWork(itUpdateE->first,
                                                itUpdateE->second);
        itUpdateE++;
    }
    // write the ids for reuse.
    if (indicationIfToFreeData == NO) {
        this->writeToFiles->writeId(this->customerId, this->employeeId,
                                    this->flightId, this->planeId,
                                    this->reservationId);
    } else if (indicationIfToFreeData == YES) {
        delete (this->readFromFiles);
        delete (this->writeToFiles);
    }
}

/**
 * The function operation is to call the function
 * writeObjectsToFileAndFreeObjects to write the objects in the files.
 *
 */
void MyImplementation::exit() {
    writeObjectsToFileAndFreeObjects(NO);
}