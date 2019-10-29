//
// Created by Armando Herrera on 9/1/19.
// CSCI-6350-01 Project 1
// Due: 9/20/2019
//

#include "cell.h"

std::ostream &operator<<(std::ostream &os, const cell &input_cell) {
  os << "{";
  for (const cell::cell_obstacle &obs : input_cell.neighborObstacles) {
    switch (obs) {
      case cell::UPPER_OBSTACLE:
        os << "0,";
        break;
      case cell::LOWER_OBSTACLE:
        os << "1,";
        break;
      case cell::LEFT_OBSTACLE:
        os << "2";
        break;
      case cell::RIGHT_OBSTACLE:
        os << "3,";
    }
  }
  if (!input_cell.contains_obstacle) {

    if (input_cell.has_been_transversed)
      os << "x";
    else if (input_cell.cellValue == cell::CLEAN_VALUE)
      os << "0";
    else
      os << "1";
  } else {
    os << "o";
  }
  os << "}";
  return os;
}
