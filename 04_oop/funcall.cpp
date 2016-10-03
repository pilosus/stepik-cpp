#include <string> // std::string
#include <cassert>
#include <cmath>  // sqrt и fabs

#include "binaryop.cpp"

// эти классы определять заново не нужно
struct Expression;
struct BinaryOperation;
struct Number;

/** 
1) дописываешь функции name и arg, чтобы они возвращали параметры.
2) переопределяешь evaluate, чтобы он считал то, что нам надо(а то
сейчас он virtual из родительского класса),
3) и пишешь деструктор.

*/

struct FunctionCall : Expression
{
  /**
   * @name имя функции, возможные варианты
   *       "sqrt" и "abs".
   *
   *       Объекты, std::string можно
   *       сравнивать с C-строками используя
   *       обычный синтаксис ==.
   *
   * @arg  выражение аргумент функции
   */
  FunctionCall(std::string const &name, Expression const *arg)
    : name_(name), arg_(arg)
  {
    assert(arg_);
    assert(name_ == "sqrt" || name_ == "abs");
  }

  // реализуйте оставшие методы из
  // интерфейса Expression и не забудьте
  // удалить arg_, как это сделано в классе
  // BinaryOperation

  std::string const & name() const
  {
    // put your code here
    return name_;
  }

  Expression const *arg() const
  {
    // here
    return arg_;
    
  }

  // and here
  double evaluate() const 
  {
    double a = arg_->evaluate();
    if (name() == "abs") {
      return std::fabs(a);
    }
    else if (name() == "sqrt") {
      return std::sqrt(a);
    }
  }

  // destructor
  ~FunctionCall()
  {
    //delete name_;
    delete arg_;
  }

private:
  std::string const name_;
  Expression const *arg_;
};

// added by vrs
/*
int main() {
  return 0;
}
*/
