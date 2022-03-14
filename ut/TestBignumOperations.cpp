#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "Bignum.hpp"
#include <doctest.h>

TEST_CASE("test basic operations") {
  REQUIRE(Bignum{"00000123"}.as_string() == "123");
  REQUIRE(Bignum{"0"}.as_string() == "0");
  REQUIRE(Bignum{"456"}.as_string() == "456");
  REQUIRE(Bignum{"1"}.as_string() == "1");

  CHECK_THROWS_WITH(Bignum{"asdf"}, "Invalid number error");
  CHECK_THROWS_WITH(Bignum{"+"}, "Invalid number error");
  CHECK_THROWS_WITH(Bignum{"-"}, "Invalid number error");
  REQUIRE(Bignum{"-1"}.as_string() == "-1");
  REQUIRE(Bignum{"+1"}.as_string() == "1");
  REQUIRE(Bignum{"+0"}.as_string() == "0");
  REQUIRE(Bignum{"-0"}.as_string() == "0");
  REQUIRE(Bignum{"0"}.as_string() == "0");

  REQUIRE((Bignum{"10"} > Bignum{"5"}) == true);
  REQUIRE((Bignum{"10"} > Bignum{"10"}) == false);
  REQUIRE((Bignum{"10"} >= Bignum{"10"}) == true);
  REQUIRE((Bignum{"10"} < Bignum{"5"}) == false);
  REQUIRE((Bignum{"10"} < Bignum{"11"}) == true);
  REQUIRE((Bignum{"10"} <= Bignum{"10"}) == true);
  REQUIRE((Bignum{"10"} == Bignum{"10"}) == true);
  REQUIRE((Bignum{"10"} == Bignum{"9"}) == false);
  REQUIRE((Bignum{"10"} != Bignum{"9"}) == true);

  REQUIRE((Bignum{"-5"} < Bignum{"5"}) == true);
  REQUIRE((Bignum{"-5"} <= Bignum{"-5"}) == true);
  REQUIRE((Bignum{"-5"} < Bignum{"-4"}) == true);
  REQUIRE((Bignum{"-5"} > Bignum{"0"}) == false);
  REQUIRE((Bignum{"-5"} == Bignum{"-5"}) == true);
  REQUIRE((Bignum{"-5"} == Bignum{"5"}) == false);
  REQUIRE((Bignum{"-4"} != Bignum{"4"}) == true);

  REQUIRE(Bignum::abs(Bignum{"10"}) == Bignum{"10"});
  REQUIRE(Bignum::abs(Bignum{"-10"}) == Bignum{"10"});
  REQUIRE(Bignum::abs(Bignum{"-40"}) == Bignum{"40"});
  REQUIRE(Bignum::abs(Bignum{"-0"}) == Bignum{"0"});

  REQUIRE(Bignum{"1"} + Bignum{"2"} == Bignum{"3"});
  REQUIRE(Bignum{"0"} + Bignum{"0"} == Bignum{"0"});
  REQUIRE(Bignum{"10"} + Bignum{"20"} == Bignum{"30"});
  REQUIRE(Bignum{"51"} + Bignum{"5"} == Bignum{"56"});
  REQUIRE(Bignum{"9"} + Bignum{"1"} == Bignum{"10"});
  REQUIRE(Bignum{"99"} + Bignum{"1"} == Bignum{"100"});
  REQUIRE(Bignum{"98"} + Bignum{"1"} == Bignum{"99"});
  REQUIRE(Bignum{"5123412893128930712698618971232"} +
              Bignum{"689075890789731287698751434124121098789054351312"} ==
          Bignum{"689075890789731292822164327253051811487673322544"});
  REQUIRE(Bignum{"1894712890371289034712638901261789246789312364120879456108734"
                 "60182375610782361027845612890601827946102789312608945631"} +
              Bignum{"324892364089712659872641089276307846120873612078941236478"
                     "90236059782464170893462907864078"} ==
          Bignum{"1894712890371289034712638901586681610879025023993520545385042"
                 "44794462971990255151493503126661610410273682775516809709"});

  REQUIRE(Bignum{"-1"} + Bignum{"-2"} == Bignum{"-3"});
  REQUIRE(Bignum{"-1"} + Bignum{"2"} == Bignum{"1"});
  REQUIRE(Bignum{"-3"} + Bignum{"2"} == Bignum{"-1"});
  REQUIRE(Bignum{"-15"} + Bignum{"421"} == Bignum{"406"});
  REQUIRE(Bignum{"-15"} + Bignum{"-421"} == Bignum{"-436"});
  REQUIRE(Bignum{"0"} + Bignum{"1"} == Bignum{"1"});
  REQUIRE(Bignum{"0"} + Bignum{"-1"} == Bignum{"-1"});

  Bignum n1{"100"};
  REQUIRE(n1 == Bignum{"100"});
  n1 += Bignum{"500"};
  REQUIRE(n1 == Bignum{"600"});
  n1 += Bignum{"600"};
  REQUIRE(n1 == Bignum{"1200"});
  n1 += Bignum{"-100"};
  REQUIRE(n1 == Bignum{"1100"});
  n1 += Bignum{"-1100"};
  REQUIRE(n1 == Bignum{"0"});
  n1 += Bignum{"-100"};
  REQUIRE(n1 == Bignum{"-100"});
  n1 += Bignum{"300"};
  REQUIRE(n1 == Bignum{"200"});

  REQUIRE(Bignum{"2"} - Bignum{"1"} == Bignum{"1"});
  REQUIRE(Bignum{"10"} - Bignum{"1"} == Bignum{"9"});
  REQUIRE(Bignum{"100"} - Bignum{"1"} == Bignum{"99"});
  REQUIRE(Bignum{"50"} - Bignum{"1"} == Bignum{"49"});
  REQUIRE(Bignum{"100"} - Bignum{"11"} == Bignum{"89"});
  REQUIRE(Bignum{"5000000000000"} - Bignum{"1248907"} ==
          Bignum{"4999998751093"});
  REQUIRE(Bignum{"32189071289037612890371289045161302897"} -
              Bignum{"82394312789612978631273798"} ==
          Bignum{"32189071288955218577581676066530029099"});

  REQUIRE(Bignum{"10"} - Bignum{"20"} == Bignum{"-10"});
  REQUIRE(Bignum{"5"} - Bignum{"6"} == Bignum{"-1"});
  REQUIRE(Bignum{"5"} - Bignum{"-6"} == Bignum{"11"});
  REQUIRE(Bignum{"-5"} - Bignum{"-6"} == Bignum{"1"});
  REQUIRE(Bignum{"0"} - Bignum{"-6"} == Bignum{"6"});
  REQUIRE(Bignum{"123"} - Bignum{"-124"} == Bignum{"247"});

  Bignum n2{"1000"};
  n2 -= Bignum{"100"};
  REQUIRE(n2 == Bignum{"900"});
  n2 -= Bignum{"50"};
  REQUIRE(n2 == Bignum{"850"});
  n2 -= Bignum{"30"};
  REQUIRE(n2 == Bignum{"820"});
  n2 -= Bignum{"819"};
  REQUIRE(n2 == Bignum{"1"});
  n2 -= Bignum{"1"};
  REQUIRE(n2 == Bignum{"0"});

  REQUIRE(Bignum{"2"} * Bignum{"1"} == Bignum{"2"});
  REQUIRE(Bignum{"2"} * Bignum{"2"} == Bignum{"4"});
  REQUIRE(Bignum{"4"} * Bignum{"4"} == Bignum{"16"});
  REQUIRE(Bignum{"2"} * Bignum{"10"} == Bignum{"20"});
  REQUIRE(Bignum{"51"} * Bignum{"28"} == Bignum{"1428"});
  REQUIRE(Bignum{"17"} * Bignum{"42"} == Bignum{"714"});
  REQUIRE(Bignum{"12312453428290370948"} * Bignum{"31231279807"} ==
          Bignum{"384533678129592984720811847036"});
  REQUIRE(Bignum{"0"} * Bignum{"0"} == Bignum{"0"});
  REQUIRE(Bignum{"0"} * Bignum{"1"} == Bignum{"0"});
  REQUIRE(Bignum{"0"} * Bignum{"10"} == Bignum{"0"});
  REQUIRE(Bignum{"0"} * Bignum{"20"} == Bignum{"0"});

  Bignum n3{"2"};
  n3 *= Bignum{"2"};
  REQUIRE(n3 == Bignum{"4"});
  n3 *= Bignum{"3"};
  REQUIRE(n3 == Bignum{"12"});
  n3 *= Bignum{"10"};
  REQUIRE(n3 == Bignum{"120"});
  n3 *= Bignum{"5"};
  REQUIRE(n3 == Bignum{"600"});
  n3 *= Bignum{"1"};
  REQUIRE(n3 == Bignum{"600"});
  n3 *= Bignum{"0"};
  REQUIRE(n3 == Bignum{"0"});
  n3 *= Bignum{"100"};
  REQUIRE(n3 == Bignum{"0"});

  REQUIRE(Bignum{"10"} * Bignum{"-20"} == Bignum{"-200"});
  REQUIRE(Bignum{"-10"} * Bignum{"-20"} == Bignum{"200"});
  REQUIRE(Bignum{"-10"} * Bignum{"20"} == Bignum{"-200"});

  REQUIRE(Bignum{"231"}.subnumber(0, 2) == Bignum{"23"});
  REQUIRE(Bignum{"1000"}.subnumber(0, 3) == Bignum{"100"});
  REQUIRE(Bignum{"1000"}.subnumber(1, 3) == Bignum{"0"});
  REQUIRE(Bignum{"1000"}.subnumber(2, 1) == Bignum{"0"});
  REQUIRE(Bignum{"231"}.subnumber(1, 1) == Bignum{"3"});
  REQUIRE(Bignum{"231"}.subnumber(2, 1) == Bignum{"1"});
  REQUIRE(Bignum{"32109854901"}.subnumber(3, 1) == Bignum{"0"});
  REQUIRE(Bignum{"32109854901"}.subnumber(3, 4) == Bignum{"0985"});
  REQUIRE(Bignum{"32109854901"}.subnumber(8, 3) == Bignum{"901"});

  unsigned int dummy{};
  REQUIRE(Bignum::pad_with_zeros(Bignum{"123"}, Bignum{"1"}, dummy) ==
          Bignum{"100"});
  REQUIRE(Bignum::pad_with_zeros(Bignum{"12"}, Bignum{"1"}, dummy) ==
          Bignum{"10"});
  REQUIRE(Bignum::pad_with_zeros(Bignum{"1"}, Bignum{"1"}, dummy) ==
          Bignum{"1"});
  REQUIRE(Bignum::pad_with_zeros(Bignum{"0"}, Bignum{"0"}, dummy) ==
          Bignum{"0"});
  REQUIRE(Bignum::pad_with_zeros(Bignum{"4123412"}, Bignum{"312"}, dummy) ==
          Bignum{"3120000"});

  REQUIRE(Bignum::pow(Bignum{"2"}, Bignum{"0"}) == Bignum{"1"});
  REQUIRE(Bignum::pow(Bignum{"2"}, Bignum{"4"}) == Bignum{"16"});
  REQUIRE(Bignum::pow(Bignum{"1"}, Bignum{"4"}) == Bignum{"1"});
  REQUIRE(Bignum::pow(Bignum{"10"}, Bignum{"4"}) == Bignum{"10000"});
  REQUIRE(Bignum::pow(Bignum{"5"}, Bignum{"2"}) == Bignum{"25"});
  REQUIRE(Bignum::pow(Bignum{"312412"}, Bignum{"42"}) ==
          Bignum{"6005700901961995830390101961945491085423013514117050961600927"
                 "7142598299486088832206022261609784606673998812617317403078477"
                 "9864363406056322310269026409674502149891496256428095852947334"
                 "967323690573425635448551136953084599264968966144"});

  REQUIRE(Bignum::pow(Bignum{"-2"}, Bignum{"2"}) == Bignum{"4"});
  REQUIRE(Bignum::pow(Bignum{"-2"}, Bignum{"3"}) == Bignum{"-8"});
  REQUIRE(Bignum::pow(Bignum{"-2"}, Bignum{"4"}) == Bignum{"16"});
  REQUIRE(Bignum::pow(Bignum{"-2"}, Bignum{"5"}) == Bignum{"-32"});

  REQUIRE(Bignum{"10"} / Bignum{"2"} == Bignum{"5"});
  REQUIRE(Bignum{"20"} / Bignum{"2"} == Bignum{"10"});
  REQUIRE(Bignum{"10"} / Bignum{"5"} == Bignum{"2"});
  REQUIRE(Bignum{"15"} / Bignum{"5"} == Bignum{"3"});
  REQUIRE(Bignum{"100"} / Bignum{"2"} == Bignum{"50"});
  REQUIRE(Bignum{"50"} / Bignum{"3"} == Bignum{"16"});
  REQUIRE(Bignum{"41"} / Bignum{"32"} == Bignum{"1"});
  REQUIRE(Bignum{"10"} / Bignum{"10"} == Bignum{"1"});
  REQUIRE(Bignum{"81"} / Bignum{"9"} == Bignum{"9"});
  REQUIRE(Bignum{"729"} / Bignum{"9"} == Bignum{"81"});
  REQUIRE(Bignum{"523341"} / Bignum{"123"} == Bignum{"4254"});
  REQUIRE(Bignum{"6345234"} / Bignum{"31251"} == Bignum{"203"});

  REQUIRE(Bignum{"-10"} / Bignum{"2"} == Bignum{"-5"});
  REQUIRE(Bignum{"50"} / Bignum{"-2"} == Bignum{"-25"});
  REQUIRE(Bignum{"-50"} / Bignum{"-2"} == Bignum{"25"});

  Bignum n4{"1423"};
  n4 /= Bignum{"31"};
  REQUIRE(n4 == Bignum{"45"});
  n4 /= Bignum{"3"};
  REQUIRE(n4 == Bignum{"15"});
  n4 /= Bignum{"1"};
  REQUIRE(n4 == Bignum{"15"});
  n4 /= Bignum{"6"};
  REQUIRE(n4 == Bignum{"2"});
  n4 /= Bignum{"2"};
  REQUIRE(n4 == Bignum{"1"});
  CHECK_THROWS_WITH(n4 / Bignum{"0"}, "Division by 0 error");

  REQUIRE(Bignum{"10"} % Bignum{"2"} == Bignum{"0"});
  REQUIRE(Bignum{"11"} % Bignum{"2"} == Bignum{"1"});
  REQUIRE(Bignum{"10"} % Bignum{"1"} == Bignum{"0"});
  REQUIRE(Bignum{"14"} % Bignum{"3"} == Bignum{"2"});
  REQUIRE(Bignum{"123"} % Bignum{"63"} == Bignum{"60"});
  REQUIRE(Bignum{"5113"} % Bignum{"332"} == Bignum{"133"});
  REQUIRE(Bignum{"1312"} % Bignum{"111"} == Bignum{"91"});
  REQUIRE(Bignum{"512312879132"} % Bignum{"1522234"} == Bignum{"459730"});

  REQUIRE(Bignum{"10"} % Bignum{"-7"} == Bignum{"-4"});
  REQUIRE(Bignum{"10"} % Bignum{"-6"} == Bignum{"-2"});
  REQUIRE(Bignum{"100"} % Bignum{"-9"} == Bignum{"-8"});
  REQUIRE(Bignum{"100"} % Bignum{"-23"} == Bignum{"-15"});
  REQUIRE(Bignum{"541233"} % Bignum{"-235"} == Bignum{"-207"});
  REQUIRE(Bignum{"-541233"} % Bignum{"-235"} == Bignum{"-28"});
  REQUIRE(Bignum{"-541233"} % Bignum{"235"} == Bignum{"207"});

  Bignum n5{"1312317896236129876489"};
  n5 %= Bignum{"123124541223"};
  REQUIRE(n5 == Bignum{"47055264241"});
  n5 %= Bignum{"123123"};
  REQUIRE(n5 == Bignum{"116101"});
  n5 %= Bignum{"132"};
  REQUIRE(n5 == Bignum{"73"});
  n5 %= Bignum{"13"};
  REQUIRE(n5 == Bignum{"8"});
  n5 %= Bignum{"2"};
  REQUIRE(n5 == Bignum{"0"});

  REQUIRE(Bignum::concatenate(Bignum{"123"}, Bignum{"456"}) ==
          Bignum{"123456"});
  REQUIRE(Bignum::concatenate(Bignum{"333"}, Bignum{"444"}) ==
          Bignum{"333444"});
  REQUIRE(Bignum::concatenate(Bignum{"1"}, Bignum{"1"}) == Bignum{"11"});
  REQUIRE(Bignum::concatenate(Bignum{"0"}, Bignum{"1"}) == Bignum{"1"});
  REQUIRE(Bignum::concatenate(Bignum{"31"}, Bignum{"12"}) == Bignum{"3112"});
  REQUIRE(Bignum::concatenate(Bignum{"0"}, Bignum{"0"}) == Bignum{"0"});

  REQUIRE(Bignum::split_into_pairs(Bignum{"123"}) ==
          std::vector<std::string>{"1", "23"});
  REQUIRE(Bignum::split_into_pairs(Bignum{"0"}) ==
          std::vector<std::string>{"0"});
  REQUIRE(Bignum::split_into_pairs(Bignum{"1234"}) ==
          std::vector<std::string>{"12", "34"});
  REQUIRE(Bignum::split_into_pairs(Bignum{"1234567"}) ==
          std::vector<std::string>{"1", "23", "45", "67"});

  REQUIRE(Bignum::small_number_sqrt(Bignum{"14"}) == Bignum{"3"});
  REQUIRE(Bignum::small_number_sqrt(Bignum{"41"}) == Bignum{"6"});
  REQUIRE(Bignum::small_number_sqrt(Bignum{"36"}) == Bignum{"6"});
  REQUIRE(Bignum::small_number_sqrt(Bignum{"4"}) == Bignum{"2"});
  REQUIRE(Bignum::small_number_sqrt(Bignum{"5"}) == Bignum{"2"});
  REQUIRE(Bignum::small_number_sqrt(Bignum{"10"}) == Bignum{"3"});
  REQUIRE(Bignum::small_number_sqrt(Bignum{"45123"}) == Bignum{"212"});
  REQUIRE(Bignum::small_number_sqrt(Bignum{"1234"}) == Bignum{"35"});

  REQUIRE(Bignum::find_equation_factor(Bignum{"30"}, Bignum{"1"}) ==
          Bignum{"2"});
  REQUIRE(Bignum::find_equation_factor(Bignum{"252"}, Bignum{"2"}) ==
          Bignum{"8"});
  REQUIRE(Bignum::find_equation_factor(Bignum{"2883"}, Bignum{"36"}) ==
          Bignum{"7"});
  REQUIRE(Bignum::find_equation_factor(Bignum{"31413"}, Bignum{"374"}) ==
          Bignum{"8"});

  REQUIRE(Bignum::sqrt(Bignum{"1"}) == Bignum{"1"});
  REQUIRE(Bignum::sqrt(Bignum{"2"}) == Bignum{"1"});
  REQUIRE(Bignum::sqrt(Bignum{"4"}) == Bignum{"2"});
  REQUIRE(Bignum::sqrt(Bignum{"5"}) == Bignum{"2"});
  REQUIRE(Bignum::sqrt(Bignum{"6"}) == Bignum{"2"});
  REQUIRE(Bignum::sqrt(Bignum{"7"}) == Bignum{"2"});
  REQUIRE(Bignum::sqrt(Bignum{"8"}) == Bignum{"2"});
  REQUIRE(Bignum::sqrt(Bignum{"9"}) == Bignum{"3"});
  REQUIRE(Bignum::sqrt(Bignum{"10"}) == Bignum{"3"});
  REQUIRE(Bignum::sqrt(Bignum{"11"}) == Bignum{"3"});
  REQUIRE(Bignum::sqrt(Bignum{"12"}) == Bignum{"3"});
  REQUIRE(Bignum::sqrt(Bignum{"13"}) == Bignum{"3"});
  REQUIRE(Bignum::sqrt(Bignum{"14"}) == Bignum{"3"});
  REQUIRE(Bignum::sqrt(Bignum{"15"}) == Bignum{"3"});
  REQUIRE(Bignum::sqrt(Bignum{"16"}) == Bignum{"4"});
  REQUIRE(Bignum::sqrt(Bignum{"12345"}) == Bignum{"111"});
  REQUIRE(Bignum::sqrt(Bignum{"1234531297868914"}) == Bignum{"35135897"});
  REQUIRE(Bignum::sqrt(Bignum{"12345312"}) == Bignum{"3513"});
  REQUIRE(Bignum::sqrt(Bignum{"64523135"}) == Bignum{"8032"});
  REQUIRE(Bignum::sqrt(Bignum{"183296712983761290874562378"}) ==
          Bignum{"13538711644161"});

  CHECK_THROWS_WITH(Bignum::sqrt(Bignum{"-10"}),
                    "Square root of negative number error");
  CHECK_THROWS_WITH(Bignum::sqrt(Bignum{"-1"}),
                    "Square root of negative number error");
}