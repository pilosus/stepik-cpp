#include <iostream>
using namespace std;

#include <cstddef> // size_t
// реализуйте шаблонную функцию array_size,
// которая возвращает значение типа size_t.

// put your code here

/**
would work for the real arrays, but will compile for pointer, which
is wrong

template<typename T>
size_t array_size(T & arr) {
  return sizeof(arr) / sizeof(*arr);
}
*/

/**

https://stackoverflow.com/questions/437150/can-someone-explain-this-template-code-that-gives-me-the-size-of-an-array

https://coderwall.com/p/nb9ngq

*/

template<typename T, size_t N>
size_t array_size(T (&arr)[N]) {
  return N;
}


int main() {
  int ints[] = {1, 2, 3, 4};
  int *iptr = ints;
  double doubles[] = {3.14};
  cout << array_size(ints) << endl;  
  // вернет 4

  cout << array_size(doubles) << endl; 
  // вернет 1

  //cout <<  array_size(iptr) << endl;; 
  // тут должна произойти ошибка компиляции
  
  return 0;
}
