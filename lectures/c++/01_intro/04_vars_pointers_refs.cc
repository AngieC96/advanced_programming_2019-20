#include <iostream>

int main() {
  // two types of variables 
  double d = 9.9;
  double &ref = d;  // from now on ref is an alias to d, saying d or ref is the same -> it's a nickname
  double *ptr = &d; // ptr contains the address of the variable d
  std::cout << "value of   d: " << d << std::endl;
  std::cout << "value of ref: " << ref << std::endl;
  std::cout << "value of ptr: " << ptr << std::endl << std::endl;  // contains a valuse in base 16 (a=10, b=11, ...)

  std::cout << "address of   d: " << &d << std::endl;
  std::cout << "address of ref: " << &ref << std::endl;
  std::cout << "address of ptr: " << &ptr << std::endl << std::endl;

  // the value of variable d can be changed through either ref or
  // ptr as follows
  ref = 7.7;
  std::cout << "value of   d: " << d << std::endl;

  *ptr = 5.5;  // DEFERENTATION: we are deferentiating the pointer: it conduces us to the value contained in the addess they store
  std::cout << "value of   d: " << d << std::endl;
}
