#include <iostream>
using namespace std;

#include <cassert>
#include <string>
#include <cmath>

struct Transformer;
struct Number;
struct BinaryOperation;
struct FunctionCall;
struct Variable;

struct Expression
{
  virtual ~Expression() { }
  virtual double evaluate() const = 0;
  virtual Expression *transform(Transformer *tr) const = 0;
};

struct Transformer
{
  virtual ~Transformer() { }
  virtual Expression *transformNumber(Number const *) = 0;
  virtual Expression *transformBinaryOperation(BinaryOperation const *) = 0;
  virtual Expression *transformFunctionCall(FunctionCall const *) = 0;
  virtual Expression *transformVariable(Variable const *) = 0;
};

struct Number : Expression
{
  Number(double value);
  double value() const;
  double evaluate() const;
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
  double evaluate() const;
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
  double evaluate() const;
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
  double evaluate() const;
  Expression *transform(Transformer *tr) const;

private:
  std::string const name_;
};


/**
 * реализуйте все необходимые методы класса
 * вы можете определять любые вспомогательные
 * методы, если хотите
 */
struct CopySyntaxTree : Transformer
{
  Expression *transformNumber(Number const *number)
  { 
    Expression * exp = new Number(number->value());
    return exp;
  }

  Expression *transformBinaryOperation(BinaryOperation const *binop)
  { 
    Expression * exp = new BinaryOperation((binop->left())->transform(this), 
					   binop->operation(),
					   (binop->right())->transform(this));
    return exp;
  }

  Expression *transformFunctionCall(FunctionCall const *fcall)
  { 
    Expression * exp = new FunctionCall(fcall->name(), 
					(fcall->arg())->transform(this));
    return exp;
  }

  Expression *transformVariable(Variable const *var)
  { 
    Expression *exp = new Variable(var->name());
    return exp;
  }

  ~CopySyntaxTree() { };

};

/**
 * реализуйте все необходимые методы
 * если считаете нужным, то можете
 * заводить любые вспомогательные
 * методы
 */


struct FoldConstants : Transformer
{
  Expression *transformNumber(Number const *number)
  { 
    Expression * exp = new Number(number->value());
    return exp;
  }

  Expression *transformBinaryOperation(BinaryOperation const *binop)
  { 
    // 1. Создаем указатели на левое и правое выражение
    Expression * nleft = (binop->left())->transform(this);
    Expression * nright = (binop->right())->transform(this);
    int noperation = binop->operation();

    // 2. Создаем новый объект типа BinaryOperation с новыми указателями
    BinaryOperation * nbinop = new BinaryOperation(nleft, 
						   noperation,
						   // binop->operation(),
						   nright);
    // 3. Проверяем на приводимость указателей к типу Number
    Number * nleft_is_number = dynamic_cast<Number *>(nleft);
    Number * nright_is_number = dynamic_cast<Number *>(nright);
    if (nleft_is_number && nright_is_number){
      // 3.1 Вычисляем значение выражения
      Expression * result = new Number(binop->evaluate());

      // 3.2 Освобождаем память
      delete nbinop;
      // 3.3 Возвращаем результат
      return result;
    }
    else {
      return nbinop;
    }

    /*
    // 1. Создаем указатели на левое и правое выражение
    Expression * nleft = (binop->left())->transform(this);
    Expression * nright = (binop->right())->transform(this);
    int noperation = binop->operation();

    // 2. Создаем новый объект типа BinaryOperation с новыми указателями
    BinaryOperation * nbinop = new BinaryOperation(nleft, 
						   noperation,
						   // binop->operation(),
						   nright);
    // 3. Проверяем на приводимость указателей к типу Number
    Number * nleft_is_number = dynamic_cast<Number *>(nleft);
    Number * nright_is_number = dynamic_cast<Number *>(nright);
    if (nleft_is_number && nright_is_number){
      // 3.1 Вычисляем значение выражения
      Expression * result = new Number(nbinop->evaluate());

      // 3.2 Освобождаем память
      delete nbinop;
      // 3.3 Возвращаем результат
      return result;
    }
    else {
      return nbinop;
    }
    */
  }

  Expression *transformFunctionCall(FunctionCall const *fcall)
  {
    // 1. Создаем указатель на аргумент
    Expression * narg = (fcall->arg())->transform(this);
    std::string const & nname = fcall->name();

    // 2. Создаем новый объект типа FunctionCall с новым указателем
    FunctionCall * nfcall = new FunctionCall(nname,
					     //fcall->name(), 
					     narg);

    // 3. Проверяем на приводимость указателя к типу Number
    Number * narg_is_number = dynamic_cast<Number *>(narg);
    if (narg_is_number){
      // 3.1 Вычисляем значение выражения
      Expression * result = new Number(fcall->evaluate());

      // 3.2 Освобождаем память
      delete nfcall;
      // 3.3 Возвращаем результат
      return result;
    }
    else {
      return nfcall;
    }

    /*
    // 1. Создаем указатель на аргумент
    Expression * narg = (fcall->arg())->transform(this);
    std::string const & nname = fcall->name();

    // 2. Создаем новый объект типа FunctionCall с новым указателем
    FunctionCall * nfcall = new FunctionCall(nname,
					     //fcall->name(), 
					     narg);

    // 3. Проверяем на приводимость указателя к типу Number
    Number * narg_is_number = dynamic_cast<Number *>(narg);
    if (narg_is_number){
      // 3.1 Вычисляем значение выражения
      Expression * result = new Number(narg->evaluate());

      // 3.2 Освобождаем память
      delete nfcall;
      // 3.3 Возвращаем результат
      return result;
    }
    else {
      return nfcall;
    }
    */
    
  }

  Expression *transformVariable(Variable const *var)
  {  
    Expression *exp = new Variable(var->name());
    return exp;
  }

  ~FoldConstants() { };

};

// added by vrs
int main() {
  /*
  struct Number *x = new Number(10);
  struct Number *y = new Number(6);

  Expression *expression1 = new BinaryOperation(x,BinaryOperation::PLUS,y);
  Transformer *transformer1 = new FoldConstants();
  Expression *new_expression1 = expression1->transform(transformer1);

  cout<<"binary operation 1: "<<new_expression1->evaluate()<<endl;

  Expression *expression2 = new FunctionCall("sqrt", new_expression1);
  Transformer *transformer2 = new FoldConstants();
  Expression *new_expression2 = expression2->transform(transformer1);

  cout<<"function call 1: "<<new_expression2->evaluate()<<endl;

  Expression *expression3 = new FunctionCall("sqrt", new_expression2);
  Transformer *transformer3 = new FoldConstants();
  Expression *new_expression3 = expression3->transform(transformer1);

  cout<<"function call 2: "<<new_expression3->evaluate()<<endl;

  Expression *expression4 = new BinaryOperation(new_expression3,BinaryOperation::DIV,y);
  Transformer *transformer4 = new FoldConstants();
  Expression *new_expression4 = expression4->transform(transformer1);

  cout<<"binary operation 2: "<<new_expression4->evaluate()<<endl;
  //system("pause");
  struct Number *x = new Number(10);
  struct Number *y = new Number(6);

  Expression *expression1 = new BinaryOperation(x,BinaryOperation::PLUS,y);
  Transformer *transformer1 = new FoldConstants();
  Expression *new_expression1 = expression1->transform(transformer1);

  cout<<"binary operation 1: "<<new_expression1->evaluate()<<endl;

  Expression *expression2 = new FunctionCall("sqrt", new_expression1);
  Transformer *transformer2 = new FoldConstants();
  Expression *new_expression2 = expression2->transform(transformer1);

  cout<<"function call 1: "<<new_expression2->evaluate()<<endl;

  Expression *expression3 = new FunctionCall("sqrt", new_expression2);
  Transformer *transformer3 = new FoldConstants();
  Expression *new_expression3 = expression3->transform(transformer1);

  cout<<"function call 2: "<<new_expression3->evaluate()<<endl;

  Expression *expression4 = new BinaryOperation(new_expression3,BinaryOperation::DIV,y);
  Transformer *transformer4 = new FoldConstants();
  Expression *new_expression4 = expression4->transform(transformer1);

  cout<<"binary operation 2: "<<new_expression4->evaluate()<<endl;
  //system("pause");
  */
  return 0;
}
