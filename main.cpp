#include <iostream>
#include <random>
#include <chrono>
#include <stdexcept>

#include "Environment.h"
#include "parser.h"

int main(int argc, char *argv[]) {
    int super_max = std::numeric_limits<int>::max();
    using namespace std::chrono;
    typedef high_resolution_clock hrc;

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

    // Create the first strategy as a lambda function and store in a function type
    std::function<std::string(const std::string &, Environment &)> strategy_1 = [](const std::string &vacuum_name,
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

    std::vector<int> durations(p.runs.size());
    std::vector<int> times(p.runs.size());
    i = 0;
    for (const auto &r : p.runs) {
        Environment environment(p.side_size, r.dirty_percentage, r.obstruction_percentage);

        try {
            environment.add_vacuum(0, 0, "Vacuum_1");
        } catch (const std::runtime_error &error) {
            durations[i] = super_max;
            times[i] = super_max;
            i++;
            continue;
        }

        environment.add_agent_function((r.strategy == 1) ? strategy_1 : strategy_2);

        std::cout << "\n RUN " << i << ": \n";
        int j;
        auto t1 = hrc::now();
        for (j = 0; j < p.step_limit; j++) {
            std::cout << environment << std::endl << std::endl;
            if (environment.step_vacuums())
                break;
        }
        auto t2 = hrc::now();
        durations[i] = (j == p.step_limit) ? super_max : j;
        times[i] = duration_cast<milliseconds>(t2 - t1).count();
        i++;
    }

    for (unsigned long j = 0; j < durations.size(); j++) {
        std::cout << "Run - " << j + 1 << " stats\n";
        if (durations[j] == super_max) {
            if (times[j] == super_max)
                std::cout << "Vacuum could not find path\n";
            else
                std::cout << "Vacuum found it self in a infinite loop or there was an inaccessable location\n";
        } else {
            std::cout << "Steps - " << durations[j] << std::endl;
            std::cout << "Time - " << times[j] << " millisenconds\n";
        }
        std::cout << std::endl;
    }

    return EXIT_SUCCESS;
}