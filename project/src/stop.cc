/**
 * @file stop.cc
 * Jacob Gorr, gorrx005
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#include <iostream>
#include <vector>

#include "src/stop.h"

Stop::Stop(int id, double longitude, double latitude) {
    // Defaults to Westbound Coffman Union stop
    // no initialization of list of passengers necessary
    id_ = id;
    longitude_ = longitude;
    latitude_ = latitude;
}


void Stop::LoadPassengers(Bus * bus) {
    // loading some passengers onto a bus
    if (!passengers_.empty()) {
      bus->LoadPassenger(passengers_.front());
      passengers_.front()->GetOnBus();
      passengers_.pop_front();
    }
}


int Stop::AddPassengers(Passenger * pass) {
    // add the passenger to the stop
    passengers_.push_back(pass);
    return 1;
}


int Stop::GetId() const {
    return id_;
}

bool Stop::HasPassengers() {
  if (passengers_.empty() == true) {
    return false;
  }
  return true;
}

int Stop::NumberOfPassengers() {
  return static_cast<int>(passengers_.size());  // guess an error may be here
}

double Stop::GetLongitude() {
  return longitude_;
}

double Stop::GetLatitude() {
  return latitude_;
}

void Stop::Update() {
  for (std::list<Passenger *>::iterator it = passengers_.begin();
       it != passengers_.end(); it++) {
    (*it)->Update();
  }
}

void Stop::Report(std::ostream &out) const {
    out << "ID: " << id_ << std::endl;
    out << "Passengers waiting: " << passengers_.size() << std::endl;
    for (std::list<Passenger *>::const_iterator it = passengers_.begin();
      it != passengers_.end(); it++) {
      (*it)->Report(std::cout);
    }
}
