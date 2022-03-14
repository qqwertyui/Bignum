#pragma once
#include <doctest.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void load_json(json &input, const std::string &input_file) {
  std::ifstream test_file{input_file};
  if (not test_file.good()) {
    REQUIRE(false);
  }
  test_file >> input;
  test_file.close();
}