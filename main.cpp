#include <iostream>
#include <cassert>

#include "cxxopts.hpp"
#include "Environment.h"

int main(int argc, char* argv[]) {
    cxxopts::Options options("VacuumCleaner", "Vacuum Cleaner Agent Program");
    options.add_options()
            ("n", "Size of side of square of environment", cxxopts::value<int>())
            ("s,strategy", "The strategy to use, either 0 or 1", cxxopts::value<int>());
    auto results = options.parse(argc, argv);
    int n = results["n"].as<int>();
    int strategy = results["strategy"].as<int>();

    assert(0 < n);
    assert(strategy == 0 || strategy == 1);
    return EXIT_SUCCESS;
}