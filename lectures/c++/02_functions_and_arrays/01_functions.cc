#include <iostream>

//ret_type founction(){
//	function body
//}

// a function is a named sequence of instruction/statements
unsigned int factorial(unsigned int n) { 
  unsigned int ret{1};
  while (n > 1) {
    ret *= n;
    --n;

    // or simply
    // ret *= n--;
  }
  return ret;
}

//auto factorial(unsigned int n) {} -> in c++14 (-std=c++14)

int main() {
  unsigned int f5{factorial(5)};
  //the compiler decides alone the type of the variable based on the returning type of the function
  auto f6 = factorial(6);  // use = with auto
  std::cout << "factorial of 5 is " << f5 << '\n'
            << "factorial of 6 is " << f6 << std::endl;

  //c++ is STRONGLY CHECKED: at compile time everything is checked
  // errors at compile time
  // factorial(); // too few args
  // factorial(3,4,5,5); // too many args
  // factorial("byobu"); // wrong type
  return 0;
}
