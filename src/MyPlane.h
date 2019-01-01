#ifndef MYPLANE_H
#define MYPLANE_H


#include <vector>
#include "interface.h"
#include "MyFlight.h"

class MyPlane : public Plane {
private:
    int modelNumber;
    map<Jobs, int> crewNeeded;
    int maxFirstClass;
    int maxEconomyClass;
    string id;
    vector<MyFlight *> flights;

public:
    MyPlane(int modelNumber, map<Jobs, int> crewNeeded, int maxFirstClass,
            int maxEconomyClass, string id);

    virtual int getModelNumber();

    virtual map<Jobs, int> getCrewNeeded();

    virtual int getMaxFirstClass();

    virtual int getMaxEconomyClass();

    virtual string getID();

    void addFlight(MyFlight *flight);

    vector<MyFlight *> getFlight();

    void setFlights(vector<MyFlight *> flights);
};

#endif
