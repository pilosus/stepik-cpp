#include <iostream>

using namespace std;

// Чтобы поменять строки, надо просто поменять указатели на них
// INT_MAX не определен T_T



void swap_min(int **mt, int m, int n) {
  // put your code here
  int melem = mt[0][0]; // начально минимальное значение это 1-й элемент mt
  int mline = 0; // индекс строки с минимальным элементом
  for (int i = 0; i != m; ++i) {
    for (int j = 0; j != n; ++j) {
      if (mt[i][j] < melem) {
	melem = mt[i][j];
	if (mline != i) { mline = i; }
      }
    }
  }
  int * tempmt = new int[m]; // временная матрица для найденной строки
  if (mline != 0) {
    tempmt = mt[0]; // храним первую строчку во временном массиве
    mt[0] = mt[mline];
    mt[mline] = tempmt;
    delete [] tempmt;
  }
}

int main() {
  
  return 0;
}
