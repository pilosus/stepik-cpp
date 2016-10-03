#include <string>
#include <iostream>
using namespace std;

struct Person {
  Person(string const& name, int age)
    : name_(name), age_(age)
  {}
  virtual ~Person() {}
  virtual string name() const {return name_;} 
  virtual string occupation() const = 0;
private:
  string name_;
  int age_;
};

struct Teacher : Person {
  Teacher(string const& nm, int age, string const& course) : 
    Person(nm, age), course_(course)
  { cout << name () << endl; }
  virtual string occupation() const { return "teacher"; }
  virtual string course() const { return course_; }
private:
  string course_;
};

struct Professor : Teacher {
  Professor(string const& name, int age, string const& course, 
	    string const& thesis)
    : Teacher(name, age, course), thesis_(thesis)
  {}
  virtual string thesis() const { return thesis_; }
  string name() const { return "Prof. "+ Person::name(); }
  virtual string occupation() const { return "professor"; }

private:
  string thesis_;
};

int main() {
  Professor p("Stroustrup", 63, "C++", "The C++ language"); // stdout:
							    // Stroustrup
  // то есть метод name в конструкторе повел себя как невиртуальный
  return 0;
}

/**
g++-4.9 -fdump-class-hierarchy virtable.cpp -o virtable

Получим файл с описанием классов, в том числе таблицами виртуальных
методов

Vtable for Person
Person::_ZTV6Person: 6u entries
0     (int (*)(...))0
8     (int (*)(...))(& _ZTI6Person)
16    0u
24    0u
32    (int (*)(...))Person::name
40    (int (*)(...))__cxa_pure_virtual

Class Person
   size=24 align=8
   base size=20 base align=8
Person (0x0x1029b3060) 0
    vptr=((& Person::_ZTV6Person) + 16u)

Vtable for Teacher
Teacher::_ZTV7Teacher: 7u entries
0     (int (*)(...))0
8     (int (*)(...))(& _ZTI7Teacher)
16    (int (*)(...))Teacher::~Teacher
24    (int (*)(...))Teacher::~Teacher
32    (int (*)(...))Person::name
40    (int (*)(...))Teacher::occupation
48    (int (*)(...))Teacher::course

Class Teacher
   size=32 align=8
   base size=32 base align=8
Teacher (0x0x1029b8478) 0
    vptr=((& Teacher::_ZTV7Teacher) + 16u)
  Person (0x0x1029b30c0) 0
      primary-for Teacher (0x0x1029b8478)

Vtable for Professor
Professor::_ZTV9Professor: 8u entries
0     (int (*)(...))0
8     (int (*)(...))(& _ZTI9Professor)
16    (int (*)(...))Professor::~Professor
24    (int (*)(...))Professor::~Professor
32    (int (*)(...))Professor::name
40    (int (*)(...))Professor::occupation
48    (int (*)(...))Teacher::course
56    (int (*)(...))Professor::thesis

Class Professor
   size=40 align=8
   base size=40 base align=8
Professor (0x0x1029b86e8) 0
    vptr=((& Professor::_ZTV9Professor) + 16u)
  Teacher (0x0x1029b8750) 0
      primary-for Professor (0x0x1029b86e8)
    Person (0x0x1029b3120) 0
        primary-for Teacher (0x0x1029b8750)

 */
