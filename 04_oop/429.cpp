#include <iostream>
using namespace std;

void promotion(char &) { std::cout << "char" << std::endl; }
void promotion(int &) { std::cout << "int" << std::endl; }
void promotion(long &) { std::cout << "long" << std::endl; }

int main() {
  short sh = 10;
  promotion(sh);

  return 0;
}
