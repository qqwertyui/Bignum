#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Bignum.hpp"
#include "TestUtils.hpp"

TEST_CASE("Test operations with generated input") {
  json input;
  SUBCASE("Addition") {
    load_json(input, "add.json");
    for (auto &key : input["testcases"]) {
      Bignum a{key["input"][0]};
      Bignum b{key["input"][1]};
      Bignum c{key["output"]};
      REQUIRE(a + b == c);
    }
  }

  SUBCASE("Subtraction") {
    load_json(input, "sub.json");
    for (auto &key : input["testcases"]) {
      Bignum a{key["input"][0]};
      Bignum b{key["input"][1]};
      Bignum c{key["output"]};
      REQUIRE(a - b == c);
    }
  }

  SUBCASE("Multiplication") {
    load_json(input, "mul.json");
    for (auto &key : input["testcases"]) {
      Bignum a{key["input"][0]};
      Bignum b{key["input"][1]};
      Bignum c{key["output"]};
      REQUIRE(a * b == c);
    }
  }

  SUBCASE("Division") {
    load_json(input, "div.json");
    for (auto &key : input["testcases"]) {
      Bignum a{key["input"][0]};
      Bignum b{key["input"][1]};
      Bignum c{key["output"]};
      REQUIRE(a / b == c);
    }
  }
}