#include <iostream>

struct X {
  int a = 5;  // in-class initialization -> I can assign a default value to some members
  double b;
  char c = 'a';
  X() = default;  // in-class initializers are used by the constructors
  // to explicitly ask the compiler to create a default constructor
};

struct Y {
  int a = 77;
  double b;
  char c = 'a';
  Y() : a{5} {}  // what it is written here wins the in-class initialization
  //Y() : a{5} {a=7;}  // when we write a=7 we are calling the copy constructor because a has already been initialized
  Y(const Y&) = delete; // You cannot copy this objects!
  // used to eliminate a particular function
};

int main() {
  X x1;    // compiler-generated default ctor
  X x2{};  // compiler-generated default ctor calls {} on uninitialized vars -> it calls all the costructors of the members -> y2.b=0!
  std::cout << x1.a << "--" << x1.b << "--" << x1.c << "\n";
  std::cout << x2.a << "--" << x2.b << "--" << x2.c << "\n\n";

  Y y1;    // default ctor
  Y y2{};  // default ctor -> since I defined the default ctor in this way, it doesn't call the default ctor of each member
  std::cout << y1.a << "--" << y1.b << "--" << y1.c << "\n";
  std::cout << y2.a << "--" << y2.b << "--" << y2.c << "\n";

  // Y y3{y2}; // error: call to a deleted function

  return 0;
}
