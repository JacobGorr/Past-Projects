/**
 * @file configuration_sim.cc
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#include <iostream>
#include <fstream>

#include "src/my_local_sim.h"
#include "src/config_manager.h"
// #include "src/configuration_simulator.h"


int main(int argc, char**argv) {
  // NOTE: this usage will change depending on
  //       how you build your config_sim classes
  //   E.g., how will you handle getting the length of simulation value?
  std::cout << "Usage: ./build/bin/configuration_sim <config_filename>";
  std::cout << std::endl;

  int rounds_ = 200;
  // std::fstream fileHeader;
  std::string name_;
  // Check command line params for config file name
  if (argc == 1) {
    std::cout<< "Only one argument entered, using defualt config.txt";
    std::cout<< std::endl;
    name_ = "config.txt";
  } else if (argc == 2) {
    name_ = (argv[1]);
    // name_ = "config/" + name_;
  } else {
    std::cout<< "Extra arguments passed to program, discarding them";
    std::cout<< std::endl;
    name_ = (argv[1]);
    // name_ = "config/" + name_;
  }
  // name_ = "config/" + name_;
  std::cout<< name_ <<std::endl;
  std::fstream fileHeader("config/"+name_);
  fileHeader.open(name_);
  if (fileHeader.is_open() == false) {
    std::cout<< "file failed to open"<< std::endl;
    return 0;
  } else {
    std::cout<< "File opened"<< std::endl;
    fileHeader.close();
  }

  MyLocalSim sim(name_);


  std::cout << "/*************************" << std::endl << std::endl;
  std::cout << "         STARTING" << std::endl;
  std::cout << "        SIMULATION" << std::endl;
  std::cout << "*************************/" << std::endl;

  sim.Start();

  std::cout << "/*************************" << std::endl << std::endl;
  std::cout << "           BEGIN" << std::endl;
  std::cout << "          UPDATING" << std::endl;
  std::cout << "*************************/" << std::endl;

  for (int i = 0; i < rounds_; i++) {
    sim.Update();
  }

  std::cout << "/*************************" << std::endl << std::endl;
  std::cout << "        SIMULATION" << std::endl;
  std::cout << "         COMPLETE" << std::endl;
  std::cout << "*************************/" << std::endl;

  // if filename arg present
  //   Create ConfigManager
  //   Call ReadConfig
  //   Create ConfigurationSimulator
  //   Call Start on ConfigurationSimulator
  //   Start for loop, length of simulation (where from?)
  //     Call Update on ConfigurationSimulator
  // else
  //   echo info to the user about needing a config file name

  return 0;
}
