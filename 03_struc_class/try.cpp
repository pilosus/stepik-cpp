#include <iostream>
using namespace std;
#include <cstddef> // size_t
#include <cstring> // strlen, strcpy

int main() {
  int p[5] = {1, 2, 3, 4, 5};
  cout << "Length of the array is: " << sizeof(p) << endl;
  cout << "p[0]: " << p[0] << endl;
  cout << "p[4]: " << p[4] << endl;
  cout << "p[5]: " << p[5] << endl;
}
