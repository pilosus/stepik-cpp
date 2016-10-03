#include <cstddef>
#include <iostream>
/**
template <typename T>
class Array
{
public:
  explicit Array(size_t size = 0, const T& value = T());
  Array(const Array& other);
  ~Array();
  Array& operator=(Array other);
  void swap(Array &other);
  size_t size() const;
  T& operator[](size_t idx);
  const T& operator[](size_t idx) const;

private:
  size_t size_;
  T *data_;
};
*/

/////////////////////////////////////////
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


// Весь вывод должен осущствляться в поток out,
// переданный в качестве параметра.
//
// Можно заводить любые вспомогаетльные функции,
// структуры или даже изменять сигнатуру flatten,
// но при этом все примеры вызова из задания должны
// компилироваться и работать.

// нужна одна перегрузка + рекурсия

template <typename T>
void flatten(const Array<T>& array, std::ostream& out)
{ 
  for (size_t i = 0; i != array.size(); ++i) {
    out << array[i] << " ";
  }
}

template <typename T>
void flatten(const Array< Array <T> >& array, std::ostream& out)
{ 
  for (size_t i = 0; i != array.size(); ++i) {
    flatten(array[i], out);
  }
}


int main() {
  Array<int> ints(2, 0);
  ints[0] = 10;
  ints[1] = 20;
  //flatten(ints, std::cout); 
  // выводит на экран строку "10 20"

  Array< Array<int> > array_of_ints(2, ints);
  flatten(array_of_ints, std::cout); 
  // выводит на экран строку "10 20 10 20"

  Array<double> doubles(10, 0.0);
  //flatten(doubles, std::cout);
  // работать должно не только для типа int

  return 0;
}
