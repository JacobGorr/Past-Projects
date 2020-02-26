/**
 * @file passenger_factory.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef SRC_PASSENGER_H_
#define SRC_PASSENGER_H_


/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <string>

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for Passenger.
 *
 *  Passengers in an object that holds a name_
 *  an id, and information about bus stops
 *  Along with a static int count for counting total num of passenger objects
 */

class Passenger {
// : public Reporter {
 public:
  explicit Passenger(int = -1, std::string = "Nobody");
  /**
   * @brief Update
   *
   * Called every time unit to update the passengers status
   */

  void Update();
  /**
   * @brief GetOnBus
   *
   * Changes the passenger to start adding to time on bus
   */

  void GetOnBus();
  /**
   * @brief GetTotalWait
   *
   * @return Int of the time_on_bus_ + wait_at_stop_
   */

  int GetTotalWait() const;
  /**
   * @brief IsOnBus
   *
   *  This is a function for getting the status of a passenger
   *  @return Bool if the passenger is on the bus
   *
   */
  bool IsOnBus() const;
  /**
   * @brief GetDestination
   *
   * @return Int of destination_stop_id
   */

  int GetDestination() const;
  /**
   * @brief Report
   *
   *  outputs all of the passenger data
   */

  void Report(std::ostream &out) const;  // updated to take in a ostream

 private:
  std::string name_;
  int destination_stop_id_;
  int wait_at_stop_;
  int time_on_bus_;
  int id_;
  static int count_;  // global count, used to set ID for new instances
};
#endif  // SRC_PASSENGER_H_
