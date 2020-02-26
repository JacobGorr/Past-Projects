/**
 * @file stop.cc
 * Jacob Gorr, gorrx005
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#include "src/bus.h"

Bus::Bus(std::string name, Route * out, Route * in,
         int capacity, double speed) {
  name_ = name;
  outgoing_route_ = out;
  incoming_route_ = in;
  passenger_max_capacity_ = capacity;
  speed_ = speed;
  distance_remaining_ = 0;
  route_num_ = 0;
}


bool Bus::LoadPassenger(Passenger * new_passenger) {
  if ((unsigned)passenger_max_capacity_ > passengers_.size()) {
    passengers_.push_back(new_passenger);
    return true;
  }
  return false;
}

void Bus::UnloadPassengers() {  // currently only calls on outgoing route
  for (std::list<Passenger *>::iterator it = passengers_.begin();
       it != passengers_.end(); it++) {
    if (route_num_ == 0) {
      if ((*it)->GetDestination() == outgoing_route_->GetDestinationStop()
           ->GetId() ) {
        passengers_.erase(it);
        it = passengers_.begin();  // need to come up with a better solution
      }
    } else if (route_num_ == 1) {
      if ((*it)->GetDestination() == incoming_route_->GetDestinationStop()
          ->GetId() ) {
        passengers_.erase(it);
        it = passengers_.begin();
      }
    }
  }
}

bool Bus::Move() {
  distance_remaining_ = distance_remaining_ - speed_;
  return true;
}

void Bus::UpdateBusData() {
  bus_info_.id = name_;
  bus_info_.position.x = 0;  // longitude
  bus_info_.position.y = 0;  // latitude
  bus_info_.num_passengers = passengers_.size();
  bus_info_.capacity = passenger_max_capacity_;
}

BusData Bus::GetBusData() {
  return bus_info_;
}

std::string Bus::GetName() {
  return name_;
}

Stop * Bus::GetNextStop() {
  return outgoing_route_->GetDestinationStop();  // temp, needs to be updated
}

size_t Bus::GetNumPassengers() {
  return passengers_.size();
}

int Bus::GetCapacity() {
  return passenger_max_capacity_;
}

bool Bus::IsTripComplete() {
  if (incoming_route_->IsAtEnd() == true) {
    return true;
  }
  return false;
}

void Bus::Update() {  //  using common Update format
  if (outgoing_route_->IsAtEnd() == false) {
    if (distance_remaining_ > 0) {
      Move();
      for (std::list<Passenger *>::iterator it = passengers_.begin();
           it != passengers_.end(); it++) {
        (*it)->Update();
      }
    } else if (distance_remaining_ >= 0) {
      UnloadPassengers();
      Stop* s = outgoing_route_->GetDestinationStop();
      while (s->HasPassengers()) {
        s->LoadPassengers(this);
      }
      outgoing_route_->NextStop();
      distance_remaining_ = outgoing_route_->GetNextStopDistance();
    }
  //  if the outgoing route is at the end
  } else if (incoming_route_->IsAtEnd() == false) {
    route_num_ = 1;
    if (distance_remaining_ > 0) {
      Move();
      for (std::list<Passenger *>::iterator it = passengers_.begin();
           it != passengers_.end(); it++) {
        (*it)->Update();
      }
    } else if (distance_remaining_ >= 0) {
      UnloadPassengers();
      Stop* s = incoming_route_->GetDestinationStop();
      while (s->HasPassengers()) {
        s->LoadPassengers(this);
      }
      incoming_route_->NextStop();
      distance_remaining_ = incoming_route_->GetNextStopDistance();
  }
  }
  UpdateBusData();
  }


void Bus::Report(std::ostream &out) {
  out << "Name: " << name_ << std::endl;
  out << "Speed: " << speed_ << std::endl;
  out << "Distance to next stop: " << distance_remaining_ << std::endl;
  out << "\tPassengers (" << passengers_.size() << "): " << std::endl;
  for (std::list<Passenger *>::iterator it = passengers_.begin();
       it != passengers_.end(); it++) {
    (*it)->Report(std::cout);
  }
}
