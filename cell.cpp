//
// Created by Armando Herrera on 9/1/19.
//

#include "cell.h"

std::ostream &operator<<(std::ostream &os, const cell &input_cell) {
    os << "{";
    for (const cell::cell_obstacle &obs : input_cell.neighborObstacles) {
        switch (obs) {
            case cell::UPPER_OBSTACLE:
                os << "\033[31m0\033[0m,";
                break;
            case cell::LOWER_OBSTACLE:
                os << "\033[32m1\033[0m,";
                break;
            case cell::LEFT_OBSTACLE:
                os << "\033[33m2\033[0m";
                break;
            case cell::RIGHT_OBSTACLE:
                os << "\033[34m3\033[0m,";
        }
    }
    if (!input_cell.contains_obstacle) {

        if (input_cell.has_been_transversed)
            os << "\033[33mx\033[0m";
        else if (input_cell.cellValue == cell::CLEAN_VALUE)
            os << "\033[32m0\033[0m";
        else
            os << "\033[31m1\033[0m";
    } else {
        os << "\033[35mo\033[0m";
    }
    os << "}";
    return os;
}