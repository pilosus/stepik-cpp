#include <iostream>
using namespace std;

#include <cassert>
#include <string>
#include <cmath>

class Transformer;
class Number;
class BinaryOperation;
class FunctionCall;
class Variable;

struct Scope
{
  virtual ~Scope() { }
  virtual double variableValue(std::string const &name) const = 0;
};

struct Expression
{
  virtual ~Expression() { }

  virtual double evaluate(Scope *sc) const = 0;

  virtual Expression *transform(Transformer *tr) const = 0;
};

struct Number : Expression
{
  Number(double value);
  double value() const;

  double evaluate(Scope *sc) const
  {
    return value_;
  }

  Expression *transform(Transformer *tr) const;

private:
  double value_;
};

struct BinaryOperation : Expression
{
  enum {
    PLUS = '+',
    MINUS = '-',
    DIV = '/',
        MUL = '*'
  };
  BinaryOperation(Expression const *left, int op, Expression const *right);
  ~BinaryOperation();

  double evaluate(Scope *sc) const
  {
    double const l = left()->evaluate(sc);
    double const r = right()->evaluate(sc);

    switch (operation())
      {
      case PLUS: return l + r;
      case MINUS: return l - r;
      case MUL: return l * r;
      case DIV: return l / r;
      }

    assert(0);
    return 0.0l;
  }

  Expression *transform(Transformer *tr) const;
  Expression const *left() const;
  Expression const *right() const;
  int operation() const;

private:
  Expression const *left_;
  Expression const *right_;
  int op_;
};

struct FunctionCall : Expression
{
  FunctionCall(std::string const &name, Expression const *arg);
  ~FunctionCall();

  double evaluate(Scope *sc) const
  {
    double const value = arg()->evaluate(sc);
    if (name() == "sqrt")
      return sqrt(value);
    if (name() == "abs")
      return fabs(value);
    assert(0);
    return 0.0l;
  }

  Expression *transform(Transformer *tr) const;
  std::string const &name() const;
  Expression const *arg() const;

private:
  std::string const name_;
  Expression const *arg_;
};

struct Variable : Expression
{
  Variable(std::string const name);
  std::string const & name() const;

  double evaluate(Scope *sc) const
  {
    double res = sc->variableValue(name_);
    return res;
    //assert(0);
    //return 0.0;
  }

  Expression *transform(Transformer *tr) const;

private:
  std::string const name_;
};

int main() {
  return 0;
}
