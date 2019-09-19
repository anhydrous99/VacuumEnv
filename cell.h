//
// Created by Armando Herrera on 9/1/19.
//

#ifndef CSCI6350_PROJECT1_CELL_H
#define CSCI6350_PROJECT1_CELL_H

#include <ostream>
#include <vector>

//! The class for a single cell
struct cell {
    //! This is an enum holding boundary types for cell
    enum cell_type {
        NON_BOUNDARY_TYPE = 0, ///< A non-boundary type
        WEST_BOUNDARY_TYPE = 1, ///< A west-boundary type
        NORTH_BOUNDARY_TYPE = 2, ///< A north-boundary type
        EAST_BOUNDARY_TYPE = 3, ///< A east-boundary type
        SOUTH_BOUNDARY_TYPE = 4, ///< A south-boundary type
        NORTHWEST_CORNER_TYPE = 5, ///< A northwest-corner type
        NORTHEAST_CORNER_TYPE = 6, ///< A northeast-corner type
        SOUTHEAST_CORNER_TYPE = 7, ///< A southeast-corner type
        SOUTHWEST_CORNER_TYPE = 8 ///< A southwest-conrner type
    } cellType = NON_BOUNDARY_TYPE;
    //! This is an enum holding whether this cell is bordering an obstacle
    enum cell_obstacle {
        UPPER_OBSTACLE, ///< There is an obstacle in the upper cell
        LOWER_OBSTACLE, ///< There is an obstacle in the lower cell
        LEFT_OBSTACLE, ///< There is an obstacle in the left cell
        RIGHT_OBSTACLE ///< There is an obstacle in the right cell
    };
    //! This is an enum holding whether this cell is clean or dirty
    enum cell_value {
        CLEAN_VALUE = 0, ///< This cell is clean
        DIRTY_VALUE = 1 ///< This cell is dirty
    } cellValue = CLEAN_VALUE;

    std::vector<cell_obstacle> neighborObstacles; //! Holds neighbor obstacle status
    bool contains_obstacle = false; //! Holds whether the current cell contains an obstacle
    bool has_been_transversed = false; //! Holds whether the vacuum has transversed the cell

    /*!
     * The default constructor because setting a constructor remove the implicit addition of the default constructor
     */
    cell() = default;

    /*!
     * A constructor
     * @param ctype The cell border type
     * @param cvalue Whether the cell is clean or dirty
     */
    cell(cell_type ctype, cell_value cvalue) {
        cellType = ctype;
        cellValue = cvalue;
    }
};

/*!
 * The print operator for used with cout.. makes the cell look pretty when printing with cout
 * @param os The output stream
 * @param input_cell The input cell
 * @return The output stream with the cell imprinted on it
 */
std::ostream &operator<<(std::ostream &os, const cell &input_cell);

#endif //CSCI6350_PROJECT1_CELL_H
