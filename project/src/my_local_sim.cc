/**
 * @file my_local_sim.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#include "src/my_local_sim.h"

#include <vector>
#include <list>

#include "src/bus.h"
#include "src/stop.h"
#include "src/route.h"
#include "src/random_passenger_generator.h"
#include "src/config_manager.h"

MyLocalSim::MyLocalSim(std::string fileName) {
  file_name_ = fileName;
}

bool MyLocalSim::Start() {
  simulation_time_elapsed_ = 0;

  int num_round_trips_ = 1;
  for (int i = 0; i < num_round_trips_; i++) {
    time_since_last_bus_generation_.push_back(0);
  }

  ConfigManager my_manager_;
  std::string my_file_header_ = file_name_;  // convert char* to string
  std::cout << file_name_ << std::endl;
  my_manager_.ReadConfig(my_file_header_);
  std::vector<Route *> my_routes_ = my_manager_.GetRoutes();
  std::cout << my_manager_.GetRoutes().size() << std::endl;

  for (std::vector<Route *>::const_iterator it = my_routes_.begin();
      it != my_routes_.end(); it++) {
    prototype_routes_.push_back(*it);
  }

  for (std::vector<Route *>::const_iterator it = prototype_routes_.begin();
      it != prototype_routes_.end(); it++) {
    (*it)->Report(std::cout);
  }

  bus_counters_.push_back(10000);  // copied

  // This will eventually be replaced by configuration/command line argument
  bus_start_timings_.push_back(10);
  return true;
}


bool MyLocalSim::Update() {
  simulation_time_elapsed_++;
  std::cout << "~~~~~~~~~~~~~ The time is now " << simulation_time_elapsed_;
  std::cout << " ~~~~~~~~~~~~~" << std::endl;

  // various route-indexed list iterators
  std::vector<int>::iterator bus_gen_timing_iter = bus_start_timings_.begin();
  std::vector<int>::iterator bus_counter_iter = bus_counters_.begin();
  std::vector<Route *>::iterator prototype_route_iter =
       prototype_routes_.begin();

  // increase each time since last bus
  // various iterators parallel the time_since_last iterator
  for (std::vector<int>::iterator it = time_since_last_bus_generation_.begin();
      it != time_since_last_bus_generation_.end();
      it++, bus_gen_timing_iter++, bus_counter_iter++) {
    (*it)++;

    // if time since last [index] == bus gen timing[index]
    if (0 >= (*bus_gen_timing_iter)) {
      // create a new bus! routes are:
      // prototype_routes_[index * 2] & prototype_routes_[index * 2 + 1]
        //  Route * outbound = (*prototype_route_iter);
        //  prototype_route_iter++;
        //  Route * inbound = (*prototype_route_iter);
        //  prototype_route_iter++;
        Route * outbound = *prototype_routes_.begin();
        Route * inbound = *prototype_routes_.begin();
      active_buses_.push_back(new Bus(std::to_string((*bus_counter_iter)),
                                  outbound->Clone(), inbound->Clone(), 60, 1));
      (*bus_counter_iter)++;
      (*bus_gen_timing_iter) = 10;
    } else {
      prototype_route_iter++;
      prototype_route_iter++;
      (*bus_gen_timing_iter)--;
    }
  }

  // for each bus
  for (std::list<Bus *>::iterator bus_iter = active_buses_.begin();
      bus_iter != active_buses_.end(); bus_iter++) {
    // update bus
    (*bus_iter)->Update();
    // bus report
    (*bus_iter)->Report(std::cout);

    // REQUIRES USE OF IsTripComplete, which was not required
    // Buses which are "done" will just keep having Update() called
//<<<<<<< HEAD
    //  Students MAY need to deal with this, not sure yet...
    // remove bus if trip is complete
     if ((*bus_iter)->IsTripComplete()) {
      bus_iter = active_buses_.erase(bus_iter);
      bus_iter--;
    }
//=======
    //   Students MAY need to deal with this, not sure yet...
    // remove bus if trip is complete
    // if ((*bus_iter)->IsTripComplete()) {
    //   bus_iter = active_buses_.erase(bus_iter);
    //   bus_iter--;
    // }
//>>>>>>> support-code
  }

  // for each stop
  for (std::vector<Route *>::iterator route_iter = prototype_routes_.begin();
      route_iter != prototype_routes_.end(); route_iter++) {
    // update stop
    (*route_iter)->Update();
    (*route_iter)->Report(std::cout);
  }

  return true;
}
