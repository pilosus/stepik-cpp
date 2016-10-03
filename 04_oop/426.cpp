#include <iostream>
using namespace std;

void foo(char) { std::cout << "char" << std::endl; }
void foo(signed char) { std::cout << "signed char" << std::endl; }
void foo(unsigned char) { std::cout << "unsigned char" << std::endl; }

int main() {
  cout << "foo('a'): " << endl;
  foo('a');
  
  cout << "foo(97): " << endl;
  foo(97); // ошибка компиляции, потому что 97 может относиться и к
	   // unsigned char (-128..127) и к signed char (0,
	   // 255). Впрочем, foo(255) тоже не сработает из-за
	   // неоднозначности 

  return 0;
}
