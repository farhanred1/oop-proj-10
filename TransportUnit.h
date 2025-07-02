// TransportUnit.h
#pragma once
#include <string>
#include <iostream>
using namespace std;

class TransportUnit {
private:
    string id;
    string city;
    int time;

public:
    // Constructor declaration
    TransportUnit(const string& id, const string& city, int time);

    // Getter methods
    string getID() const;
    string getCity() const;
    int getTime() const;

    // Setter methods
    void setID(const string& id);
    void setCity(const string& city);
    void setTime(int time);

    // Pure virtual method for polymorphism
    virtual void displayInfo() const = 0;
};
