#include <iostream>
#include <random>
#include <chrono>

#include "Environment.h"
#include "parser.h"

int simulate(Environment env);

int main(int argc, char *argv[]) {
    using namespace std::chrono;
    typedef high_resolution_clock hrc;

    // Get and print configuration from json file
    parser p("conf.json");
    std::cout << "Using the following settings - \n";
    std::cout << p.side_size << " - side size\n";
    std::cout << p.step_limit << " - step limit\n\n";
    int i = 1;
    for (const auto& r : p.runs) {
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


    /*
    std::function<std::string(const std::string &, Environment &)> strategy_1 = [](const std::string &vacuum_name,
                                                                                   Environment &env) -> std::string {
        vacuum current_vacuum = env.access_vacuum(vacuum_name);
        position current_position = current_vacuum.get_position();
        cell current_cell = env(current_position);

        int n = env.side_size();
        std::string ret;

        if (current_cell.cellValue == cell::DIRTY_VALUE)
            ret = "D";
        else
            ret = "C";

        if (current_position.second != n - 1 && current_position.second != 0) {
            if ((current_position.first + 1) % 2 == 0)
                ret += "W";
            else
                ret += "E";
        } else if (current_position.second == 0) {
            if ((current_position.first + 1) % 2 == 0)
                ret += "S";
            else
                ret += "E";
        } else if (current_position.second == n - 1) {
            if ((current_position.first + 1) % 2 == 0)
                ret += "W";
            else
                ret += "S";
        }

        return ret;
    };
    std::function<std::string(const std::string &, Environment &)> strategy_2 = [&](const std::string &vacuum_name,
                                                                                    Environment &env) -> std::string {
        vacuum current_vacuum = env.access_vacuum(vacuum_name);
        cell current_cell = env(current_vacuum.get_position());

        while (true) {
            int random_number = dis(gen);
            std::string direction;

            if (current_cell.cellValue == cell::DIRTY_VALUE)
                direction = "D";
            else
                direction = "C";

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

    Environment env_1(10, 0.50);
    Environment env_2(10, 0.50);
    env_1.add_vacuum(0, 0, "Vacuum_1");
    env_1.add_agent_function(strategy_1);

    env_2.add_vacuum(0, 0, "Vacuum_1");
    env_2.add_agent_function(strategy_2);

    std::cout << "Strategy 1: \n";
    auto t1 = hrc::now();
    int strat_1 = simulate(env_1);
    auto t2 = hrc::now();
    std::cout << "Strategy 2: \n";
    auto t3 = hrc::now();
    int strat_2 = simulate(env_2);
    auto t4 = hrc::now();

    std::cout << "Strategy 1 : " << strat_1 << " steps - completed in " << duration_cast<milliseconds>(t2 - t1).count()
              << " milliseconds\n";
    std::cout << "Strategy 2 : " << strat_2 << " steps - completed in " << duration_cast<milliseconds>(t4 - t3).count()
              << " milliseconds\n"; */

    return EXIT_SUCCESS;
}

int simulate(Environment env) {
    int i = 0;
    while (true) {
        std::cout << "Step " << i << ": \n" << env << std::endl;
        if (env.step_vacuums())
            break;
        i++;
    }
    return i;
}