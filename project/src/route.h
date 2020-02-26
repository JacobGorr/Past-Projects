/**
 * @file route.h
 *
 * @Copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef SRC_ROUTE_H_
#define SRC_ROUTE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <list>
#include <iostream>
#include <string>

#include "./passenger_generator.h"
#include "./stop.h"
#include "src/data_structs.h"

class PassengerGenerator;
class Stop;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for Route.
 *
 *  Route in an object that holds a name_
 *  list of stops, list of distances_between_ each stop
 *  Along with a int of stops and a passenger_generator
 */

class Route {
// : public Reporter {
 public:
  Route(std::string name , Stop ** stops,
        double * distances, int num_stops,
        PassengerGenerator * generator);
  /**
  * @brief Clone
  *
  * @return Route with the same values as the one calling clone
  */

  Route * Clone();
  /**
  * @brief Update
  *
  * Called every timestep, makes generator GeneratePassengers
  * Also calls update on all of the Stops it has access to
  */

  void Update();
  /**
  * @brief Report
  *
  * Outputs data of the route and then calls report on all of its stops
  */

  void Report(std::ostream&);
  /**
  * @brief IsAtEnd
  *
  * @return bool of if the route is at the end of stops
  */

  bool IsAtEnd() const;
  /**
  * @brief NextStop
  *
  * updates the head of the stop list by popping the pop_front
  * alos pops the head of distances_between_ and updates destination_stop_
  */

  void NextStop();  // Change destination_stop_ to next stop
  /**
  * @brief GetDestinationStop
  *
  * @return Stop* with the next stop_ on the route
  */

  Stop * GetDestinationStop() const;    // Get pointer to next stop
  /**
  * @brief
  *
  * @return double with the distance to next stop
  */

  double GetNextStopDistance() const;
  /**
  * @brief GetName
  *
  * @return std::string with the name of the route
  */

  std::string GetName();
  /**
  * @brief GetStops
  *
  * @return list<Stop *> of all the stops in the route
  */

  std::list<Stop *> GetStops();
  /**
  * @brief UpdateRouteData
  *
  * called every update to update the routes information stored in
  * routeData struct
  */

  void UpdateRouteData();
  /**
  * @brief GetRouteData
  *
  * @return RouteData with the routes latest data
  */

  RouteData GetRouteData();

 private:
  int GenerateNewPassengers();       // generates passengers on its route
  PassengerGenerator * generator_;
  std::list<Stop *> stops_;
  std::list<double> distances_between_;  // length = num_stops_ - 1
  std::string name_;
  int num_stops_;
  int destination_stop_index_;  // always starts at zero, no init needed
  Stop * destination_stop_;
  RouteData route_info_;
  // double trip_time_; // derived data - total distance travelled on route
};
#endif  // SRC_ROUTE_H_
