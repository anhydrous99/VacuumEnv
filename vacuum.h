//
// Created by Armando Herrera on 9/3/19.
//

#ifndef CSCI6350_PROJECT1_VACUUM_H
#define CSCI6350_PROJECT1_VACUUM_H

#include <functional>
#include <utility>

typedef std::pair<int, int> position;

//! A vacuum agent
/*!
 * This contains information specific to the vacuum agent
 */
class vacuum {
    position pos;
    std::function<position(position)> agent_function;

public:
    vacuum(int x_position, int y_position);
};


#endif //CSCI6350_PROJECT1_VACUUM_H
