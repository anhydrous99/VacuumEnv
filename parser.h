//
// Created by Armando Herrera on 9/17/19.
//

#ifndef CSCI6350_PROJECT1_PARSER_H
#define CSCI6350_PROJECT1_PARSER_H

#include <vector>
#include <string>

//! Parses the JSON config file
class parser {
public:
    //! Contains information for a single run
    struct single_run {
        int strategy; //! Which strategy to use
        float dirty_percentage; //! The percentage of cells to be dirty
        float obstruction_percentage; //! The percentage of cells that are obstructions

        single_run() = default;

        /*!
         * Constructs the single_run class
         * @param strat
         * @param dirty
         * @param obstruction
         */
        single_run(int strat, float dirty, float obstruction) : strategy(strat), dirty_percentage(dirty),
                                                                obstruction_percentage(obstruction) {}
    };

    int side_size; //! Size of side of environment
    int step_limit; //! Iteration Limit
    std::vector<single_run> runs; //! Vector containing runs

    /*!
     * Parses the JSON configuration file at conf_path and stores it in the class's variables
     * @param conf_path Path to JSON configuration file
     */
    explicit parser(const std::string& conf_path);
};


#endif //CSCI6350_PROJECT1_PARSER_H
