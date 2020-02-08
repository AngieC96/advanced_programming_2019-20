#include <iostream>

int main() {
  std::cout << "Please insert array lenght: ";
  std::size_t n;
  std::cin >> n;
  //with c++ compiler you have to know the length of the array at compile-time and NOT at run-time!
  int* da{new int[n]};  // allocated on the HEAP, or free-store, free-memeory
  //new returns a pointer! The address of the house that has been allocated in the heap -> then we store it in the 'da' variable

  for (std::size_t i{0}; i < n; ++i)
    da[i] = i * 10;

  for (std::size_t i{0}; i < n; ++i)
    std::cout << "da[" << i << "] = " << da[i] << std::endl;

  delete[] da; //it is not automatically erased!
  return 0;
}

//ulimit -a
//free -m
//the stack is small (4MB) while the heap is larger (16GB)!
//stack overflow -> segmentation fault --> the program crashes
