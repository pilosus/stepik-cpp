#include <cassert> // assert

struct Expression
{
  // put your code here
  virtual double evaluate() const = 0;
  virtual ~Expression() {} // чтобы не было утечек памяти
};

struct Number : Expression
{
  Number(double value)
    : value_(value)
  {}

  double value() const
  { return value_; }

  double evaluate() const
  { return value_; }

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

  BinaryOperation(Expression const *left, int op, Expression const *right)
    : left_(left), op_(op), right_(right)
  { assert(left_ && right_); }

  ~BinaryOperation()
  {
    delete left_;
    delete right_;
  }

  Expression const *left() const
  { return left_; }

  Expression const *right() const
  { return right_; }

  int operation() const
  { return op_; }

  double evaluate() const
  {
    double left = left_->evaluate();
    double right = right_->evaluate();
    switch (op_)
      {
      case PLUS: return left + right;
      case MINUS: return left - right;
      case DIV: return left / right;
      case MUL: return left * right;
      }
    assert(0);
    return 0.0;
  }

private:
  Expression const *left_;
  Expression const *right_;
  int op_;
};

/*
int main() {
  return 0;
}
*/
