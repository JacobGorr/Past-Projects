/**
 * @file stop.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_STOP_H_
#define SRC_STOP_H_


/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <list>

#include "src/bus.h"
#include "src/passenger.h"
#include "src/data_structs.h"

class Bus;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief The main class for Stop.
 *
 *  Stop is an object that holds an id_
 *  a passenger list, and a pair of doubles
 *  longitude_ and latitude_
 */

class Stop {
 public:
  explicit Stop(int = 0, double = 44.973723, double = -93.235365);
  /**
   * @brief LoadPassengers
   *
   * stop removes the passengers from its list
   * and adds them to the bus that just come to the stop
   */

  void LoadPassengers(Bus *);
  /**
   * @brief AddPassengers
   *
   * stop recieves new passengers (from the generator)
   * to add to its list of passengers waiting
   * @return Int 1 if successfully added passenger
   */

  int AddPassengers(Passenger *);
  /**
   * @brief GetId
   *
   * @return Int of the stops id
   */

  int GetId() const;
  /**
   * @brief Update
   *
   * Called every time unit to update the stops status
   */

  void Update();
  /**
   * @brief HasPassengers
   *
   * @return bool based on if the stop has any passengers waiting
   */

  bool HasPassengers();
  /**
   * @brief NumberOfPassengers
   *
   * @return int with the number of passengers waiting at the stop
   */

  int NumberOfPassengers();
  /**
   * @brief GetLongitude
   *
   * @return double with the longitude_ of stop
   */

  double GetLongitude();
  /**
   * @brief GetLatitude
   *
   * @return double with the latitude_ of the stop
   */

  double GetLatitude();
  /**
   * @brief Report
   *
   * outputs all of the passenger data
   */
  void Report(std::ostream &out) const;


 private:
  int id_;
  std::list<Passenger *> passengers_;  // considered array, vector, queue, list
  // int passengers_present_;  // derived information - not needed?
  double longitude_;
  double latitude_;  // are we using long/lat coords?
};
#endif  // SRC_STOP_H_
