/**
 * @file bus.h
 * Jacob Gorr
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_BUS_H_
#define SRC_BUS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <list>
#include <string>

#include "src/passenger.h"
#include "src/route.h"
#include "src/stop.h"
#include "src/data_structs.h"

class PassengerUnloader;
class PassengerLoader;
class Route;
class Stop;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for Bus.
 *
 *  Bus in an object that holds a name_
 *  an inbound and outbound route, a max capacity and speed
 *  Along with a list of passengers that are riding on it
 */

class Bus {
// : public Reporter {
 public:
  Bus(std::string name, Route * out, Route * in, int capacity = 60,
                                                 double speed = 1);
  /**
  * @brief LoadPassenger
  *
  * @param[in] passenger* for passenger to be added to bus
  * @return bool if the passenger being added successfully got on the bus
  */

  bool LoadPassenger(Passenger *);  // returning revenue delta
  /**
  * @brief UnloadPassengers
  *
  *
  * removes passengers on bus whose destination_stop_id matches there
  * destination id
  */

  void UnloadPassengers();
  /**
  * @brief Move
  *
  * @return bool if the move function was successfully
  * updates the bus's distance_remaining_ based on its speed
  */

  bool Move();
  /**
  * @brief Update
  *
  * while there the route isn't at the end it calls move()
  * once the bus makes it to the next stop it first UnloadPassengers
  * then it LoadPassenger from the stop and finally it updates route with
  * nextStop()
  * once the outbound route is at the end it switches to the incoming_route_
  */

  void Update();
  /**
  * @brief UpdateBusData
  *
  * Called every time update is called to update the bus_info_ bus_data
  * data_struct to be updated with the latest information
  */

  void UpdateBusData();
  /**
  * @brief GetBusData
  *
  * @return bus_data struct containing all the bus's information
  */

  BusData GetBusData();
  /**
  * @brief GetName
  *
  * @return std::string with the name of the bus
  */

  std::string GetName();
  /**
  * @brief GetNextStop
  *
  * @return Stop* the next stop the bus is moving towards
  */

  Stop * GetNextStop();
  /**
  * @brief GetNumPassengers
  *
  * @return size_t with the number of passengers on the bus
  */

  size_t GetNumPassengers();
  /**
  * @brief GetCapacity
  *
  * @return int of the maxium capacity of the bus
  */

  int GetCapacity();
  /**
  * @brief IsTripComplete
  *
  * @return bool if the bus is at the end of its routes
  */

  bool IsTripComplete();
  /**
  * @brief Report
  *
  * outputs the bus's information then calles report on all its passengers
  */

  void Report(std::ostream &out);

 private:
  std::list<Passenger *> passengers_;
  int passenger_max_capacity_;
  std::string name_;
  double speed_;  // could also be called "distance travelled in one time step"
  int route_num_;  // 0 = outgoing, 1 = incoming determines which route to use
  Route * outgoing_route_;
  Route * incoming_route_;
  double distance_remaining_;
  BusData bus_info_;
  // when negative?, unload/load procedure occurs
                              // AND next stop set
  // double revenue_; // revenue collected from passengers, doesn't include
                      // passengers who pay on deboard
  // double fuel_;   // may not be necessary for our simulation
  // double max_fuel_;
};
#endif  // SRC_BUS_H_
