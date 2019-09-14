//
// Created by Armando Herrera on 9/1/19.
//

#ifndef CSCI6350_PROJECT1_CELL_H
#define CSCI6350_PROJECT1_CELL_H

#include <ostream>
#include <vector>

struct cell {
    enum cell_type {
        NON_BOUNDARY_TYPE = 0,
        WEST_BOUNDARY_TYPE = 1,
        NORTH_BOUNDARY_TYPE = 2,
        EAST_BOUNDARY_TYPE = 3,
        SOUTH_BOUNDARY_TYPE = 4,
        NORTHWEST_CORNER_TYPE = 5,
        NORTHEAST_CORNER_TYPE = 6,
        SOUTHEAST_CORNER_TYPE = 7,
        SOUTHWEST_CORNER_TYPE = 8
    } cellType = NON_BOUNDARY_TYPE;
    enum cell_obstacle {
        UPPER_OBSTACLE,
        LOWER_OBSTACLE,
        LEFT_OBSTACLE,
        RIGHT_OBSTACLE
    };
    enum cell_value {
        CLEAN_VALUE = 0,
        DIRTY_VALUE = 1
    } cellValue = CLEAN_VALUE;

    std::vector<cell_obstacle> neighborObstacles;
    bool contains_obstacle = false;

    cell() = default;
    cell(cell_type ctype, cell_value cvalue) { cellType = ctype; cellValue = cvalue; }
};

std::ostream &operator<<(std::ostream &os, const cell &input_cell);

#endif //CSCI6350_PROJECT1_CELL_H
