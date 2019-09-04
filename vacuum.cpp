//
// Created by Armando Herrera on 9/3/19.
//

#include "vacuum.h"

vacuum::vacuum(int x_position, int y_position) : pos(x_position, y_position) {
}

position vacuum::get_position() {
    return pos;
}

int vacuum::get_x() {
    return pos.first;
}

int vacuum::get_y() {
    return pos.second;
}
