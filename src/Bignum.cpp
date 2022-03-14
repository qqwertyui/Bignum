#include "Bignum.hpp"
#include <algorithm>
#include <cctype>
#include <stdexcept>

Bignum::Bignum(const std::string &number) {
  check_if_valid(number);
  if (number.front() == '-') {
    negative = true;
  }
  std::string base{strip_sign(number)};
  auto index = base.find_first_not_of('0');
  snumber = (index == std::string::npos) ? "0" : base.substr(index);
  if (snumber.compare("0") == 0) {
    negative = false;
  }
}

Bignum::Bignum(const int &number) {
  std::string raw_number{std::to_string(number)};
  if (raw_number.at(0) == '-') {
    negative = true;
  }
  this->snumber = strip_sign(raw_number);
}

Bignum::Bignum(const std::string &number, bool negative) : Bignum(number) {
  this->negative = negative;
}

Bignum::Bignum(const Bignum &number, bool negative) : Bignum(number) {
  this->negative = negative;
}

void Bignum::check_if_valid(const std::string &number) {
  std::string base{strip_sign(number)};
  bool is_valid = std::all_of(base.begin(), base.end(), isdigit);
  if (not is_valid) {
    throw std::runtime_error("Invalid number error");
  }
}

std::string Bignum::strip_sign(const std::string &number) {
  if (number.size() > 1) {
    return (number.at(0) == '+' or number.at(0) == '-') ? number.substr(1)
                                                        : number;
  }
  return number;
}

Bignum &Bignum::operator++() {
  (*this) += 1;
  return *this;
}

Bignum Bignum::operator++(int) {
  Bignum result{*this};
  (*this) += 1;
  return result;
}

Bignum &Bignum::operator--() {
  (*this) -= 1;
  return *this;
}

Bignum Bignum::operator--(int) {
  Bignum result{*this};
  (*this) -= 1;
  return result;
}

Bignum &Bignum::operator=(const Bignum &number2) {
  if (this != &number2) {
    snumber = number2.snumber;
    negative = number2.negative;
  }
  return *this;
}

bool Bignum::is_same_sign(const Bignum &number1, const Bignum &number2) {
  return (not(number1.isPositive() xor number2.isPositive()));
}

int Bignum::unsigned_compare(const Bignum &number1, const Bignum &number2) {
  return compare(Bignum{number1, false}, Bignum{number2, false});
}

int Bignum::compare(const Bignum &number1, const Bignum &number2) {
  bool number1_is_negative{number1.isNegative()};
  bool number2_is_negative{number2.isNegative()};
  const std::string &sn1{strip_sign(number1.snumber)},
      &sn2{strip_sign(number2.snumber)};

  if (is_same_sign(number1, number2)) {
    if (sn1.compare(sn2) == 0) {
      return 0;
    }
    if (sn1.size() > sn2.size()) {
      return number1_is_negative ? 1 : -1;
    } else if (sn1.size() < sn2.size()) {
      return number1_is_negative ? -1 : 1;
    }
    if (sn1.size() == sn2.size()) {
      for (unsigned int i = 0; i < sn1.size(); i++) {
        if (sn1[i] > sn2[i]) {
          return number1_is_negative ? 1 : -1;
        } else if (sn1[i] < sn2[i]) {
          return number1_is_negative ? -1 : 1;
        }
      }
    }
  }
  return (number1_is_negative == false and number2_is_negative == true) ? -1
                                                                        : 1;
}

bool Bignum::isPositive() const { return (not negative); }

bool Bignum::isNegative() const { return negative; }

Bignum Bignum::abs(const Bignum &number) { return Bignum{number, false}; }

auto unsigned_comparator = [](const Bignum &number1,
                              const Bignum number2) -> bool {
  return (Bignum::unsigned_compare(number1, number2) == 1);
};

Bignum Bignum::add(const Bignum &number1, const Bignum &number2) {
  if (not is_same_sign(number1, number2)) {
    const Bignum &max = std::max(number1, number2, unsigned_comparator);
    const Bignum &min = std::min(number1, number2, unsigned_comparator);
    return Bignum{subtract(Bignum::abs(max), Bignum::abs(min)),
                  max.isNegative()};
  }
  const std::string &sn1{number1.snumber}, &sn2{number2.snumber};
  std::string result{};
  auto idx1{static_cast<int>(sn1.size() - 1)},
      idx2{static_cast<int>(sn2.size() - 1)};
  int carry{};
  while (idx1 >= 0 or idx2 >= 0) {
    int v1 = (idx1 >= 0) ? sn1[idx1--] - 48 : 0;
    int v2 = (idx2 >= 0) ? sn2[idx2--] - 48 : 0;
    int v3 = (v1 + v2 + carry) % 10;
    carry = (v1 + v2 + carry) >= 10;
    result += static_cast<char>(v3 + 48);
  }
  if (carry) {
    result += static_cast<char>(carry + 48);
  }
  return Bignum{std::string{result.rbegin(), result.rend()},
                number1.isNegative()};
}

Bignum Bignum::subtract(const Bignum &number1, const Bignum &number2) {
  if (not is_same_sign(number1, number2)) {
    return Bignum{add(number1, Bignum{number2, not number2.isNegative()}),
                  number1.isNegative()};
  }
  if (number2.isNegative()) {
    return subtract(Bignum::abs(number2), Bignum::abs(number1));
  }
  if (unsigned_compare(number1, number2) == 1) {
    return Bignum{subtract(number2, number1), not number2.isNegative()};
  }
  std::string sn1{number1.snumber}, sn2{number2.snumber};
  auto idx1{static_cast<int>(sn1.size() - 1)},
      idx2{static_cast<int>(sn2.size() - 1)};
  while (idx1 >= 0 or idx2 >= 0) {
    int v1 = (idx1 >= 0) ? sn1[idx1] - 48 : 0;
    int v2 = (idx2 >= 0) ? sn2[idx2] - 48 : 0;
    int v3{};
    if (v1 < v2) {
      int stop = idx1 - 1;
      while (sn1[stop] == '0') {
        stop--;
      }
      sn1[stop]--;
      stop++;
      while (stop < idx1) {
        sn1[stop++] = '9';
      }
      v3 = v1 + 10 - v2;
    } else {
      v3 = v1 - v2;
    }
    sn1[idx1] = v3 + 48;
    idx1--;
    idx2--;
  }
  return Bignum{sn1, number1.isNegative()};
}

Bignum Bignum::multiply(const Bignum &number1, const Bignum &number2) {
  std::string sn1{number1.snumber}, sn2{number2.snumber};
  std::vector<Bignum> numbers{};
  for (int idx2 = sn2.size() - 1; idx2 >= 0; idx2--) {
    int v2 = sn2[idx2] - 48;
    int carry{};
    std::string sum{};
    for (int idx1 = sn1.size() - 1; idx1 >= 0; idx1--) {
      int v1 = sn1[idx1] - 48;
      int v3 = (v2 * v1 + carry) % 10;
      carry = (v2 * v1 + carry) / 10;
      sum += v3 + 48;
    }
    if (carry) {
      sum += carry + 48;
    }
    int trailing_zeros = sn2.size() - 1 - idx2;
    std::string result{sum.rbegin(), sum.rend()};
    for (int i = 0; i < trailing_zeros; i++) {
      result += '0';
    }
    numbers.push_back(Bignum{result});
  }
  Bignum result{};
  for (Bignum &num : numbers) {
    result += num;
  }
  return Bignum{result, not Bignum::is_same_sign(number1, number2)};
}

Bignum::DivisionResult Bignum::divide(const Bignum &number1,
                                      const Bignum &number2) {
  Bignum n1{Bignum::abs(number1)}, n2{Bignum::abs(number2)};
  bool result_negative{not Bignum::is_same_sign(number1, number2)};
  if (n2 == Bignum{"0"}) {
    throw std::runtime_error("Division by 0 error");
  }
  if (unsigned_compare(n1, n2) == 1) {
    return Bignum::DivisionResult{Bignum{"0"}, number2};
  }
  if (n1 == n2) {
    return Bignum::DivisionResult{Bignum{"1", result_negative}, Bignum{"0"}};
  }

  Bignum quotient{};
  while (n1 >= n2) {
    int count = 1;
    Bignum part{};
    while ((part = n1.subnumber(0, count)) < n2) {
      count++;
    }
    int times = 1;
    Bignum subtractor{n2};
    while (subtractor <= part) {
      times++;
      subtractor += n2;
    }
    times--;
    subtractor -= n2;
    unsigned int zeros_padded{};
    subtractor = Bignum::pad_with_zeros(n1, subtractor, zeros_padded);
    Bignum partial_sum =
        Bignum{std::to_string(times)} *
        Bignum::pow(Bignum{"10"}, Bignum{std::to_string(zeros_padded)});
    quotient += partial_sum;
    n1 -= subtractor;
  }
  Bignum remainder{(result_negative ? (n2 - n1) : n1), number2.isNegative()};
  return Bignum::DivisionResult{Bignum{quotient, result_negative}, remainder};
}

Bignum Bignum::pad_with_zeros(const Bignum &number1, const Bignum &number2,
                              unsigned int &zeros_padded) {
  const std::string &sn1{number1.snumber}, &sn2{number2.snumber};
  if (sn1.size() <= sn2.size()) {
    return number2;
  }
  unsigned int zeros_to_pad = sn1.size() - sn2.size();
  std::string result{sn2};
  zeros_padded = 0;
  for (unsigned int i = 0; i < zeros_to_pad; i++) {
    result += '0';
    zeros_padded++;
    if (Bignum{result} > number1) {
      result.pop_back();
      zeros_padded--;
      return Bignum{result};
    }
  }
  return Bignum{result};
}

Bignum Bignum::pow(const Bignum &base, const Bignum &exponent) {
  if (exponent.isNegative()) {
    throw std::runtime_error("Negative exponent not supported error");
  }
  Bignum result{"1"};
  if (exponent == Bignum{"0"}) {
    return result;
  }
  for (Bignum i{"0"}; i < exponent; i++) {
    result *= base;
  }
  return result;
}

Bignum Bignum::sqrt(const Bignum &number) {
  if (number.isNegative()) {
    throw std::runtime_error("Square root of negative number error");
  }
  if (number == Bignum{"0"}) {
    return number;
  }
  auto pairs{split_into_pairs(number)};
  Bignum current{pairs[0]};
  Bignum base{small_number_sqrt(current)};
  Bignum factor_prefix{Bignum{"2"} * base};
  std::string result{base.snumber};

  current -= Bignum::pow(base, Bignum{"2"});

  for (auto it = pairs.begin() + 1; it != pairs.end(); it++) {
    std::string raw_pair{*it};
    current = current.snumber + raw_pair;
    Bignum factor = find_equation_factor(current, factor_prefix);
    result += factor.snumber;
    factor_prefix = Bignum::concatenate(factor_prefix, factor);
    Bignum subtractor = factor_prefix * factor;
    current -= subtractor;
    factor_prefix += factor;
  }
  return Bignum{result};
}

Bignum Bignum::concatenate(const Bignum &number1, const Bignum &number2) {
  return Bignum{number1.snumber + number2.snumber};
}

Bignum Bignum::subnumber(unsigned int index, unsigned int count) const {
  return Bignum{snumber.substr(index, count), negative};
}

unsigned int Bignum::digits() const { return snumber.size(); }

std::string Bignum::as_string() const {
  std::string result{};
  if (isNegative()) {
    result += '-';
  }
  return (result + snumber);
}

std::vector<std::string> Bignum::split_into_pairs(const Bignum &number) {
  std::vector<std::string> pairs{};
  unsigned int i = 0;
  if (number.digits() % 2 == 1) {
    pairs.push_back(number.snumber.substr(i++, 1));
  }
  for (; i < number.digits(); i += 2) {
    pairs.push_back(number.snumber.substr(i, 2));
  }
  return pairs;
}

Bignum Bignum::small_number_sqrt(const Bignum &number) {
  Bignum base{"1"};
  const Bignum exponent{"2"};
  while (Bignum::pow(base, exponent) <= number) {
    base++;
  }
  base--;
  return base;
}

Bignum Bignum::find_equation_factor(const Bignum &base, const Bignum &factor) {
  Bignum multiplier{"0"};
  Bignum current{};
  do {
    multiplier++;
    current = Bignum::concatenate(factor, multiplier) * multiplier;
  } while (current <= base);
  multiplier--;
  return multiplier;
}