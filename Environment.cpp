//
// Created by aherrera on 8/31/19.
//

#include "Environment.h"

Environment::Environment(int n) : _n(n), _data(n * n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 && j == 0)
                _data[0].cellType = cell::NORTHWEST_CORNER_TYPE;
            else if (i == 0 && j == n - 1)
                _data[i * n + j].cellType = cell::NORTHEAST_CORNER_TYPE;
            else if (i == n - 1 && j == 0)
                _data[i * n + j].cellType = cell::SOUTHWEST_CORDER_TYPE;
            else if (i == n - 1 && j == n - 1)
                _data[i * n + j].cellType = cell::NORTHEAST_CORNER_TYPE;
            else if (i == 0)
                _data[i * n + j].cellType = cell::NORTH_BOUNDARY_TYPE;
            else if (i == n - 1)
                _data[i * n + j].cellType = cell::SOUTH_BOUNDARY_TYPE;
            else if (j == 0)
                _data[i * n + j].cellType = cell::WEST_BOUNDARY_TYPE;
            else if (j == n - 1)
                _data[i * n + j].cellType = cell::EAST_BOUNDARY_TYPE;
        }
    }
}

cell &Environment::operator()(int i, int j) {
    return _data[i * _n + j];
}

std::ostream &operator<<(std::ostream &os, const Environment &environment) {
    int n = environment._n;
    for (int i = 0; i < n; i++) {
        int current_row = i * n;
        for (int j = 0; j < n; j++) {
            os << environment._data[current_row + j] << " ";
        }
        os << std::endl;
    }
    return os;
}