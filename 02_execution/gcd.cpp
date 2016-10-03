#include <iostream>
using namespace std;

int gcd(int a, int b)
{
  // put your code here
  if (b == 0) { return a; } 
  return gcd(b, a % b);
}

int main() {
  int a = 0;
  int b = 0;

  // Input
  std::cin >> a >> b;

  // Output
  std::cout <<  gcd(a, b) << endl; 

  return 0;
}
