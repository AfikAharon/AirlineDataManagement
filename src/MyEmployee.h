#ifndef MYEMPLOYEE_H
#define MYEMPLOYEE_H

#include <vector>
#include "interface.h"
#include "MyFlight.h"

class MyEmployee : public Employee {
private:
    int seniority;
    int birthYear;
    MyEmployee *employer;
    Jobs title;
    string id;
    vector<MyFlight *> flights;

public:
    MyEmployee(int seniority, int birthYear, MyEmployee *employer, Jobs title,
               string id);

    void addFlights(MyFlight *s);

    vector<MyFlight *> getFlights();

    virtual int getSeniority();

    virtual int getBirthYear();

    virtual Employee *getEmployer();

    virtual Jobs getTitle();

    virtual string getID();
};


#endif
