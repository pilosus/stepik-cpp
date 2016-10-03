#include <iostream>
using namespace std;

struct ICloneable
{
  virtual ICloneable* clone() const = 0;
  virtual ~ICloneable() { }
};

// Шаблон ValueHolder с типовым параметром T,
// должен содержать одно открытое поле data_
// типа T.
//
// В шаблоне ValueHolder должен быть определен
// конструктор от одного параметра типа T,
// который инициализирует поле data_.
//
// Шаблон ValueHolder должен реализовывать
// интерфейс ICloneable, и возвращать указатель
// на копию объекта, созданную в куче, из метода
// clone.

template <typename T>
struct ValueHolder : ICloneable
{
  // конструктор от одного параметра типа Т
  // ValueHolder(T&  value)
  ValueHolder(const T&  value) { 
    data_ = (T*) new char[sizeof(T)];
    new (data_) T(value);
  }

  // реализация интерфейса
  ValueHolder * clone() const
  {
    return new ValueHolder(*this);
    //return new ValueHolder(data_);
  }

public:
  T * data_;
};

int main() {
  int a = 10;
  ValueHolder <int> vh(a);
  vh.clone();

  return 0;
}
