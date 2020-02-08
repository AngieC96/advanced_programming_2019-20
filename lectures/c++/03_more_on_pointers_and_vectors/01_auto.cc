#include <cmath>
#include <iostream>

#if __cplusplus > 201103L  //compiler if. 201103L string of the official c++11

template <class T>
auto init(const std::size_t l) {  //only in c++14!
  return new T[l]{};
}

#else

template <class T>
T* init(const std::size_t l) {
  return new T[l]{};  //T[l]{} i create a vector initilizated to 0
}

#endif

template <class T>  //class is equal to typename
void debug(T); //I'm declaring the function, but not defining it

int main() {  //every executable contains only ONE function named main that returns an interger -> it's the first function that is called!
//auto is a keyword to automatically determinate the type of the variable
//with auto DON'T USE THE {} for the declaration of variables, USE = !
  auto b = true;          // a bool
  auto ch = 'x';          // a char
  auto i = 123;           // an int -> by standard
  auto d = 1.2;           // a double -> by standard
  auto z = std::sqrt(d);  // z has the type of whatever sqrt(d) returns. ':' scope resolution operator. We're using the namespace std
  auto ui = 0u;           // unsigned int
  auto llui = 0llu;       // long long unsigned int

  for (auto i = 0; i < 7; ++i)
    std::cout << i << std::endl;

  auto pb = &b;  // guess what.. How can I know?  //pointer to a boolean

  //debug(pb); //ERROR -> the compiler will speak to me -> safest way to find out the type of a variable
  //Since I don't put the <type> part, the compiler will say to me what to put:  riferimento non definito a "void debug<bool*>(bool*)" -> now I know the type of the variable!

  std::cout << pb << std::endl;
  std::cout << &b << std::endl;
  std::cout << *pb << std::endl;

  auto ps = init<double>(11);
  delete[] ps;
  return 0;
}
