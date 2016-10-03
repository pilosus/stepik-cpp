#include <iostream>
using namespace std;

int my_strstr(const char *str, const char *pattern) {
  // put your code here
  int pos = 0; // position

  if (*str =='\n' || *pattern == '\0')
    return -1;

  for ( ; *str != '\0'; ++str, ++pos) {
    const char *p = str;
    const char *q = pattern; 
    for ( ;*p && (*p == *q) ; ++p, ++q) {
      ; // matching in progress
    }
    if (*q == '\0') {
      // if the inner loop ended with complete match, then the last
      // char of the pattern string should be a null char
      return pos;
    }
    // match not found
  }
  return -1;
}



int main()
{
  /*char str1[] = "";
  cin >> str1;
  char str2[] = "";
  cin >> str2; */
  
  char str1[] = "Hello, world!";
  char pattern1[] = "ello";

  cout << my_strstr(str1, pattern1) << endl;

  return 0;
}
