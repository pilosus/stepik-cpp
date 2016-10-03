#include <cstddef>  // size_t

#include <iostream>
using namespace std;

int ** transpose(const int * const * m, size_t r, size_t c) {
  // put your code here
  // create matrix to store transpose
  int ** mt = new int * [c];
  mt[0] = new int [r * c];
  for (size_t i = 1; i != c; ++i) {
    mt[i] = mt[i - 1] + r;
  }

  // save m transpose to mt
  for(size_t i = 0; i != r; ++i) {
    for(size_t j = 0; j != c; ++j) {
      mt[j][i] = m[i][j];
    }
  }
  delete [] m; // flush memory
  return mt;
}

void transpose_print(int ** m, size_t r, size_t c) {
  // save m transpose to mt
  for(size_t j = 0; j != c; ++j) {
    for(size_t i = 0; i != r; ++i) {
      cout << m[i][j] << " ";
    }
    cout << endl;
  }
}

void matrix_print(int ** m, size_t r, size_t c) {
  for(size_t i = 0; i != r ; ++i) {
    for(size_t j = 0; j != c; ++j) {
      cout << m[i][j] << " ";
    }
    cout << endl;
  }  
}

int main() {

  int ** m2d = new int * [5];
  for(size_t i = 0; i != 5; ++i) {
    m2d[i] = new int[4];
  }

  cout << "Matrix M:" << endl;
  matrix_print(m2d, 5, 4);

  cout << "Trnaspose matrix MT:" << endl;
  matrix_print(transpose(m2d, 5, 4), 4, 5);

  return 0;
}
