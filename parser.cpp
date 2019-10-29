//
// Created by Armando Herrera on 9/17/19.
// CSCI-6350-01 Project 1
// Due: 9/20/2019
//

#include "parser.h"

#include <fstream>
#include "nlohmann/json.hpp"

parser::parser(const std::string &conf_path) {
  // Read from file into a string
  std::fstream file(conf_path);
  std::string str((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

  // Parse json
  auto parsed = nlohmann::json::parse(str);
  side_size = parsed["side_size"].get<int>();
  step_limit = parsed["step_limit"].get<int>();
  print_steps = parsed["print_steps"].get<bool>();
  step_delay = parsed["step_delay"].get<int>();

  auto rns = parsed["runs"];
  for (auto &r : rns) {
    auto obstruction = r.find("obstruction_percentage");
    float obs = (obstruction != r.end()) ? r["obstruction_percentage"].get<float>() : 0.0f;
    runs.emplace_back(single_run(r["strategy"].get<int>(), r["dirty_percentage"].get<float>(),
                                 static_cast<float>(obs)));
  }
}
