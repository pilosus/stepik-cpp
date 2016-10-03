#include <iostream> 
using namespace std;
#include <algorithm>
#include <cstddef>

template <typename T>
class Array
{
public:
  // Список операций:
  //
  // Array(size_t size, const T& value = T())
  //   конструктор класса, который создает
  //   Array размера size, заполненный значениями
  //   value типа T. Считайте что у типа T есть
  //   конструктор, который можно вызвать без
  //   без параметров, либо он ему не нужен.

  // http://www.parashift.com/c++-faq/placement-new.html
  // http://www.informit.com/guides/content.aspx?g=cplusplus&seqNum=304
  // https://stackoverflow.com/questions/15254/can-placement-new-for-arrays-be-used-in-a-portable-way%EF%BB%BF

  Array(size_t size, const T& value = T()) {
    size_ = size;
    data_ = (T*) new char[size_*sizeof(T)];
    for (size_t i = 0; i != size_; ++i) {
      new (data_ + i) T(value);
    }
  }
  //
  // Array()
  //   конструктор класса, который можно вызвать
  //   без параметров. Должен создавать пустой
  //   Array.

  Array() {
    size_ = 0;
    data_ = (T*) new char[size_*sizeof(T)];
    //data_ = 0;
  }


  //
  // Array(const Array &)
  //   конструктор копирования, который создает
  //   копию параметра. Для типа T оператор
  //   присвивания не определен.
  //

  Array(const Array & a) {
    size_ = a.size();
    data_ = (T*) new char[a.size()*sizeof(T)];

    for (size_t i = 0; i != size_; ++i) {
      //data_[i] = a.data_[i];
      //new (a.data_ + i) T();
      //new (a.data_ + i) T(a.data_[i]);
      new (data_ + i) T(a.data_[i]);
    }
  }

  // ~Array()
  //   деструктор, если он вам необходим.

  ~Array() {
    // проверить!
    for (size_t i = 0; i < size_; ++i) {
      data_[i].~T();
    }
    delete [] (char*) data_;
  }

  //
  // Array& operator=(...)
  //   оператор присваивания.
  //

  Array & operator=(Array const& a) { 
    if (this != &a) {
      for (size_t i = 0; i < size_; ++i) {
	data_[i].~T();
      }
      delete [] (char*) data_;

      size_ = a.size();
      data_ = (T*) new char[a.size()*sizeof(T)];

      for (size_t i = 0; i != size_; ++i) {
	new (data_ + i) T(a.data_[i]);
      }
    }
    return *this;
  }

  // size_t size() const
  //   возвращает размер массива (количество
  //                              элемнтов).
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

int main () {
  int a = 666;
  int & b = a;
  int d = 777;
  int &e = d;
  //Array <int> a1(10, 6);
  Array <int> a1(6, b);
  Array <int> a2 = a1; // конструктор копирования
  Array <int> a3(7, e);
  cout << "Size a1: " << a1.size() << endl;
  cout << "Size a2: " << a2.size() << endl;
  cout << "Size a3: " << a3.size() << endl;
  cout << "a1[0]: " << a1[0] << endl;
  cout << "a2[0]: " << a2[0] << endl;
  cout << "a3[0]: " << a3[0] << endl;
  a1 = a3; // оператор присваивания
  cout << "a1 = a3 => a1.size(): " << a1.size() << endl;
  cout << "a1 = a3 => a1[0]: " << a1[0] << endl;

  return 0;
}
