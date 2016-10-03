#include <iostream>
#include <string>
using namespace std;
 
class Number; // Foo
class BinaryOperation; // Bar
class FunctionCall; // Baz
class Variable
 
class Transformer{ // class Visitor
public:
  virtual void visit(Number&ref) = 0;
  virtual void visit(BinaryOperation&ref) = 0;
  virtual void visit(FunctionCall&ref) = 0;
  virtual void visit(Variable&ref) = 0;
};
 

class Expression{ // class Element
public:
  virtual void transform(Transformer&v) = 0; // accept
};
 
//class Foo:public Element{
class Number:public Expression {
public:
  //  void accept(Visitor&v){v.visit(*this);}
  void transform(Transformer&v){v.visit(*this);}
};
 
//class Bar:public Element{
class BinaryOperation:public Expression{
public:
  //  void accept(Visitor&v){v.visit(*this);}
  void accept(Transformer&v){v.visit(*this);}
};
 
//class Baz:public Element{
class FunctionCall:public Expressiont{
public:
  //  void accept(Visitor&v){v.visit(*this);}
  void accept(Transformer&v){v.visit(*this);}
};
 
//class GetType:public Visitor{
class GetType:public Transformer{
public:
  string value;
public:
  void visit(Foo &){value="Foo";}
  void visit(Bar &){value="Bar";}
  void visit(Baz &){value="Baz";}
};
 
int main()
{
  Number foo; //Foo foo;
  BinaryOperation bar; //Bar bar;
  FunctionCall baz; //Baz baz;
  // An array of elements
  Element *elements[] = {&foo,&bar,&baz,0};
 
  // Iterate over elements and get their type
  for(Element **it = &elements[0]; *it; ++it)
    {
      GetType visitor;
      //      (*it)->accept(visitor);
      (*it)->transform(visitor);
      cout << visitor.value << endl;
    }
  return 0;
}

