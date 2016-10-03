#include <iostream>
using namespace std;

int main() {
  int A = 0;
  int B = 0;
  int count = 0;

  // Input
  std::cin >> A >> B;

  int current_year = A;
  while (current_year < B) {
    if ((((current_year % 4) == 0) && ((current_year % 100) != 0)) \
	|| ((current_year % 400) == 0)) { 
      count += 1; 
    }
    current_year += 1;
  }

  // Output
  std::cout << count << endl; 

  return 0;
}
