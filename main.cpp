#include <iostream>
#include <random>
#include <cassert>

#include "Environment.h"

int simulate(Environment env);

int main(int argc, char *argv[]) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(1, 4);
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
        } else if (current_position.second == n - 1){
            if ((current_position.first + 1) % 2 == 0)
                ret += "W";
            else
                ret += "S";
        }
        return ret;
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
                    current_cell.cellType == cell::SOUTHWEST_CORNER_TYPE)
                    continue;

                if (env(current_vacuum.get_x(), current_vacuum.get_y() - 1).contains_obstacle)
                    continue;
            } else if (random_number == 3) {
                if (current_cell.cellType == cell::WEST_BOUNDARY_TYPE ||
                    current_cell.cellType == cell::SOUTHWEST_CORNER_TYPE ||
                    current_cell.cellType == cell::NORTHWEST_CORNER_TYPE)
                    continue;

                if (env(current_vacuum.get_x() - 1, current_vacuum.get_y()).contains_obstacle)
                    continue;
            } else {
                if (current_cell.cellType == cell::EAST_BOUNDARY_TYPE ||
                    current_cell.cellType == cell::SOUTHWEST_CORNER_TYPE ||
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