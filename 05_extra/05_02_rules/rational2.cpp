#include <iostream>

struct Rational
{
  Rational(int numerator = 0, int denominator = 1);

  void add(Rational rational);
  void sub(Rational rational);
  void mul(Rational rational);
  void div(Rational rational);

  void neg();
  void inv();
  double to_double() const;

  Rational& operator+=(Rational rational);
  Rational& operator-=(Rational rational);
  Rational& operator*=(Rational rational);
  Rational& operator/=(Rational rational);

  Rational operator-();
  Rational operator+();

private:
  int numerator_;
  unsigned denominator_;
};

Rational operator+(Rational r1, Rational r2) {
  return r1 += r2;
}

Rational operator-(Rational r1, Rational r2) {
  return r1 -= r2;
}

Rational operator*(Rational r1, Rational r2) {
  return r1 *= r2;
}

Rational operator/(Rational r1, Rational r2) {
  return r1 /= r2;
}

int main() {
  return 0;
}
