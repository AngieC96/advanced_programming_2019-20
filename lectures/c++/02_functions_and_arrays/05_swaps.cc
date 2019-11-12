#include <iostream>
#include <utility>  //std::swap

void buggy_swap(int a, int b); //already seen
void c_swap(int* a, int* b); //c style
void cxx_swap(int& a, int& b); //c++ style

template <typename T> //template function to swap two objects in c++ style
void templ_swap(T& a, T& b);

int main() {
  int a = 3;
  int b = {7};
  buggy_swap(a, b);
  std::cout << "buggy:\texpected 7 3 --> " << a << " " << b << "\n";

  a = 3;
  b = 7;
  c_swap(&a, &b); // & gives the address of a variable
  std::cout << "    c:\texpected 7 3 --> " << a << " " << b << "\n";

  a = 3;
  b = 7;
  cxx_swap(a, b);
  std::cout << "  cxx:\texpected 7 3 --> " << a << " " << b << "\n";

  a = 3;
  b = 7;
  templ_swap(a, b);
  std::cout << "templ:\texpected 7 3 --> " << a << " " << b << "\n";

  a = 3;
  b = 7;
  std::swap(a, b);
  std::cout << "  stl:\texpected 7 3 --> " << a << " " << b << "\n";
}

void buggy_swap(int a, int b) {
  int tmp{b};
  b = a;
  a = tmp;
}

// a pointer (a) points to the address of a house, while when we dereference it (*a) we access to the content of the house
void c_swap(int* a, int* b) {
  int tmp{*b}; //tmp is an integer
  *b = *a;
  *a = tmp;
}

//In c++ there is a new type: int& -> a pointer that automatically dereferences itself
void cxx_swap(int& a, int& b) {
  int tmp{b};
  b = a;
  a = tmp;
}

template <typename T>
void templ_swap(T& a, T& b) {
  T tmp{b};
  b = a;
  a = tmp;
}

//WE CAN DO BETTER! move syntax
