#include <iostream>
#include <memory>  // std::uniqe_ptr

#include "ap_error.h"

// two types of smart pointers: unique pointers or shared pointers
// shared pointers have to know how many peopole share it 

class Vector {
  std::unique_ptr<double[]> elem;  // if someone throws an exception, unique pointers take care of that

 public:
  Vector(const unsigned int l) : elem{new double[l]} {
    std::cout << "Vector ctor\n";
  }
  double& operator[](const unsigned int i) noexcept {  // if you are sure that a function doesn't throws an exception -> the code will be faster!
    return elem[i];
  }  // you can use smart pointers almost like raw pointers
  ~Vector() noexcept { std::cout << "~Vector\n"; }
};

class ManyResources {
  std::unique_ptr<double[]> ptr;
  Vector v;

 public:
  ManyResources() : ptr{new double[5]}, v{3} {
    std::cout << "ManyResources ctor\n";
    AP_ERROR(false) << "I am simulating something wrong.\n";
  }
  ~ManyResources() noexcept { std::cout << "~ManyResources\n"; }
};

int main() {
  try {
    std::unique_ptr<int[]> up{new int[7]};
    ManyResources mr;

  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return 1;

  } catch (...) {
    std::cerr << "Unknown exception. Aborting.\n" << std::endl;
    return 2;
  }

  return 0;
}
// the main should be entirely put in a try-catch!