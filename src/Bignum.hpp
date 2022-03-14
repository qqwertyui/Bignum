#include <array>
#include <string>
#include <vector>

class Bignum {
public:
  Bignum() = default;
  Bignum(const std::string &number);
  Bignum(const int &number);
  ~Bignum() = default;

  /*
  DivisionResult indexes:
    0 - quotient
    1 - remainder
  */
  using DivisionResult = std::array<Bignum, 2>;
  Bignum &operator++();
  Bignum operator++(int);
  Bignum &operator--();
  Bignum operator--(int);
  Bignum &operator=(const Bignum &number2);

#include "Bignum_operators.inl"

  /*
     -1 - number1 > number2
     0 - number1 == number2
     1 - number1 < number2
  */
  static int compare(const Bignum &number1, const Bignum &number2);
  static int unsigned_compare(const Bignum &number1, const Bignum &number2);

  static Bignum add(const Bignum &number1, const Bignum &number2);
  static Bignum subtract(const Bignum &number1, const Bignum &number2);
  static Bignum multiply(const Bignum &number1, const Bignum &number2);
  static DivisionResult divide(const Bignum &number1, const Bignum &number2);
  static Bignum pow(const Bignum &base, const Bignum &exponent);
  static Bignum sqrt(const Bignum &number);
  static Bignum abs(const Bignum &number);

  bool isPositive() const;
  bool isNegative() const;
  unsigned int digits() const;
  std::string as_string() const;

  static bool is_same_sign(const Bignum &number1, const Bignum &number2);
  Bignum subnumber(unsigned int index, unsigned int count) const;
  static Bignum pad_with_zeros(const Bignum &number1, const Bignum &number2,
                               unsigned int &zeros_padded);
  static Bignum concatenate(const Bignum &number1, const Bignum &number2);
  static std::vector<std::string> split_into_pairs(const Bignum &number);
  static Bignum small_number_sqrt(const Bignum &number);
  static Bignum find_equation_factor(const Bignum &base, const Bignum &factor);

private:
  Bignum(const std::string &number, bool negative);
  Bignum(const Bignum &number, bool negative);
  static void check_if_valid(const std::string &number);
  static std::string strip_sign(const std::string &number);
  friend std::ostream &operator<<(std::ostream &os, const Bignum &number) {
    return os << number.as_string();
  }
  bool negative{false};
  std::string snumber{"0"};
};
