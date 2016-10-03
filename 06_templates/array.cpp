#include <algorithm>
#include <iostream>
#include <cstddef>

template <typename T>
class Array
//struct Array // иначе будет ошибка о приватности методов
{
  // убрать public, если используется struct вместо class
public:
  // Список операций:
  //
  // explicit Array(size_t size = 0, const T& value = T())
  //   конструктор класса, который создает
  //   Array размера size, заполненный значениями
  //   value типа T. Считайте что у типа T есть
  //   конструктор, который можно вызвать без
  //   без параметров, либо он ему не нужен.
  explicit Array(size_t size = 0, const T& value = T()) {
    size_ = size;
    data_ = new T[size];
    for (size_t i = 0; i != size_; ++i) {
      data_[i] = value;
    }
  }
  //
  // Array(const Array &)
  //   конструктор копирования, который создает
  //   копию параметра. Считайте, что для типа
  //   T определен оператор присваивания.

  Array(const Array & a): 
    size_(a.size()), data_(new T[a.size()]) {
    for (size_t i = 0; i != size_; ++i) {
      data_[i] = a.data_[i];
    }
  }

  //
  // ~Array()
  //   деструктор, если он вам необходим.

  ~Array() {
    delete [] data_;
  }

  //
  // Array& operator=(...)
  //   оператор присваивания.
  //

  // Вспомогаетльная функция
  void swap(Array & a) { 
    std::swap(size_, a.size_); std::swap(data_, a.data_);
  }

  Array & operator=(Array const& a) { 
    if (this != &a)
      Array(a).swap(*this); 
    return *this;
  }

  // size_t size() const
  //   возвращает размер массива (количество
  //                              элементов).
  //

  size_t size() const { 
    return size_; 
  }

  // T& operator[](size_t)
  // const T& operator[](size_t) const
  //   две версии оператора доступа по индексу.
  T& operator[](size_t i) {
    return data_[i];
  }

  const T& operator[](size_t i) const {
    return data_[i];
  }

private:
  size_t size_;
  T * data_;
};

//
int main() {
  int A = 5;
  int & ra = A;
  int b = 0;
  b = ra;
  std::cout << b << std::endl;

  return 0;
}
