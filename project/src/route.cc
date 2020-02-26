/**
 * @file route.h
 * Jacob Gorr
 * @Copyright 2019 3081 Staff, All rights reserved.
 */
#include "src/route.h"
#include <string>


Route::Route(std::string name, Stop ** stops, double * distances,
             int num_stops, PassengerGenerator * generator) {
  for (int i = 0; i < num_stops; i++) {
    stops_.push_back(stops[i]);
  }
  for (int i = 0; i < num_stops - 1; i++) {
    distances_between_.push_back(distances[i]);
  }

  name_ = name;
  num_stops_ = num_stops;
  generator_ = generator;
  destination_stop_ = stops_.front();
  destination_stop_index_ = destination_stop_->GetId();
}

Route* Route::Clone() {
  Stop** stops;
  stops = new Stop*[num_stops_];
  double* distances;
  distances = new double[num_stops_-1];
  int count = 0;
  for (auto const& i : stops_) {
    stops[count] = i;
    count++;
  }
  count = 0;
  for (auto const& i : distances_between_) {
    distances[count] = i;
    count++;
  }
  return new Route(name_, stops, distances, num_stops_, generator_);
}

void Route::Update() {
  generator_->GeneratePassengers();
  for (std::list<Stop *>::iterator it = stops_.begin(); it != stops_.end();
       it++) {
    (*it)->Update();
  }
  UpdateRouteData();
}

bool Route::IsAtEnd() const {
  if (stops_.front()->GetId() == stops_.back()->GetId()) {
    return true;
  }
  return false;
}

void Route::NextStop() {
  if (IsAtEnd()== false) {
    stops_.pop_front();
    distances_between_.pop_front();
    destination_stop_ = stops_.front();
  }
}

Stop* Route::GetDestinationStop() const {
  return destination_stop_;
}

double Route::GetNextStopDistance() const {
  return distances_between_.front();
}

std::string Route::GetName() {
  return name_;
}

std::list<Stop *> Route::GetStops() {
  return stops_;
}

void Route::UpdateRouteData() {
  route_info_.id = name_;
  std::vector<StopData> copyOfStops;
  StopData stop_data = {};
  Position p;
  for (std::list<Stop *>::const_iterator it = stops_.begin();
      it != stops_.end(); it++) {
    stop_data.id = std::to_string((*it)->GetId());
    p.x = (*it)->GetLatitude();
    p.y = (*it)->GetLongitude();
    stop_data.position = p;
    stop_data.num_people = (*it)->NumberOfPassengers();
    copyOfStops.push_back(stop_data);
  }
}

RouteData Route::GetRouteData() {
  return route_info_;
}

void Route::Report(std::ostream &out) {
  out << "Name: " << name_ << std::endl;
  out << "Num stops: " << num_stops_ << std::endl;
  int stop_counter = 0;
  for (std::list<Stop *>::const_iterator it = stops_.begin();
      it != stops_.end(); it++) {
    (*it)->Report(std::cout);
    stop_counter++;
  }
}
