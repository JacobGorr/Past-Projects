/**
 * @file local_simulator.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_LOCAL_SIMULATOR_H_
#define SRC_LOCAL_SIMULATOR_H_


/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>

#include "src/simulator.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief The main class for LocalSimulator.
  *
  * This is the main function of the current project, it creates
  * all the stops and routes and buses and starts the simulation
  */
class LocalSimulator : public Simulator {
 public:
  bool Start() override;
  bool Update() override;
 private:
  std::vector<int> bus_counters_;
  std::vector<int> bus_start_timings_;
  std::vector<int> time_since_last_bus_generation_;
  int simulation_time_elapsed_;
};

#endif  // SRC_LOCAL_SIMULATOR_H_
