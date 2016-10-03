#include <iostream>
using namespace std;

#include <cstddef>
#include <cstring>

struct String {
  String(const char *str = "");

  // для аллокации памяти не используйте malloc
  // иначе ваша программа может не пройти
  // тестирование

  // заполните строку n повторениями символа c,
  // например, для n == 3 и c == 'a', в строке
  // должно быть "aaa" (и не забудьте про
  // завершающий нулевой символ)
  // n == 0 допустимое значение
  String(size_t n, char c) {
    // put your code here
    this->str_ = new char[(n + 1) * sizeof(char)];
    for (size_t i = 0; i != n; ++i){
      str_[i] = c;
    }
    str_[n] = '\0';
  }

  // не изменяйте эти имена, иначе ваша программа
  // не пройдет тестирование
  size_t size_;
  char *str_;
};

int main() {
  String s(3, 't');
  //cout << s << endl;
}

