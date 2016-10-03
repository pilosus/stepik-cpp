#include <iostream>
using namespace std;

unsigned my_strlen(const char *str) {
  // put your code here
  const char *p = str; // указатель на начало строки
  while (*p != '\0')
    p++;
  return (p - str);
}

int main()
{
  char data[] = "";
  cin >> data;

  cout << my_strlen(data) << endl;  

  return 0;
}
