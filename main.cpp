#include <iostream>

#include "Environment.h"

int main() {
    std::cout << "Hello, World!" << std::endl;
    cell this_is_a_cell(cell::EAST_BOUNDARY_TYPE, cell::CLEAN_VALUE);
    std::cout << this_is_a_cell << std::endl;
    return 0;
}