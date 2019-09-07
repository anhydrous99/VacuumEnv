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

public:
    vacuum() = default;
    /*!
     * Constructs a vacuum object
     * @param x_position
     * @param y_position
     */
    vacuum(int x_position, int y_position);

    /*!
     * Gets the position of the vacuum
     * @return The position of the object, a pair of integers
     */
    position get_position();

    /*!
     * Sets the position of vacuum
     * @param p The position withing the Environment to set the vacuum
     */
    void set_position(position p);

    /*!
     * Gets the x-axis position of the vacuum
     * @return An integer representing the x-axis of the vacuum
     */
    int get_x();

    /*!
     * Gets the y-axis position of the vacuum
     * @return An integer representing the x-axis of the vacuum
     */
    int get_y();
};


#endif //CSCI6350_PROJECT1_VACUUM_H
