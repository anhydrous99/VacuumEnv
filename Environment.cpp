//
// Created by aherrera on 8/31/19.
//

#include "Environment.h"

Environment::Environment(int n) : _n(n) {
    _data = static_cast<cell *>(std::calloc(0, sizeof(cell) * n));
}

cell Environment::operator()(int i, int j) {
    return _data[i * _n + j];
}

std::ostream &operator<<(std::ostream &os, const cell &cell) {
    os << cell.s << "," << cell.l;
    return os;
}

std::ostream &operator<<(std::ostream &os, const Environment &environment) {
    auto* data = environment._data;
    int n = environment._n;
    for (int i = 0; i < n; i++) {
        os << "|";
        int current_row = i * n;
        for (int j = 0; j < n; j++) {
            os << data[current_row + j] << "|";
        }
        os << std::endl;
    }
    return os;
}