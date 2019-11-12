#include <iostream>

struct X {  //It's a built-it type, so it is not initialized so you have garbage in it
  char member;
};

int main() {
  X x1;                 // default ctor
  X x2{x1};             // copy ctor -> you are constructed the object with this value
  X x3{std::move(x2)};  // move ctor
  X x4{};               // default ctor calling {} to each member
  x4 = x3;              // copy assignment -> you construct it and then you copy the value on it
  X x5;                 // default ctor
  x5 = std::move(x4);   // move assignment
  std::cout << x5.member << std::endl;  // what do you expect??
  return 0;
}

//If you dont' write anything, the compiler will create a bunch of functions for you: default ctor, copy ctor, move ctor. If you define the copy ctor the compiler won't create neither his copyctor neither the move ctor, and if you define only the move ctor the compiler won't create his copy ctor, nor the copy/move assignments
