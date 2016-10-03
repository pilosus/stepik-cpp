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
  ValueHolder(const T&  value)
      : data_(value) { }

  // реализация интерфейса
  ValueHolder * clone() const
  {
    //return new ValueHolder(*this);
    return new ValueHolder(data_);
  }

public:
  T  data_;
};

int main() {
  int a = 10;
  ValueHolder <int> vh(a);
  vh.clone();

  return 0;
}

/*
Пишите конструктор используя список инициализаци

new ValueHolder(*this)

Как правильно указывать тип возвращаемого значения функции в шаблонном
классе?
ValueHolder<T> * clone() const {...}

 */
