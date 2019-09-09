#include <iostream>
#include <random>
#include <cassert>

#include "Environment.h"

int main(int argc, char *argv[]) {
    Environment env1(10, 20);

    std::function<vacuum(const std::string &, Environment &)> strategy_1 = [](const std::string &vacuum_name,
                                                                                    Environment &env) -> vacuum {

    };
    std::function<vacuum(const std::string &, Environment &)> strategy_2 = [=](const std::string &vacuum_name,
                                                                                    Environment &env) -> vacuum {
        vacuum current_vacuum = env.access_vacuum(vacuum_name);
        std::random_device rd;
        std::uniform_int_distribution<int> dis(1, 4);
        int random_number = dis(rd);

        while (true) {

        }
    };
    return EXIT_SUCCESS;
}