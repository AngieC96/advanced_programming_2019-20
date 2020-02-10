#include <iostream>

struct Foo {
  static double s;  // must be defined outside the class
  // static int si = 0; // error: must be const
  static const int sc = 9;  // only integral types are allowed
  // static const double sd;  // error: only int are allowed inside the struct!
  int i;
};

//double Foo::s;

// double Foo::s = 0;
 double Foo::s = 9;

// int Foo::i = 2; // error, only static members can be defined out of class

int main() {
  Foo f1;
  Foo f2;
  std::cout << f1.s << '\n' << f2.s << '\n' << Foo::s << std::endl;
  Foo::s = 77.88;
  std::cout << sizeof(f1) << std::endl;
  std::cout << f1.s << '\n' << f2.s << '\n' << Foo::s << std::endl;
  f1.s = 88.99;
  std::cout << f1.s << '\n' << f2.s << '\n' << Foo::s << std::endl;
  //Both f1 and f2 share the variable s
  return 0;
}
