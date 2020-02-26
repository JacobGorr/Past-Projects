/**
 * @file mainpage.h
 * Jacob Gorr
 * @copyright 2019, All rights reserved.
 */
#ifndef SRC_MAINPAGE_H_
#define SRC_MAINPAGE_H_
/*! \mainpage My Personal Index Page
 *
 * \section intro_sec Introduction
 *
 *
 *
 *
 *Transit Simulator is a simulator with the goal of emulating buses following
 *routes through a city picking up passengers as it travels between stops. It
 *can be run many different routes as long as either the config.txt file is
 *edited or if a new file is created with the route data. The goal of running
 *this program is find the optimal number of buses for how many passengers
 *arrive at a stop so that our passengers don't have to wait for too long.
 *To simulate our bus system I primarily worked with 4 classes a Route, Stop,
 *Passenger, and Bus class. To actually utalize these classes I make use of a
 *driver class and a class called my_local_sim to run the simulation.
 *
 *In this iteration of transit sim there are 2 distinct versions of the program
 *that both use the same code. A visual simulator and a configuration simulator.
 *
 *How this project is orgizinzed is by seperating things into their own
 *directory. All the shared code of .cc and .h files is located in the src
 *directory. Then there is a driver directory which holds all the different
 *files for driving the different simulators. Tests are kept in the test directory.
 *The config directory holds .txt files with different routes and stops to be
 *passed to configuration_sim. Everything that is compiled or built is placed in
 *build directory. For more documentation it is located in the docs directory.
 *
 *Passenger is the most basic class, it holds a name, id int, an int of how long
 *it was waiting at the stop and an int of how long it is on the bus, and finally
 *the passengers destination stop id. The passenger is only responsible for
 *updating its own time, everything else is done in the other classes.
 *
 *Stop is slightly more complex the information it holds its a stop id,
 *and a longitude and latitude, these values are used in the visual simulator.
 *The last thing it holds is a list of passengers currently waiting at its stop.
 *Stops mostly interface
 *with Bus when they are adding passengers to the bus from their list of
 *passengers. At the moment all stops are created once when transit simulator is
 *first being set up, these stops are shared by routes that way every bus that
 *is on a route shares the stops that way the list of passengers is able to be
 *accessed by every bus on the uses that stop.
 *
 *Route is a list of stops and every bus has at least one route, this is how
 *buses interface with stops and know which stop to go to next.
 *Each route contains a list of stops, a list of distances between stops, and a
 *passengerGenerator a class that creates new passengers to wait at its stops.
 *For our implementation we have the simulator create prototypes routes at the
 *beginning and they have a list of pointers to the stops on their route.
 *Routes are how bus’s get the information about where they are heading and
 *how far they need to travel. Route now hold a route_data struct which holds
 *all of there info, this is used for easily grabbing everything at once.
 *
 *The most complex class is our Bus class as it interfaces with all the other
 *classes described so far. In this iteration bus has quite a few variables,
 *it has two routes, an outgoing and incoming. It also has a passenger list,
 *a name, a speed, and a distance remaining. Most of the buses logic takes
 *place in the update function. In it the bus interfaces with the route
 *to find its next stop and moves its position. Similar to route, bus holds
 *bus_data struct which holds all of that buses info and to be accessed by other
 *classes.
 *
 *For more info on all of the classes check out the pages on this webpage for further
 *detail.
 *
 * If you want to expand the code beyond just editing the 4 main classes laid out
 * you will want to either edit my_local_sim or create your own local_sim that
 * inherits from the simulator.h. You will need to overwrite start() and update().
 * The other main area of code that can be edited is creating an edited version
 *  passengerGenerator.
 *
 * \n\n
 * USER GUIDE
 * ===
 * 	Welcome to the User Guide for how to use this transit simulator. This Guide
 *  will walk you through how to get the needed code, how to build the
 * executable, how to properly run the executable and how to make txt files to
 * have your own custom routes for this transit sim.
 * \n\n
 * 1. DOWNLOADING
 * ===
 * First for downloading the project, there are 2 ways to go about getting the
 * code either downloading a zip or cloning the repository, this guide will go
 * over both of them. For either method you want to get the code you first need
 * to go to this github link.

 * https://github.umn.edu/umn-csci-3081-f19/repo-gorrx005
 *
 * Once on this page you will need to click the green button labeled
 * “Clone or download” located above the list of folders and files present.
 *
 * \image html github2.png
 *
 * This will bring down a drop down menu where you can choose to either download
 * a zip of this repository, or it will allow you to copy the address needed to
 * clone the repository.

 * \image html cloneOrDownload.PNG

 * If you are choosing downloading the zip will just need to extract the files
 * into a folder you can navigate to later.
 *
 * If you are choosing to clone the directory instead you must first need to now
 * begin using a terminal, note the words between the <carrots> are for you to
 * put in what you want.
 *
 * 	\n
 *   $cd <location of your choosing>
 *	\n
 *   $mkdir <name of folder to hold repo>
 *	\n
 *
 *   $cd  <name of folder just created>
 *	\n
 *
 *   $git clone https://github.umn.edu/umn-csci-3081-f19/repo-gorrx005.git
 *
 *	\n
 *



 * 2. CREATING AN EXECUTABLE
 * ===
 * For creating the executable you will need to navigate to the directory that
 * holds your copy of the repository, you should be in repo-gorrx005 directory
 * to start this section. If you want to avoid any of the potential issue below
 * you may consider running this code a cselabs machine at the University of
 * Minnesota in the Twin Cities.
 *
 * Note you may need to download gcc and g++ in your terminal in order for our
 * makefile to work on your machine. To install them on ubuntu simply type or
 * copy the following. There may be other packages on my testing environments
 * that may be different than yours, for the makefile to work properly you will
 * need to have the same packages installed on your system that our own mine,
 * when running make you may need to look at the output if it fails and install
 * any missing packages. This section may be the most difficult because you may
 * be missing many packages used by our makefile.
 * \n\n
 *   $sudo apt install gcc
 *   $sudo apt install g++
 * \n\n
 * From the repo-gorrx005 directory type the following in your terminal
 * \n\n
 *   $cd project
 *   $make
 * \n\n
 * If the make failed at this time you will need to install those missing
 * packages that it tries to call. However if no errors came up then you have
 * successfully compiled and linked the program.
 *
 * \n\n



 * 3. HOW TO RUN THE PROGRAM
 * ===
 * Now that you have successfully installed it you may be wondering where the
 * executable actually is. For the structure of this directory everything you
 * build will be placed in the “build” directory, then for executables they will
 * be in the “bin” directory. Feel free to navigate there now to see everything
 * that has been built. This folder won’t be present until you have called make.
 *
 * However you will not be running the executables from here, you need to navigate back to the project directory. Once you are in the project directory you will need to type the following into your terminal.
 * \n\n
 *   $./build/bin/configuration_sim
 * \n\n
 *You have now successfully run the bus simulator.
 *
 * \n\n
 * 4. HOW TO EDIT CONFIG.TXT
 * ===
 * You may have noticed a message when you ran configuration_sim that stated at
 * the beginning of the program it would be using the default config.txt. In
 * this Bus simulator all the routes and stops data is stored in text files that
 * are read in at the beginning of the program. If you would like you could
 * either edit config.txt located in the config directory in project, or make
 * your own txt file in the config folder.
 *
 * Before you begin editing you should create a backup of config.txt. Then open
 * the file to examine the contents and how data is laid out. Below is a copy of
 * the first few lines to explain how information is laid out. The line numbers
 * are only present for reference.
 *
 * \n\n
 * 1 ROUTE_GENERAL, Campus Connector
 *
 * 2
 *
 * 3 Stop Name, Long, Lat, Pass Gen Prob
 *
 * 4
 *
 * 5 ROUTE, East Bound
 *
 * 6
 *
 * 7 STOP, Blegen Hall, 44.972392, -93.243774, .15
 *
 * 8 STOP, Coffman, 44.973580, -93.235071, .3
 *
 * 9 STOP, Oak Street at University Avenue, 44.975392, -93.226632, .025
 *
 * 10 STOP, Transitway at 23rd Avenue SE, 44.975837, -93.222174, .05
 *
 * \n\n
 *
 * Lines 1-4 shows you a template for your data will be written in this file.
 * Routes are written with the type ROUTE in all capital letters followed by a
 * comma and the name of the route. Afterwards a line is skipped and a list of
 * stops the the route contains follow it. This data in this file is separated
 * by blank lines like lines 2 and 4 in the template. Stops structure is similar
 * to route, each stop begins with STOP, followed by the name of the stop, its
 * longitude, latitude, and the probability that a passenger will show up each
 * time step. The Route knows it ends when there is a blank line after the last
 * stop.
 *
 * Using config.txt as a template you could either edit this config.txt or make
 * your own file with routes in the future.  If you make your own file you need
 * to include in the config folder. When running with another txt file with
 * route information you need to specify that in the terminal before you run the
 * program along with the path to the file. Remember this is run for the project
 * directory and if you have only edited or made a config file then you don’t
 * need to call make again.
 *
 *    $./build/bin/configuration_sim config/my_config.txt
 *\n\n
 *5. WHAT ELSE CAN I CHANGE?
 * ===
 *
 * If you want to change how long the simulation lasts or how often a bus is made
 * for each route you will need to actually go into the code to do that. To change
 * how long the simulation runs you need to navigate to the drivers folder in the
 * project directory and change the variable rounds_ near the top on main on line
 * 21.
 *
 * To edit how often buses are created you will need to navigate to the src folder
 * and into the file "my_local_sim.cc" at line 49 is a variable
 * bus_start_timings.push_back(10), you can change this 10 to another int. This int
 * is how many rounds pass before a new bus is created, so lower numbers mean less
 * time between buses being created.
 *
 * If you do change either of these values you will need to recompile the code using
 * make, remember to call make when in the project directory.
 */
#endif  // SRC_MAINPAGE_H_
