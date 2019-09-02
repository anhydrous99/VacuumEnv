//
// Created by Armando Herrera on 9/1/19.
//

#ifndef CSCI6350_PROJECT1_CELL_H
#define CSCI6350_PROJECT1_CELL_H

#include <ostream>

struct cell {
    enum cell_type {
        NON_BOUNDARY = 0,
        WEST_BOUNDARY = 1,
        NORTH_BOUNDARY = 2,
        EAST_BOUNDARY = 3,
        SOUTH_BOUNDARY = 4,
        NORTHWEST_CORNER = 5,
        NORTHEAST_CORNER = 6,
        SOUTHEAST_CORNER = 7,
        SOUTHWEST_CORDER = 8
    } cellType = NON_BOUNDARY;

    enum cell_value {
        CLEAN = 0,
        DIRTY = 1
    } cellValue = CLEAN;

    cell() = default;
    cell(cell_type ctype, cell_value cvalue) { cellType = ctype; cellValue = cvalue; }
};

std::ostream &operator<<(std::ostream &os, const cell &input_cell);

#endif //CSCI6350_PROJECT1_CELL_H
