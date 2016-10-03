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

  // Step 3
  Rational & operator+=(Rational const& r2) {
    numerator_ = numerator_ * r2.denominator_ + r2.numerator_ * denominator_;
    denominator_ = denominator_ * r2.denominator_;
    return *this;
  }

  Rational & operator+=(int i) {
    numerator_ = numerator_ + denominator_ * i;
    return *this;
  }

  Rational & operator-=(Rational const& r2) {
    numerator_ = numerator_ * r2.denominator_ - r2.numerator_ * denominator_;
    denominator_ = denominator_ * r2.denominator_;
    return *this;
  }

  Rational & operator-=(int i) {
    numerator_ = numerator_ - denominator_ * i;
    return *this;
  }

  Rational & operator*=(Rational const& r2) {
    numerator_ = numerator_ * r2.numerator_;
    denominator_ = denominator_ * r2.denominator_;
    return *this;
  }

  Rational & operator*=(int i) {
    numerator_ = numerator_ * i;
    return *this;
  }

  Rational & operator/=(Rational const& r2) {
    numerator_ = numerator_ * r2.denominator_;
    denominator_ = denominator_ * r2.numerator_;
    return *this;
  }

  Rational & operator/=(int i) {
    denominator_ = denominator_ * i;
    return *this;
  }

  // unary -
  Rational operator-() {
    Rational tmp(*this);
    return Rational(-tmp.numerator_, tmp.denominator_);
  }

  // unary +
  Rational operator+() {
    Rational tmp(*this);
    return tmp;
  }

  // Step 8
  operator double() const {
    Rational tmp(*this);
    return tmp.to_double();
  }

private:
  int numerator_;
  unsigned denominator_;
};

// Step 4
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

// Step 6
bool operator<(Rational const& a, Rational const& b) { 
  //return (a.numerator_ * b.denominator_) < (b.numerator_ * a.denominator_);
  return a.to_double() < b.to_double();
}

bool operator==(Rational const& a, Rational const& b) { 
  return !(a < b) && !(b < a);
}

bool operator!=(Rational const& a, Rational const& b) {
  return !(a == b); 
}

bool operator>(Rational const& a, Rational const& b) {
  return b < a; 
}

bool operator<=(Rational const& a, Rational const& b) { 
  return !(b < a);
}

bool operator>=(Rational const& a, Rational const& b) {
  return !(a < b); 
}

int main() {
  /*
  Rational a(2, 5);
  Rational b(3, 7);
  int i = 2;
  */
     
  return 0;
}
