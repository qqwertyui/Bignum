#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Bignum.hpp"
#include "TestUtils.hpp"

TEST_CASE("Test operations with generated input") {
  json input;
  SUBCASE("Addition") {
    load_json(input, "add.json");
    for (auto &key : input["testcases"]) {
      Bignum a{key["input"][0].get<std::string>()};
      Bignum b{key["input"][1].get<std::string>()};
      Bignum c{key["output"].get<std::string>()};
      REQUIRE(a + b == c);
    }
  }

  SUBCASE("Subtraction") {
    load_json(input, "sub.json");
    for (auto &key : input["testcases"]) {
      Bignum a{key["input"][0].get<std::string>()};
      Bignum b{key["input"][1].get<std::string>()};
      Bignum c{key["output"].get<std::string>()};
      REQUIRE(a - b == c);
    }
  }

  SUBCASE("Multiplication") {
    load_json(input, "mul.json");
    for (auto &key : input["testcases"]) {
      Bignum a{key["input"][0].get<std::string>()};
      Bignum b{key["input"][1].get<std::string>()};
      Bignum c{key["output"].get<std::string>()};
      REQUIRE(a * b == c);
    }
  }

  SUBCASE("Division") {
    load_json(input, "div.json");
    for (auto &key : input["testcases"]) {
      Bignum a{key["input"][0].get<std::string>()};
      Bignum b{key["input"][1].get<std::string>()};
      Bignum c{key["output"].get<std::string>()};
      REQUIRE(a / b == c);
    }
  }
}