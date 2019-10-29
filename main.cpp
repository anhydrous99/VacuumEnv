//
// CSCI-6350-01 Project 1
// Due: 9/20/2019
// -- Armando Herrera --
// ID: 20217690
//

#include <iostream>
#include <random>
#include <chrono>
#include <thread>
#include <stdexcept>

#include "Environment.h"
#include "parser.h"

int main(int argc, char *argv[]) {
  int super_max = std::numeric_limits<int>::max(); // Grab maximum possible int value
  using namespace std::chrono; // include chrono namespace
  typedef high_resolution_clock hrc; // shorten a name

  // Get and print configuration from json file
  parser p("conf.json");
  std::cout << "Using the following settings - \n";
  std::cout << p.side_size << " - side size\n";
  std::cout << p.step_limit << " - step limit\n\n";
  int i = 1;
  for (const auto &r : p.runs) {
    std::cout << i << " - run\n";
    std::cout << r.strategy << " - strategy\n";
    std::cout << r.dirty_percentage << " - percent dirty\n";
    std::cout << r.obstruction_percentage << " - obstruction_percentage\n\n";
    i++;
  }
  std::cout << "Press any key to continue ...\n";
  std::cin.get();

  // Init a random number generator for strategy 2
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> dis(1, 4);

  // Create the random number generator that will be used when randomly placng the vacuums
  std::uniform_int_distribution<int> dis_vacuums(0, p.side_size - 1);

  // Boolean for first strategy containing whether the agent has reached the corner
  bool has_reached_corner = false;

  // Create the first strategy as a lambda function and store in a function type
  std::function<std::string(const std::string &, Environment &)> strategy_1 = [&](const std::string &vacuum_name,
                                                                                  Environment &env) -> std::string {
    vacuum current_vacuum = env.access_vacuum(vacuum_name);    // Get current vacuum
    position current_position = current_vacuum.get_position(); // Get current position of vacuum
    cell current_cell = env(current_position);                 // Gets the cell at position of vacuum

    // Gets side length & declare returned string type
    int n = env.side_size();
    std::string ret;

    // If cell is dirty suck by setting first character to D
    if (current_cell.cellValue == cell::DIRTY_VALUE)
      ret = "D";
    else
      ret = "C";

    ret += " ";


    if (!has_reached_corner) {
      // Choose next direction based on even and odd numbered rows
      if (current_position.second != n - 1 && current_position.second != 0) {
        if ((current_position.first + 1) % 2 == 0)
          ret[1] = 'W';
        else
          ret[1] = 'E';
      } else if (current_position.second == 0) {
        if ((current_position.first + 1) % 2 == 0)
          ret[1] = 'S';
        else
          ret[1] = 'E';
      } else if (current_position.second == n - 1) {
        if ((current_position.first + 1) % 2 == 0)
          ret[1] = 'W';
        else
          ret[1] = 'S';
      }

      if (n % 2 == 0) {
        if (current_cell.cellType == cell::SOUTHWEST_CORNER_TYPE)
          has_reached_corner = true;
      }
      else {
        if (current_cell.cellType == cell::SOUTHEAST_CORNER_TYPE)
          has_reached_corner = true;
      }
    } else {
      //  Choose next direction based on odd and even numbered rows
      if (current_position.second != n - 1 && current_position.second != 0) {
        if ((current_position.first + 1) % 2 == 0)
          ret[1] = 'E';
        else
          ret[1] = 'W';
      } else if (current_position.second == 0) {
        if ((current_position.first + 1) % 2 == 0)
          ret[1] = 'E';
        else
          ret[1] = 'N';
      } else if (current_position.second == n - 1) {
        if ((current_position.first + 1) % 2 == 0)
          ret[1] = 'N';
        else
          ret[1] = 'W';
      }

      if (current_cell.cellType == cell::NORTHWEST_CORNER_TYPE)
        has_reached_corner = false;
    }

    // Check for obstacles, take another direction if there is an obstacle
    while (true) {
      if (ret[1] == 'W' && (
          current_cell.cellType == cell::WEST_BOUNDARY_TYPE ||
          current_cell.cellType == cell::NORTHWEST_CORNER_TYPE ||
          current_cell.cellType == cell::SOUTHWEST_CORNER_TYPE ||
          env(current_vacuum.get_x(), current_vacuum.get_y() - 1).contains_obstacle)) {
        ret[1] = 'S';
        continue;
      }
      if (ret[1] == 'S' && (
          current_cell.cellType == cell::SOUTH_BOUNDARY_TYPE ||
          current_cell.cellType == cell::SOUTHEAST_CORNER_TYPE ||
          current_cell.cellType == cell::SOUTHWEST_CORNER_TYPE ||
          env(current_vacuum.get_x() + 1, current_vacuum.get_y()).contains_obstacle)) {
        ret[1] = 'E';
        continue;
      }
      if (ret[1] == 'E' && (
          current_cell.cellType == cell::EAST_BOUNDARY_TYPE ||
          current_cell.cellType == cell::SOUTHEAST_CORNER_TYPE ||
          current_cell.cellType == cell::NORTHEAST_CORNER_TYPE ||
          env(current_vacuum.get_x(), current_vacuum.get_y() + 1).contains_obstacle)) {
        ret[1] = 'N';
        continue;
      }
      if (ret[1] == 'N' && (
          current_cell.cellType == cell::NORTH_BOUNDARY_TYPE ||
          current_cell.cellType == cell::NORTHEAST_CORNER_TYPE ||
          current_cell.cellType == cell::NORTHWEST_CORNER_TYPE ||
          env(current_vacuum.get_x() - 1, current_vacuum.get_y()).contains_obstacle)) {
        ret[1] = 'W';
        continue;
      }

      break;
    }

    return ret;
  };

  // Create the second strategy as a lambda function and store in a function type
  //   I am passing the random number generator as a reference with the & in the lambda function
  std::function<std::string(const std::string &, Environment &)> strategy_2 = [&](const std::string &vacuum_name,
                                                                                  Environment &env) -> std::string {
    vacuum current_vacuum = env.access_vacuum(vacuum_name); // Gets current vacuum
    cell current_cell = env(current_vacuum.get_position()); // Gets current cell of vacuum

    while (true) {
      int random_number = dis(gen); // Generates a random number between 1 and 1
      std::string direction;            // Declare returned string

      // Suck if cell is dirty - sets first character
      if (current_cell.cellValue == cell::DIRTY_VALUE)
        direction = "D";
      else
        direction = "C";

      // Sets a direction based on the random number
      switch (random_number) {
        case 1:
          direction += "N";
          break;
        case 2:
          direction += "S";
          break;
        case 3:
          direction += "W";
          break;
        default:
          direction += "E";
      }

      // Checks if direction is valid
      if (random_number == 1) {
        if (current_cell.cellType == cell::NORTH_BOUNDARY_TYPE ||
            current_cell.cellType == cell::NORTHEAST_CORNER_TYPE ||
            current_cell.cellType == cell::NORTHWEST_CORNER_TYPE)
          continue;

        if (env(current_vacuum.get_x() - 1, current_vacuum.get_y()).contains_obstacle)
          continue;
      } else if (random_number == 2) {
        if (current_cell.cellType == cell::SOUTH_BOUNDARY_TYPE ||
            current_cell.cellType == cell::SOUTHEAST_CORNER_TYPE ||
            current_cell.cellType == cell::SOUTHWEST_CORNER_TYPE)
          continue;

        if (env(current_vacuum.get_x() + 1, current_vacuum.get_y()).contains_obstacle)
          continue;
      } else if (random_number == 3) {
        if (current_cell.cellType == cell::WEST_BOUNDARY_TYPE ||
            current_cell.cellType == cell::SOUTHWEST_CORNER_TYPE ||
            current_cell.cellType == cell::NORTHWEST_CORNER_TYPE)
          continue;

        if (env(current_vacuum.get_x(), current_vacuum.get_y() - 1).contains_obstacle)
          continue;
      } else {
        if (current_cell.cellType == cell::EAST_BOUNDARY_TYPE ||
            current_cell.cellType == cell::SOUTHEAST_CORNER_TYPE ||
            current_cell.cellType == cell::NORTHEAST_CORNER_TYPE)
          continue;

        if (env(current_vacuum.get_x(), current_vacuum.get_y() + 1).contains_obstacle)
          continue;
      }

      return direction;
    }
  };

  std::vector<int> step_count(p.runs.size()); // Stores required steps
  std::vector<int> times(p.runs.size());      // Stores elapsed times
  i = 0;                                      // Keeps track of index
  for (const auto &r : p.runs) { // Range-based loop
    Environment environment(p.side_size, r.dirty_percentage, r.obstruction_percentage); // Start up environment

    // This throws a runtime_error exception if vacuum is sorrounded by obstacles and walls
    try {
      environment.add_vacuum(dis_vacuums(gen), dis_vacuums(gen), "Vacuum_1");
    } catch (const std::runtime_error &e) { // Catch the runtime_error exception
#ifdef _MSC_VER // Removed warning from not using e on VC++
      (void)e;
#endif
      step_count[i] = super_max; // Indicate that the vacuum is sorrounded
      times[i] = super_max;
      i++;                       // Iterates i
      continue;                  // Move to next run
    }

    // Adds the prescribed agent function
    environment.add_agent_function((r.strategy == 1) ? strategy_1 : strategy_2);

    std::cout << "\n RUN " << i << ": \n";
    int j; // keep track of env iteration
    auto t1 = hrc::now(); // get start time
    for (j = 0; j < p.step_limit; j++) {
      if (p.print_steps) {
        std::cout << environment << std::endl << std::endl; // Prints environment
        if (p.step_delay != 0)
          std::this_thread::sleep_for(milliseconds(p.step_delay)); // Delays printing on console
      }
      if (environment.step_vacuums()) // Steps all vacuums
        break; // break if environment is clean
    }
    auto t2 = hrc::now(); // get end time
    step_count[i] = (j == p.step_limit) ? super_max : j; // if max is reached indicate by setting count to int max
    times[i] = static_cast<int>(duration_cast<milliseconds>(t2 - t1).count()); // Calculate time difference & store
    i++; // Iterate index
  }

  // Print results
  for (unsigned long j = 0; j < step_count.size(); j++) {
    std::cout << "Run - " << j + 1 << " stats\n";
    if (step_count[j] == super_max) {
      if (times[j] == super_max)
        std::cout << "Vacuum could not find path\n";
      else
        std::cout << "Vacuum found it self in a infinite loop or there was an inaccessable location\n";
    } else {
      std::cout << "Steps - " << step_count[j] << std::endl;
      std::cout << "Time - " << times[j] << " millisenconds\n";
    }
    std::cout << std::endl;
  }

  std::cout << "Press any key to continue ...\n";
  std::cin.get();
  return EXIT_SUCCESS;
}
