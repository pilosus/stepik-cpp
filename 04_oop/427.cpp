#include <iostream>
using namespace std;

float square(float value) { return value*value; }
double square(float value) { return (double)value*value; }

int main() {
  double sq = square(2.0);

  cout << "sq =  " << sq << endl;

  return 0;
}
