#include <iostream>

void swap(int a, int b);

int main() {
  int x{3}, y{7};
  std::cout << "before\t" << x << " " << y << std::endl;
  swap(x, y);
  std::cout << "after\t" << x << " " << y << std::endl;
  return 0; //I can pass ONLY ONE VALUE!!!!
}

//In c++ variables are passed by VALUE! (everything is)
//In the stack a variable is deleted if it goes out of scope (= the space inside the curly braces)
//In the heap a variable exists until the programmer says to delete it
void swap(int a, int b) {
  std::cout << "before\t" << a << " " << b << std::endl;
  int t{a};
  a = b;
  b = t;
  std::cout << "after\t" << a << " " << b << std::endl;
}
