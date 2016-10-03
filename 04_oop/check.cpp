#include "funcall.cpp"

/*
Я понял, что таблицы виртуальных функций отличаются у классов.
А где смотреть, как к этому обратиться?

а, методы же известны=)

http://kaisar-haque.blogspot.co.at/2008/07/c-accessing-virtual-table.html
 */

bool check_equals(Expression const *left, Expression const *right)
{
  // put your code here
  // https://stackoverflow.com/questions/3068144/print-address-of-virtual-member-function

  size_t * vptr1 = *(size_t **)&left;
  size_t * vtable1 = (size_t *)*vptr1;

  size_t * vptr2 = *(size_t **)&right;
  size_t * vtable2 = (size_t *)*vptr2;

  return (vtable1 == vtable2);
}

int main() {
  
  return 0;
}
