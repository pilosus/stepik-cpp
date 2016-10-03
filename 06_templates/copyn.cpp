#include <iostream>
using namespace std;

#include <cstddef>

// Параметры функции copy_n идут в следующем
// порядке:
//   1. целевой массив
//   2. массив источник
//   3. количество элементов, которые нужно
//      скопировать
//
// Вам нужно реализовать только функцию copy_n,
// чтобы ее можно было вызвать так, как показано
// в примере.

// put your code here
template <typename Tt, typename Tu, typename size_t>
void copy_n(Tt * T, Tu  * U, size_t n) {
  for (size_t i = 0; i != n; ++i) {
    T[i] = U[i];
  }
}

template <typename T1, typename T2>
void putthere(T1 * arr, size_t idx, T2 elem) {
  arr[idx] = (T1) elem;
}

void put(int * arr, int idx, int elem) {
  arr[idx] = elem;
}

int main() {
  int ints[] = {1, 2, 3, 4};
  double doubles[4] = {};
  double * d = doubles;
  int * i = ints;
  int x = 123;
  cout << "ints[0]: " << ints[0] << endl;
  //copy_n(d, i, 4);
  copy_n(doubles, ints, 4);
  //put(p, 0, x);
  //putthere(d, 0, x);
  cout << "doubles[0]: " << doubles[0] << endl;
   //cout << "doubles[0] = (double) ints[0]: " << doubles[0] << endl;
  return 0;
}
