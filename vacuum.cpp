//
// Created by Armando Herrera on 9/3/19.
//

#include "vacuum.h"

vacuum::vacuum(int x_position, int y_position) {
    pos = std::make_pair(x_position, y_position);
}

position vacuum::get_position() {
    return pos;
}

void vacuum::set_position(position p) {
    pos = p;
}

int vacuum::get_x() {
    return pos.first;
}

int vacuum::get_y() {
    return pos.second;
}
