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
    Expression * nleft = (binop->left())->transform(this);
    Expression * nright = (binop->right())->transform(this);
    int noperation = binop->operation();

    BinaryOperation * nbinop = new BinaryOperation(nleft, 
						   noperation,
						   nright);
    Number * nleft_is_number = dynamic_cast<Number *>(nleft);
    Number * nright_is_number = dynamic_cast<Number *>(nright);
    if (nleft_is_number && nright_is_number){
      Expression * result = new Number(nbinop->evaluate());

      delete nbinop;
      return result;
    }
    else {
      return nbinop;
    }
  }

  Expression *transformFunctionCall(FunctionCall const *fcall)
  {
    Expression * narg = (fcall->arg())->transform(this);
    std::string const & nname = fcall->name();

    FunctionCall * nfcall = new FunctionCall(nname, narg);

    Number * narg_is_number = dynamic_cast<Number *>(narg);
    if (narg_is_number){
      Expression * result = new Number(narg->evaluate());
      delete nfcall;
      return result;
    }
    else {
      return nfcall;
    }
    
  }

  Expression *transformVariable(Variable const *var)
  {  
    Expression *exp = new Variable(var->name());
    return exp;
  }

  ~FoldConstants() { };
};
