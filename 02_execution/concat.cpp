#include <iostream>
using namespace std;

void my_strcat(char *to, const char *from) {
  // put your code here
  char *p = to; // pointer to to string
  const char *q = from; // points to from string
  
  for ( ; *p != '\0'; ++p) {
    ; // just skipping chars until we find a null char
  }
  // now p points to null chat in to string
  // so let's copy chars from from string to to string
  for ( ; *q != '\0'; ++p, ++q)
    *p = *q;

  // add null char to the end of the string
  *p = '\0';
  // we return nothing, just concatenate two strings, it's a void function
}

int main()
{
  /*char str1[] = "";
  cin >> str1;
  char str2[] = "";
  cin >> str2; */
  
  char str1[100] = "Hello";
  char str2[] = ", World!";

  my_strcat(str1, str2);
  cout << str1 << endl;

  return 0;
}
