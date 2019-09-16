//
// Created by Armando Herrera on 9/16/19.
//

#ifndef CSCI6350_PROJECT1_CUSTOM_ASSERTION_H
#define CSCI6350_PROJECT1_CUSTOM_ASSERTION_H

#include <iostream>

void assert(bool assertion, const std::string &file, const int line, const std::string &msg) {
    if (!assertion) {
        std::cerr << file << ":" << line << " " << msg << std::endl;
        exit(EXIT_FAILURE);
    }
}

#define ASSERT(assertion, msg) assert(assertion, __FILE__, __LINE__, msg);

#endif //CSCI6350_PROJECT1_CUSTOM_ASSERTION_H
