//
// Created by aherrera on 8/31/19.
//

#ifndef CSCI6350_PROJECT1_ENVIRONMENT_H
#define CSCI6350_PROJECT1_ENVIRONMENT_H

#include <ostream>
#include "cell.h"

//! The Environment contains the vacuum's universe
/*!
 * It consists of a matrix type of interface where
 */
class Environment {
    std::vector<cell> _data;
    int _n;

public:
    // construct/destroy

    /*!
     * Constructs a nxn empty environment
     * @param n Size of side of environment
     */
    explicit Environment(int n);

    /*!
     * Constructs nxn environment with (dirty_percentage) clean/dirty cell ratio
     * @param n Size of size of environment
     * @param dirty_percentage Percentage of cells dirty (0.0 <= dirty_percentage <= 1.0)
     */
    Environment(int n, float dirty_percentage);

    /*!
     * Used to access environment cells
     * @param i The row to access
     * @param j The column to access
     * @return The cell at (i, j)
     */
    cell &operator()(int i, int j);

    friend std::ostream &operator<<(std::ostream &os, const Environment &environment);
};

std::ostream &operator<<(std::ostream &os, const Environment &environment);

#endif //CSCI6350_PROJECT1_ENVIRONMENT_H
