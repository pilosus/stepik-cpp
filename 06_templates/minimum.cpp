#include <iostream>
using namespace std;

#include <cstddef>

template <typename T>
class Array
{
public:
  explicit Array(size_t size = 0, const T& value = T());
  Array(const Array& other);
  ~Array();
  Array& operator=(Array other);
  void swap(Array &other);
  size_t size() const;
  T& operator[](size_t idx);
  const T& operator[](size_t idx) const;

private:
  size_t size_;
  T *data_;
};

//
bool less(int a, int b) { return a < b; }
struct Greater { bool operator()(int a, int b) { return b < a; } };


// put your code here
template <typename T, typename Comp>
const T minimum (Array<T>  arr, Comp comparator) {
  T result = arr[0];
  for (size_t i = 0; i != arr.size(); ++i) {
    // comp(b, a)) ? b : a
    if (comparator(arr[i], result)) {
      result = arr[i];
    }
  }
  return result;
}


int main() {
  Array<int> ints(3);
  ints[0] = 10;
  ints[1] = 2;
  ints[2] = 15;
  //int min = minimum(ints, less); // в min должно попасть число 2
  int max1 = minimum(ints, Greater()); // в max должно попасть число 15
  //cout << "Min: " << min << endl;
  cout << "Max: " << max1 << endl;
  return 0;
}
