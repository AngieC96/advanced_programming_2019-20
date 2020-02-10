#include <iostream>

struct foo {
  void f(int x) { std::cout << "int " << x << std::endl; }
};

struct bar : public foo {
  using foo::f;  // brings all foo::f to this scope -> I'm 'importing' it!
  void f(char x) { std::cout << "char " << x << std::endl; }  // it's OVERLOADING!!!
};

int main() {
  bar b;
  b.f(33);
  //b.f(int{33}); //to be more explicit
  // if you comment 'using foo::f;' it calls the "char" function! Why? Because function overloading is not resolved on class hierarchy
  // if you decomment 'using foo::f;'  the "int" function is called!
  b.f('3'); // calls the "char" function
}
