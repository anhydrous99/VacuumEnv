//
// Created by Armando Herrera on 9/16/19.
// CSCI-6350-01 Project 1
// Due: 9/20/2019
//

#ifndef CSCI6350_PROJECT1_CUSTOM_ASSERTION_H
#define CSCI6350_PROJECT1_CUSTOM_ASSERTION_H

#include <iostream>
#if (_MSC_VER >= 1910 && _MSC_VER <= 1916)
#include <string>
#endif

#ifdef __clang__
#undef ASSERT
#undef assert
#endif

/*!
 * If assertion fails, it prints out failed line, file, and message. Used with ASSERT macro function.
 * @param assertion
 * @param file
 * @param line
 * @param msg
 */
void assert(bool assertion, const std::string &file, const int line, const std::string &msg) {
  if (!assertion) {
    std::cerr << file << ":" << line << " " << msg << std::endl;
    exit(EXIT_FAILURE);
  }
}

#define ASSERT(assertion, msg) assert(assertion, __FILE__, __LINE__, msg);

#endif //CSCI6350_PROJECT1_CUSTOM_ASSERTION_H
