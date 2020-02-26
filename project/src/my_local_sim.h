/**
 * @file my_local_sim.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_MY_LOCAL_SIM_H_
#define SRC_MY_LOCAL_SIM_H_


/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <string>

#include "src/simulator.h"
#include "src/config_manager.h"
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief The main class for my_Local_Sim.
  *
  * This is the main function of the current project configuration Sim,
  * it creates all the stops and routes and buses and starts the simulation
  * used in configuration sim
  */
class MyLocalSim : public Simulator {
 public:
  explicit MyLocalSim(std::string fileName);
  bool Start() override;
  bool Update() override;
 private:
  std::string file_name_;
  std::vector<int> bus_counters_;
  std::vector<int> bus_start_timings_;
  std::vector<int> time_since_last_bus_generation_;
  int simulation_time_elapsed_;
};

#endif  // SRC_MY_LOCAL_SIM_H_
