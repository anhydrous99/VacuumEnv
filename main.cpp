#include <iostream>
#include <random>
#include <cassert>

#include "Environment.h"

int main(int argc, char *argv[]) {
    Environment env1(10, 20);

    std::function<vacuum(const std::string &, Environment &)> strategy_1 = [](const std::string &vacuum_name,
                                                                                    Environment &env) -> vacuum {

    };
    std::function<vacuum(const std::string &, Environment &)> strategy_2 = [=](const std::string &vacuum_name,
                                                                                    Environment &env) -> vacuum {
        vacuum current_vacuum = env.access_vacuum(vacuum_name);
        std::random_device rd;
        std::uniform_int_distribution<int> dis(1, 4);
        cell current_cell = env(current_vacuum.get_position());

        while (true) {
            int random_number = dis(rd);
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

                env.move_vacuum(vacuum_name, direction);
            } else if (random_number == 2) {
                if (current_cell.cellType == cell::SOUTH_BOUNDARY_TYPE ||
                current_cell.cellType == cell::SOUTHEAST_CORNER_TYPE ||
                current_cell.cellType == cell::SOUTHWEST_CORDER_TYPE)
                    continue;

                if (env(current_vacuum.get_x(), current_vacuum.get_y() - 1).contains_obstacle)
                    continue;

                env.move_vacuum(vacuum_name, direction);
            } else if (random_number == 3) {
                if (current_cell.cellType == cell::WEST_BOUNDARY_TYPE ||
                current_cell.cellType == cell::SOUTHWEST_CORDER_TYPE ||
                current_cell.cellType == cell::NORTHWEST_CORNER_TYPE)
                    continue;

                if (env(current_vacuum.get_x() - 1, current_vacuum.get_y()).contains_obstacle)
                    continue;

                env.move_vacuum(vacuum_name, direction);
            } else {
                if (current_cell.cellType == cell::EAST_BOUNDARY_TYPE ||
                current_cell.cellType == cell::SOUTHWEST_CORDER_TYPE ||
                current_cell.cellType == cell::NORTHWEST_CORNER_TYPE)
                    continue;

                if (env(current_vacuum.get_x() + 1, current_vacuum.get_y()).contains_obstacle)
                    continue;

                env.move_vacuum(vacuum_name, direction);
            }
        }
    };
    return EXIT_SUCCESS;
}