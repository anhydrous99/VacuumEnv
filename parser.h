//
// Created by Armando Herrera on 9/17/19.
//

#ifndef CSCI6350_PROJECT1_PARSER_H
#define CSCI6350_PROJECT1_PARSER_H

#include <vector>
#include <string>

class parser {
public:
    struct single_run {
        int strategy;
        float dirty_percentage;
        float obstruction_percentage;

        single_run() = default;

        single_run(int strat, float dirty, float obstruction) : strategy(strat), dirty_percentage(dirty),
                                                                obstruction_percentage(obstruction) {}
    };

    int side_size;
    int step_limit;
    std::vector<single_run> runs;

    explicit parser(const std::string& conf_path);
};


#endif //CSCI6350_PROJECT1_PARSER_H
