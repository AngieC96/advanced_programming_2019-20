#include <iostream>

template <typename T>
struct Base {
  void foo() const { std::cout << "base foo" << std::endl; }
};

template <typename T>
struct Derived : public Base<T> {
  // void bar() const { foo(); } // This code doesn't compile -> the compiler 
  void bar() const { this->foo(); }  // this is a pointer to myself
  // If you want to access to the parent function, use this->!!!!
  // If the base class is templated and you cannot access a memeber that you now it's yours, use this-> !!!!
};

int main() {
  Derived<int> d;
  d.bar();
}
