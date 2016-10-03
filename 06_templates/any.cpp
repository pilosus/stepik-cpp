#include <iostream>
using namespace std;

#include <algorithm>
#include <cstddef>
#include <typeinfo>


struct ICloneable
{
  virtual ICloneable* clone() const = 0;
  virtual ~ICloneable() { }
};


/*
// Эти классы реализовывать заново не нужно
struct ICloneable;

// Поле data_ типа T в классе ValueHolder
// открыто, к нему можно обращаться
template <typename T>
struct ValueHolder;
*/

template <typename T>
struct ValueHolder : ICloneable
{
  // конструктор от одного параметра типа Т
  ValueHolder(const T&  value)
      : data_(value) { }

  // реализация интерфейса
  ValueHolder * clone() const
  {
    return new ValueHolder(data_);
  }

public:
  T data_;
};


// Задачку можно решить, если вспомнить про полиморфизм и интерфейсный
// класс ICloneable.

// Это достаточно простой пример полезной идиомы type erasure

// ValueHolder<T> *vh = dynamic_cast<ValueHolder<T> *>(ptr_);

// boost::any !!! 
// http://www.boost.org/doc/libs/1_56_0/doc/html/any.html

// Это класс, который вам нужно реализовать
class Any
{
public:
  // В классе Any должен быть конструктор,
  // который можно вызвать без параметров,
  // чтобы работал следующий код:
  //    Any empty; // empty ничего не хранит
  Any() : content(0) { }

  // В классе Any должен быть шаблонный
  // конструктор от одного параметра, чтобы
  // можно было создавать объекты типа Any,
  // например, следующим образом:
  //    Any i(10); // i хранит значение 10
  template <typename T>
  Any(const T &value) 
    : content(new ValueHolder<T>(value))
  { }

  // Не забудьте про деструктор. Все выделенные
  // ресурсы нужно освободить.
  ~Any() { delete content; }

  // В классе Any также должен быть конструктор
  // копирования (вам поможет метод clone
  // интерфейса ICloneable)
  Any(const Any & other) 
    : content(other.content ? other.content->clone() : 0)
  { }

  // В классе должен быть оператор присваивания и/или
  // шаблонный оператор присваивания, чтобы работал
  // следующий код:
  //    Any copy(i); // copy хранит 10, как и i
  //    empty = copy; // empty хранит 10, как и copy
  //    empty = 0; // а теперь empty хранит 0

  Any &swap(Any &rhs) 
  { 
    std::swap(content, rhs.content);
    return *this;
  }

  Any &operator=(const Any &rhs) { 
    if (this != &rhs) {
      return Any(rhs).swap(*this);
    }
    return (*this);
  } 

  template <typename T>
  Any &operator=(const T &rhs) {
    Any tmp = Any(rhs); 
    Any * ptr = & tmp;
    if (this != ptr) {
      return Any(rhs).swap(*this);
    }
    return (*this);
  }

  // Ну и наконец, мы хотим уметь получать хранимое
  // значение, для этого определите в классе Any
  // шаблонный метод cast, который возвращает
  // указатель на хранимое значение, или нулевой
  // указатель в случае несоответствия типов или
  // если объект Any ничего не хранит:
  //    int *iptr = i.cast<int>(); // *iptr == 10
  //    char *cptr = i.cast<char>(); // cptr == 0,
  //        // потому что i хранит int, а не char
  //    Any empty2;
  //    int *p = empty2.cast<int>(); // p == 0
  // При реализации используйте dynamic_cast,
  // который мы уже обсуждали ранее.
  
  template<typename T>
  T * cast() const {
    ValueHolder<T> *vh = dynamic_cast<ValueHolder<T> *>(content);
    if (!this->content) {
      return 0;
    }
    if (vh != 0) {
      return &(vh->data_);
    }
    else {
      return 0;
    }
  }


public:
  ICloneable * content;
};

//
int main() {
  /*
  Any empty;
  Any i(10);
  cout << "[1] i=" << i.cast<int>() << endl;
  // i=0x25c6010

  Any copy(i);
  cout << "[2] copy=" << copy.cast<int>() << endl;
  // copy=0x25c6030

  empty = copy;
  cout << "[3] empty=" << empty.cast<int>() << endl;
  // empty=0x25c6050

  empty = 0;
  cout << "[4] empty=" << empty.cast<int>() << endl;
  // empty=0

  int *iptr = i.cast<int>();
  cout << "[5] *iptr=" << iptr << endl;
  // *iptr=0x25c6010

  char *cptr = i.cast<char>();
  cout << "[6] *cptr=" << cptr << endl;
  // *cptr=

  Any empty2;
  int *p = empty2.cast<int>();
  cout << "[7] *p=" << p << endl;
  // *p=0x25c6090

  Any a = 20;
  cout << "[8] a=" << a.cast<int>() << endl;
  // a=0x25c60b0

  a=0;
  cout << "[9] a=" << a.cast<int>() << endl;
  // empty = 0

  a='w';
  cout << "[10] a=" << a.cast<char>() << endl;
  // 
  */
  Any empty;
  Any i(10);
  cout << "[1] i      = " << i.cast<int>() << endl;
  // [1] i      = 0x8e9e00c

  Any copy(i);
  cout << "[2] copy   = " << copy.cast<int>() << endl;
  // [2] copy   = 0x8e9e01c

  empty = copy;
  cout << "[3] empty  = " << empty.cast<int>() << endl;
  // [3] empty  = 0x8e9e02c

  cout << "[3] *empty = " << *empty.cast<int>() << endl;
  // [3] *empty = 10

  empty = 0;
  cout << "[4] empty  = " << empty.cast<int>() << endl;
  // [4] empty  = 0x8e9e02c

  cout << "[4] *empty = " << *empty.cast<int>() << endl;
  // [4] *empty = 0

  int *iptr = i.cast<int>();
  cout << "[5] iptr   = " << iptr << endl;
  // [5] iptr   = 0x8e9e00c
  
  char *cptr = i.cast<char>(); // cptr = 0
  // cout << "[6] cptr=" << cptr << endl; // undefined behavior for char * == 0
  cout << "[6] cptr   = " << (void*)cptr << endl;
  // [6] cptr   = 0

  Any empty2;
  int *p = empty2.cast<int>();
  cout << "[7] p      = " << p << endl;
  // [7] p      = 0

  Any a = 20;
  cout << "[8] a      = " << a.cast<int>() << endl;
  // [8] a      = 0x8e9e03c
  
  a=0;
  cout << "[9] a      = " << a.cast<int>() << endl;
  // [9] a      = 0x8e9e03c

  a = 'w';
  cout << "[10] a     = " << a.cast<char>() << endl; // overloaded operator << for char *
  // [10] a     = w

  cout << "[10] a     = " << (void *)a.cast<char>() << endl; 
  // [10] a     = 0x8e9e03c


  return 0;
}
