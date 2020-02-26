/**
 * @file random_passenger_generator.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */

#ifndef SRC_RANDOM_PASSENGER_GENERATOR_H_
#define SRC_RANDOM_PASSENGER_GENERATOR_H_


/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <list>
#include <random>
#include <ctime>

#include "src/passenger_generator.h"
#include "src/stop.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief The main class for random_passenger_generator.
  *
  * this is used to make passengers as they "appear" at stops
  */
class Stop;  // forward declaration

class RandomPassengerGenerator : public PassengerGenerator{
 public:
  RandomPassengerGenerator(std::list<double>, std::list<Stop *>);
  int GeneratePassengers() override;

 private:
  static std:: minstd_rand0 my_rand;
};

#endif  // SRC_RANDOM_PASSENGER_GENERATOR_H_
