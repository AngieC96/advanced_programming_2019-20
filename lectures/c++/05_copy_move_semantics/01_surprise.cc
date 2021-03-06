#include <iostream>

struct X {  //It's a built-it type, so it is not initialized so you have garbage in it
  char member;
};

int main() {
  X x1;                 // default ctor
  //x1.member = 'a';
  X x2{x1};             // copy ctor -> you are constructed the object with this value
  X x3{std::move(x2)};  // move ctor
  X x4{};               // default ctor calling {} (the default ctor) to each member (each member calls is own default ctor)
  x4 = x3;              // copy assignment -> you construct it and then you copy the value on it
  X x5;                 // default ctor
  x5 = std::move(x4);   // move assignment
  std::cout << x5.member << std::endl;  // what do you expect??
  std::cout << "x1 = " << x1.member << std::endl;
  std::cout << "x2 = " << x2.member << std::endl;
  return 0;
}

//If you dont' write anything, the compiler will create a bunch of functions for you: default ctor, copy ctor, move ctor.
//If you define the copy ctor the compiler won't create neither his copy ctor neither the move ctor, and if you
// define only the move ctor the compiler won't create his copy ctor, nor the copy/move assignments

// The difference between move and copy is that after a copy two objects must have the same value, whereas after
// a move the source of the move is not required to have its original value. Moves can be used when the source
// object will not be used again.