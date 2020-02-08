#include <iostream>

template <typename T>
void print_sentinel(const T* a, const std::size_t l);

int main() {
  int a{8}, b{7};
  int* pi{&a}; // &a -> address of a

  const int* pc{&a}; //helps the compiler to optimize things, because if it knows that you will never change it, it performs better
  //-> constant pointer: you cannot change it after deferentiating it -> when I deferentiate it, it becomes a const int so I cannot change it
  // *pc = 7; 	// error
  a = 15;  // I can obviously change a
  pc = &b; // You can change the pointer

  int* const cp{&a}; //I cannot change the address pointed, that is the value of cp
  a = b;
  *cp = 33;
  // cp = &b;   // error -> you cannot re-use this pointer for another address!

  const int* const cpc{&a}; //const pointer to integer const -> pointer that points to a fixed memory location and you cannot change the value of the pointed variable

  // *cpc = 0;  // error
  // cpc = &n;  // error
  a = 99; //this const doesn't put restrictions on the pointed variable a

  int aa[4]{};
  print_sentinel(aa, 4);

  return 0;
}

template <typename T>
void print_sentinel(const T* a, const std::size_t N) {
  const T* const end{a + N}; //it should NOT change! -> I don't want to change it by chance! It points to the begin of the last element
  for (; a != end; ++a) //the initialization is putted before the firsst iteration, the condition is evaluated at the begginning of each operation, while the incrementation is done at the end of each iteration
    std::cout << *a << std::endl;
}
