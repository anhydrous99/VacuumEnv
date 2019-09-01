//
// Created by aherrera on 8/31/19.
//

#ifndef CSCI6350_PROJECT1_ENVIRONMENT_H
#define CSCI6350_PROJECT1_ENVIRONMENT_H

#include <ostream>

//! The Environment contains the vacuum's universe
/*!
 * It consists of a matrix type of interface where
 */
class Environment {
public:
    struct cell {
        int s;
        int l;

        cell() : s(0), l(0) {}
        cell(int _s, int _l) : s(_s), l(_l) {}
    };

    // construct/destroy

    /*!
     * Constructs a Zeroed environment
     * @param n Size side of environment
     */
    explicit Environment(int n);

    /*!
     * Used to access environment cells
     * @param i The row to access
     * @param j The column to access
     * @return The cell at (i, j)
     */
    cell operator()(int i, int j);

private:
    cell *_data;
    int _n;

    friend std::ostream &operator<<(std::ostream &os, const Environment &environment);
};

std::ostream &operator<<(std::ostream &os, const Environment::cell &cell);
std::ostream &operator<<(std::ostream &os, const Environment &environment);

#endif //CSCI6350_PROJECT1_ENVIRONMENT_H
