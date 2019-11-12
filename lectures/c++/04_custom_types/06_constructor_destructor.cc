#include <iostream>
#include <string>

// Why if I use std::vectors I don't see new or delete? In a classe there are special functions: constructors and the destructor
// We can have many constructors but only one destructor, that is called when the variable goes out of scope
struct Foo {
  int _i;
  double _d;
  std::string _s;

  // Only declaration of the constructor
  Foo(const int i, const double d,
      const std::string& s);  // custom constructor: it's a function that doesn't have a return type and is named with the same name of the class (it's case sensitive!)

  Foo();  // default constructor: it's without arguments -> it's needed if you want an array of this object

  ~Foo();  // destructor
};

Foo::Foo(const int i, const double d, const std::string& s) // Fully qualified name
    : _i{i}, // limbo region of the constructor: where variables are not constructed yet
      _d{d},  //_d(d) sometime works and sometimes not
      _s{s} //I can use the universal and uniform initializer {}
// _i, _d, _s must be initialized in the same order they have been declared

{ //body of the constructor: all the members have benn already constructed
  // Two vays of initialize _i: one is the one we are using, one is this:
  // _i{i}; // I cannot use this, because here the variable are already been constructed! So I only have to assign a value to it, then I have to use the following mode:
  // _i = i; // I first construct the element and then I copy the value in it, with the {} I do only one operation!
  std::cout << "custom ctor\n";
  // if you want/need you can use _i, _d, _s and change their value
  // with the usual notation +,-,=,*, call a function..
  // don't use {} because this notation is reserved for the
  // construction of the variables and at this point they have already
  // been constructed
}

Foo::Foo() { //DEFAULT CONSTRUCTOR
  std::cout << "default ctor\n";  // what happens to our member variables?
}

Foo::~Foo() {  // DESTRUCTOR
  std::cout << "dtor\n";
}

// Overloading of the << opertor. OR operator[] OR operator- if I want to overload [] or -
std::ostream& operator<<(std::ostream& os, const Foo& f) { //std::ostream type of cout (it's a global variable) -> it's a class in std of type ostream
  os << f._i << " " << f._d << " " << f._s << std::endl;
  return os; // to chain the operators
}

int main() {
  Foo f0;    // call default ctor
  Foo f1{};  // call default ctor
  // Foo f2(); // compiler error: the compiler thinks that you are defining a function called f2 that doen't take variables and returns a Foo element

  Foo f2{8, 2.2, "hello"}; // I call the constructor
  //Foo f2(8, 2.2, "hello"); //valid but prefer {}
  // This is also fine -> but is better to use curly braces, so it's clear you're initializing the object
  std::cout << "f0: " << f0 << "f1: " << f1 << "f2: " << f2 << std::endl;

  // the destructor is called when the variable goes out of scope: from bottom to top
  return 0;
}
