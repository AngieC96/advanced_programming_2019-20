#include <array>
#include <iostream>

// template <class T, std::size_t N>  //statics arrays that lives in the stack -> I have to specify the type and the length
// struct array;

int main() {
  std::array<int, 4> a{1, 2, 3, 4};
  std::array<int, 4> b{a};  // I can copy element-wise from another std::array
                            // this is not possible with plain built-in arrays
  b = a;
  for (auto x : a)  //new syntax since c++11: auto is the type of each element of the array that is stored in x
    std::cout << x << " ";
  std::cout << std::endl;

  for (auto x : b)
    std::cout << x << " ";
  std::cout << std::endl;

  a[0] = 0;  // same subscripting operator without bound checking

  for (const auto x : a)
    std::cout << x << " ";
  std::cout << std::endl;

  for (const auto x : b)
    std::cout << x << " ";
  std::cout << std::endl;

  for (auto& x : a) //if I want to modify all the elements -> x is the true value of a!
    x *= 10;

  for (auto i = 0u; i < a.size(); ++i)
    std::cout << "a[" << i << "] = " << a[i] << std::endl;

  b.at(90);  // bound checking at run-time: before accessing the value it will check if it in the bound
  //at() function detect if the 90th element is in my array

  //these are as fast as built-in arrays
  //what if I want to change the dimension at a run time?

  return 0;
}
