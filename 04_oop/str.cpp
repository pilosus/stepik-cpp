#include <iostream>
using namespace std;

#include <algorithm> // swap - добавлено на шаге 3.7.10
#include <cstddef> // size_t
#include <cstring> // strlen, strcpy

struct String {
  // для аллокации памяти не используйте malloc
  // иначе ваша программа может не пройти
  // тестирование
  // Step 7
  String(const char *str = "") {
    // put your code here
    this->size_ = std::strlen(str); // without trailing \0
    this->str_ = new char[(this->size_ + 1) * sizeof(char)];
    std::strcpy(str_, str);
  }
  // 3.7.9 Конструктор копирования
  String(const String &str) {
    // put your code here
    size_t nsize = str.size_;
    this->str_ = new char[nsize];
    for (size_t i = 0; i != nsize; ++i) {
      str_[i] = str.str_[i];
    }
  }
  // 3.7.10 Оператор присваивания
  void swap(String &str) {
    std::swap(size_, str.size_);
    std::swap(str_, str.str_);
  }

  String &operator=(const String &str) {
    // put your code here
    if (this != &str) {
      String(str).swap(*this);
    }
    return *this;
  }

  //  Step 8
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

  // Step 12
  ~String() {
    // put your code here
    delete [] str_;
  }
  // Step 13
  size_t size() {
    // put your code here
    return this->size_;
  }

  char &at(size_t idx) {
    // here
    cout << "char & at" << endl;
    return str_[idx];
  }

  // 3.6.14
  char at(const size_t idx) const {
    // here
    cout << "char at const" << endl;
    return str_[idx];
  }


  const char *c_str() {
    // and here
    return &str_[0];
  }

  // Step 14
  int compare(String &str) {
    // and here
    return std::strcmp(this->str_, str.c_str());
  }

  // 3.5 Step 7
  // для выделенеия и освобождения не используйте
  // malloc/free, иначе ваша программа может не
  // пройти тестирование
  void append(String &str) {
    // put your code here
    //size_t orig_size = std::strlen(this->str_);
    size_t orig_size = this->size_; // withouit trailing \0
    size_t arg_size = str.size(); // without trailing \0
    size_t nsize = orig_size + arg_size + 1;
    char * nstr = new char[(nsize) * sizeof(char)];
    std::strncat(nstr, str_, orig_size);
    std::strncat(nstr, str.c_str(), arg_size);
    nstr[nsize] = '\0';
    delete [] str_;
    str_ = new char[(nsize) * sizeof(char)];
    std::strcpy(str_, nstr);
    this->size_ = nsize - 1;
    delete [] nstr;
  }
  // не изменяйте эти имена, иначе ваша программа
  // не пройдет тестирование
  size_t size_;
  char *str_;
};

int main() {
  String s1("Hello, hello, "); // 14 chars
  String s2("my wonderful World!"); // 19 chars
  cout << "String 1: " << s1.c_str() << endl;
  cout << "String 1 size: " << s1.size_ << endl;
  cout << "String 2: " << s2.c_str() << endl;
  cout << "String 2 size: " << s2.size_ << endl;
  s1.append(s2);
  cout << "String 1 with String 2 appended: " << s1.c_str() << endl;
  cout << "Size after concatenation: " << s1.size_ << endl;
  cout << "Last symbol: " << s1.at(s1.size_ - 1) << endl;

  String s3 = s1; // проверка оператора копирования
  cout << "After s3 = s1, string s3: " << s3.c_str() << endl;

  s2 = s1; // проверка оператора присваивания
  cout << "After s2 = s1, string s2: " << s2.c_str() << endl;

  String greet("Hello");
  cout << "char ch1 = greet.at(0): " << endl;
  char ch1 = greet.at(0);

  String const const_greet("Hello, Const!");
  cout << "char const &ch2 = const_greet.at(0): " << endl;
  char const &ch2 = const_greet.at(0);

  cout << "ch1: " << ch1 << endl;
  cout << "ch2: " << ch2 << endl;
}

