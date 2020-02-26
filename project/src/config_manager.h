/**
 * @file config_manager.h
 *
 * @copyright 2019 3081 Staff, All rights reserved.
 */
#ifndef SRC_CONFIG_MANAGER_H_
#define SRC_CONFIG_MANAGER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <string>


class Route;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A class for reading config.txt files and getting their data
 *
 * A class used by my_local_sim to read in route and stop data
 * from txt files so that they dont need to be hard coded
 * and mutliple sets can exist to test
 */
class ConfigManager {
 public:
        ConfigManager();
        ~ConfigManager();
        /**
        * @brief ReadConfig
        *
        * @param[in] string for filename and location to be read
        * Given a file name it goes through the file and translates
        * the information in it to a list of routes. Files must be of the
        * correct format to get the information.
        */
        void ReadConfig(const std::string filename);
        /**
        * @brief GetRoutes
        *
        * *return std::vector<Route *> of routes it has read in from file.
        *
        */
        std::vector<Route *> GetRoutes() const { return routes; }

 private:
        std::vector<Route *> routes;
};

#endif  // SRC_CONFIG_MANAGER_H_
