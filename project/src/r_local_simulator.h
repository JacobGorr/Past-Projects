/**
 * @file r_local_simulator.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_R_LOCAL_SIMULATOR_H_
#define SRC_R_LOCAL_SIMULATOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <string>
#include "src/simulator.h"

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief the main class for Regression Test driver
 *
 * This is a hardcoded set of stops and routes used for regression testing,
 * provided by 3081 staff in lab 15. Based to local_simulator.
 *
 */
class rLocalSimulator : public Simulator {
 public:
  bool Start() override;
  bool Update() override;
 private:
  std::vector<int> bus_counters_;
  std::vector<int> bus_start_timings_;
  std::vector<int> time_since_last_bus_generation_;
  int simulation_time_elapsed_;
};

#endif  // SRC_R_LOCAL_SIMULATOR_H_
