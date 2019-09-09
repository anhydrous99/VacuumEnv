//
// Created by aherrera on 8/31/19.
//

#ifndef CSCI6350_PROJECT1_ENVIRONMENT_H
#define CSCI6350_PROJECT1_ENVIRONMENT_H

#include <ostream>
#include <map>
#include "vacuum.h"
#include "cell.h"

//! The Environment contains the vacuum's universe
/*!
 * It consists of a matrix type of interface where
 */
class Environment {
    std::function<char(const std::string &, Environment&)> agent_function;
    std::map<std::string, vacuum> _vacuums;
    std::vector<cell> _data;
    int _n;

    void recalculate_neighbor_obstacles();
public:
    // construct/destroy

    /*!
     * Constructs a nxn empty environment
     * @param n Size of side of environment
     */
    explicit Environment(int n);

    /*!
     * Constructs nxn environment with (dirty_percentage) clean/dirty cell ratio
     * @param n Size of side of environment
     * @param dirty_percentage Percentage of cells dirty (0.0 <= dirty_percentage <= 1.0)
     */
    Environment(int n, float dirty_percentage);

    /*!
     * Constructs nxn environment with (dirty_percentage) clean/dirty cell ratio and
     * (pertange_obstacle) obstacle/non-obstacle ratio
     * @param n Size of size of environment
     * @param dirty_percentage Percentage of cells dirty (0.0 <= dirty_percentage <= 1.0)
     * @param percentage_obstacle Percentage of cells obstacles (0.0 <= percentage_obstacle <= 1.0)
     */
    Environment(int n, float dirty_percentage, float percentage_obstacle);

    /*!
     * Used to access environment cells
     * @param i The row to access
     * @param j The column to access
     * @return The cell at (i, j)
     */
    cell &operator()(int i, int j);

    /*!
     * Used to access environment cells
     * @param p Position type, derived from std::pair<int, int>
     * @return returns cell at position p
     */
    cell &operator()(position p);

    /*!
     * Used to access environment cells consecutively
     * @param i The index
     * @return The cell at index i
     */
    cell &operator[](int i);

    /*!
     * Adds a vacuum to the environment
     * @param i Ith column to put vacuum at
     * @param j Jth row to put vacuum at
     */
    void add_vacuum(int i, int j, const std::string &name);

    /*!
     * Gets reference to vacuum "name"
     * @param name Name of vacuum
     * @return A reference to the vacuum
     */
    vacuum &access_vacuum(const std::string &name);

    /*!
     * Move a vacuum
     * @param direction
     */
    void move_vacuum(const std::string &name, char direction);

    /*!
     * Steps a vacuum by 1 step using a preset vacuum function
     * @param vacuum_name The name of the vacuum
     * @return Whether the Environment is clean
     */
    bool step_vacuum(const std::string &vacuum_name);

    /*!
     * Changes the agent function
     * @param func
     */
    void add_agent_function(const std::function<char(const std::string&, Environment&)> &func);

    /*!
     * Steps all vacuums by 1 using a preset vacuum function
     * @return Whether the Environment is clean
     */
    bool step_vacuums();

    /*!
     * Check if environment has been cleaned
     * @return True if cleaned False otherwise
     */
    bool check_all_clean();

    /*!
     * Gets size of a side of the Environment
     * @return The size of a side of the Environment
     */
    int side_size();

    /*!
     * Returns a pointer to cell data
     * @return
     */
    cell *data();

    friend std::ostream &operator<<(std::ostream &os, const Environment &environment);
};

/*!
 * Operator to print Environment
 * @param os The output stream
 * @param environment The environment to print
 * @return The output stream with the environment em-printed on it
 */
std::ostream &operator<<(std::ostream &os, const Environment &environment);

#endif //CSCI6350_PROJECT1_ENVIRONMENT_H
