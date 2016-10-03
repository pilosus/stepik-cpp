#include <iostream>
using namespace std;

int main() {
  // put your code here
  string input;
  string output;
  int wspace = 0;
  bool prev_char_ws = true;

  getline(cin, input);
  for (string::size_type i = 0; i < input.size(); ++i) {
    if (input[i] != ' ') {
      output += input[i];
      prev_char_ws = false;
    }
    else if (input[i] == ' ' && !prev_char_ws) {
      output += input[i];
      prev_char_ws = true;
    }
    else if (input[i] == ' ' && prev_char_ws) {
      continue;
    }
  }

  // remove trailing space
  if (output[(output.size()) - 1] == ' ') {
    string temp = "";
    for (int i = 0; i < (output.size() - 1); ++i) {
      temp += output[i];
    }
    output = temp;
    cout << output;
    }
  else {
    cout << output;
  }

  return 0;
}
