//
// Created by Armando Herrera on 9/1/19.
//

#include "cell.h"

std::ostream &operator<<(std::ostream &os, const cell &input_cell) {
    os << "{";
    switch (input_cell.cellType) {
        case cell::NON_BOUNDARY_TYPE:
            break;
        case cell::WEST_BOUNDARY_TYPE:
            os << "west-boundary,";
            break;
        case cell::NORTH_BOUNDARY_TYPE:
            os << "north-boundary,";
            break;
        case cell::EAST_BOUNDARY_TYPE:
            os << "east-boundary,";
            break;
        case cell::SOUTH_BOUNDARY_TYPE:
            os << "south-boundary,";
            break;
        case cell::NORTHWEST_CORNER_TYPE:
            os << "northwest-corner,";
            break;
        case cell::NORTHEAST_CORNER_TYPE:
            os << "northeast-corner,";
            break;
        case cell::SOUTHEAST_CORNER_TYPE:
            os << "southeast-corner,";
            break;
        case cell::SOUTHWEST_CORDER_TYPE:
            os << "southwest-corner,";
            break;
        case cell::OBSTACLE_TYPE:
            os << "obstacle,";
    }
    if (input_cell.cellValue == cell::CLEAN_VALUE)
        os << "clean";
    else
        os << "dirty";
    os << "}";
    return os;
}