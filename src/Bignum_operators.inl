template <typename T> bool operator>(const T &number2) const {
  return (compare(*this, Bignum{number2}) == -1);
}

template <typename T> bool operator>=(const T &number2) const {
  return (compare(*this, Bignum{number2}) == -1) or
         (compare(*this, Bignum{number2}) == 0);
}

template <typename T> bool operator<=(const T &number2) const {
  return (compare(*this, Bignum{number2}) == 1) or
         (compare(*this, Bignum{number2}) == 0);
}

template <typename T> bool operator<(const T &number2) const {
  return (compare(*this, Bignum{number2}) == 1);
}

template <typename T> bool operator==(const T &number2) const {
  return (compare(*this, Bignum{number2}) == 0);
}

template <typename T> bool operator!=(const T &number2) const {
  return (compare(*this, Bignum{number2}) != 0);
}

template <typename T> Bignum operator+(const T &number2) {
  return add(*this, Bignum{number2});
}

template <typename T> Bignum &operator+=(const T &number2) {
  *this = add(*this, Bignum{number2});
  return *this;
}

template <typename T> Bignum operator-(const T &number2) {
  return subtract(*this, Bignum{number2});
}

template <typename T> Bignum &operator-=(const T &number2) {
  *this = subtract(*this, Bignum{number2});
  return *this;
}

template <typename T> Bignum operator*(const T &number2) {
  return multiply(*this, Bignum{number2});
}

template <typename T> Bignum &operator*=(const T &number2) {
  *this = multiply(*this, Bignum{number2});
  return *this;
}

template <typename T> Bignum operator/(const T &number2) {
  return divide(*this, Bignum{number2})[0];
}

template <typename T> Bignum &operator/=(const T &number2) {
  *this = divide(*this, Bignum{number2})[0];
  return *this;
}

template <typename T> Bignum operator%(const T &number2) {
  return divide(*this, Bignum{number2})[1];
}

template <typename T> Bignum &operator%=(const T &number2) {
  *this = divide(*this, Bignum{number2})[1];
  return *this;
}