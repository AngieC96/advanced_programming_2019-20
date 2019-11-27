#include <iostream>

struct Base {
  Base() { std::cout << "Base\n"; }
  //~Base() { std::cout << "~Base\n"; }
  virtual ~Base() { std::cout << "~Base\n"; } // if you know that a class is inherited, put the destructor virtual! So also the derived class destructor will be called
};  // Before virtual, size = 1. Now size = 8

struct Derived : public Base {
  Derived() { std::cout << "Derived\n"; }
  ~Derived() { std::cout << "~Derived\n"; }
};  // Before virtual, size = 1. Now size = 8

int main() {
  { Derived d; }  // I construct and destruct d -> we construct from top to bottom and we destroy from bottom to top

  std::cout << "\n\npointers\n";
  Base* p = new Derived;
  delete p;  // I invoke the destructor ~Base because p is a Base pointer

  return 0;
}

// template<typename T>   wrapper to measure the complexity of an algrithm
// struct measure {
//     T value;
//     measure(){++ default.ctor;} // counter for the default ctor
//     frined
//      bool operator==(const T& a, const T& b) {
//         ++eq_counter;
//           return a.value==b.value;
// }
// }

// sort<double>
// sort<measure<double>>  // it's slower but not so much because the size of measure<double> is equal to double!

// semiregular -> type for which copy ctor, move ctor, etc has been defined
// regular -> equaltity comparison has been defined
// totally ordered -> the less or equal than, greater or equal than, etc has been defined