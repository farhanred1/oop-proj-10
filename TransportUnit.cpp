// TransportUnit.cpp
#include "TransportUnit.h"

// Constructor definition
TransportUnit::TransportUnit(const string& id, const string& city, int time)
    : id(id), city(city), time(time) {}

// Getter methods definitions
string TransportUnit::getID() const {
    return id;
}

string TransportUnit::getCity() const {
    return city;
}

int TransportUnit::getTime() const {
    return time;
}

// Setter methods
void TransportUnit::setID(const string& id) {
    this->id = id;
}

void TransportUnit::setCity(const string& city) {
    this->city = city;
}

void TransportUnit::setTime(int time) {
    this->time = time;
}
