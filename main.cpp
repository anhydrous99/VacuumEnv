#include <iostream>
#include <random>
#include <cassert>

#include "Environment.h"

int simulate(Environment env);

int main(int argc, char *argv[]) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, 4);
    char current_direction = 'E';
    std::function<char(const std::string &, Environment &)> strategy_1 = [&](const std::string &vacuum_name,
                                                                                    Environment &env) -> char {
        vacuum current_vacuum = env.access_vacuum(vacuum_name);
        std::cout << current_vacuum.get_position().first << " " << current_vacuum.get_position().second << std::endl;
        cell current_cell = env(current_vacuum.get_position());

        if (current_direction == 'E' || current_direction == 'W') {
            if (current_cell.cellType == cell::EAST_BOUNDARY_TYPE ||
                current_cell.cellType == cell::SOUTHEAST_CORNER_TYPE ||
                current_cell.cellType == cell::NORTHEAST_CORNER_TYPE ||
                current_cell.cellType == cell::WEST_BOUNDARY_TYPE ||
                current_cell.cellType == cell::SOUTHWEST_CORDER_TYPE ||
                current_cell.cellType == cell::NORTHWEST_CORNER_TYPE) {
                current_direction = 'S';
            }
        } else if (current_direction == 'S') {
            if (current_cell.cellType == cell::EAST_BOUNDARY_TYPE ||
            current_cell.cellType == cell::SOUTHEAST_CORNER_TYPE ||
            current_cell.cellType == cell::NORTHEAST_CORNER_TYPE) {
                current_direction = 'W';
            } else if (current_cell.cellType == cell::WEST_BOUNDARY_TYPE ||
            current_cell.cellType == cell::NORTHWEST_CORNER_TYPE ||
            current_cell.cellType == cell::NORTHEAST_CORNER_TYPE) {
                current_direction = 'E';
            }
        }
        return current_direction;
    };
    std::function<char(const std::string &, Environment &)> strategy_2 = [&](const std::string &vacuum_name,
                                                                                    Environment &env) -> char {
        vacuum current_vacuum = env.access_vacuum(vacuum_name);
        cell current_cell = env(current_vacuum.get_position());

        while (true) {
            int random_number = dis(gen);
            char direction;
            switch (random_number) {
                case 1:
                    direction = 'N';
                    break;
                case 2:
                    direction = 'S';
                    break;
                case 3:
                    direction = 'W';
                    break;
                default:
                    direction = 'E';
            }

            if (random_number == 1) {
                if (current_cell.cellType == cell::NORTH_BOUNDARY_TYPE ||
                current_cell.cellType == cell::NORTHEAST_CORNER_TYPE ||
                current_cell.cellType == cell::NORTHWEST_CORNER_TYPE)
                    continue;

                if (env(current_vacuum.get_x(), current_vacuum.get_y() + 1).contains_obstacle)
                    continue;
            } else if (random_number == 2) {
                if (current_cell.cellType == cell::SOUTH_BOUNDARY_TYPE ||
                current_cell.cellType == cell::SOUTHEAST_CORNER_TYPE ||
                current_cell.cellType == cell::SOUTHWEST_CORDER_TYPE)
                    continue;

                if (env(current_vacuum.get_x(), current_vacuum.get_y() - 1).contains_obstacle)
                    continue;
            } else if (random_number == 3) {
                if (current_cell.cellType == cell::WEST_BOUNDARY_TYPE ||
                current_cell.cellType == cell::SOUTHWEST_CORDER_TYPE ||
                current_cell.cellType == cell::NORTHWEST_CORNER_TYPE)
                    continue;

                if (env(current_vacuum.get_x() - 1, current_vacuum.get_y()).contains_obstacle)
                    continue;
            } else {
                if (current_cell.cellType == cell::EAST_BOUNDARY_TYPE ||
                current_cell.cellType == cell::SOUTHWEST_CORDER_TYPE ||
                current_cell.cellType == cell::NORTHWEST_CORNER_TYPE)
                    continue;

                if (env(current_vacuum.get_x() + 1, current_vacuum.get_y()).contains_obstacle)
                    continue;
            }

            return direction;
        }
    };

    Environment env_1(10, 0.25);
    env_1.add_vacuum(0, 0, "Vacuum_1");
    env_1.add_agent_function(strategy_1);

    int n_steps = simulate(env_1);
    std::cout << "Strategy 1 : " << n_steps << " steps";
    std::cout << "Strategy 2 : " << n_steps << " steps";

    return EXIT_SUCCESS;
}

int simulate(Environment env) {
    int i = 0;
    while (true) {
        if (env.step_vacuums())
            break;
        i++;
    }
    return i;
}