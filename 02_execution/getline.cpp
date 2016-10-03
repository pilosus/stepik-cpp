#include <iostream>

using namespace std;

char *getline() {
  // put your code here
  char * m = new char[10000];
  int i = 0;
  char c; // input char
  while((cin.get(c)) && (c != '\n') && (c != '\0')) {
    m[i] = c;
    i++;
  }
  m[i] = '\0';
  return m;
} 


int main() {
  cout << getline() << endl;
  
  return 0;
}
