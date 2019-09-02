//
// Created by Armando Herrera on 9/1/19.
//

#include "cell.h"

std::ostream &operator<<(std::ostream &os, const cell &input_cell) {
    os << "{";
    switch (input_cell.cellType) {
        case cell::NON_BOUNDARY:
            os << "non-boundary,";
            break;
        case cell::WEST_BOUNDARY:
            os << "west-boundary,";
            break;
        case cell::NORTH_BOUNDARY:
            os << "north-boundary,";
            break;
        case cell::EAST_BOUNDARY:
            os << "east-boundary,";
            break;
        case cell::SOUTH_BOUNDARY:
            os << "south-boundary,";
            break;
        case cell::NORTHWEST_CORNER:
            os << "northwest-corner,";
            break;
        case cell::NORTHEAST_CORNER:
            os << "northeast-corner,";
            break;
        case cell::SOUTHEAST_CORNER:
            os << "southeast-corner,";
            break;
        case cell::SOUTHWEST_CORDER:
            os << "southwest-corner,";
    }
    if (input_cell.cellValue == cell::CLEAN)
        os << "clean";
    else
        os << "dirty";
    os << "}";
    return os;
}