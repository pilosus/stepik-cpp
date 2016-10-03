#include <iostream>
using namespace std;

string reverse(string l) {
  string data = "";
  cin >> data;

  if (data != "0") {
    l = data + " " + l;
    //    cout << data + " ";
    return reverse(l);
  }
  else {
    return l;
  }
}


int main()
{
  // put your code here
  string result = "";
  cout << reverse(result) << endl; 

  return 0;
}
