#include <iostream>
#include <string>
#include <vector> //defines the std::vector

// template<class T, class Allocator = std::allocator<T>>
// class vector;

template <typename T>
void print_vector(const std::vector<T>& v, const std::string& s);

int main() {
  std::vector<int> v0{1, 2, 4}; //vector of three alements: 1, 2, 4
  std::vector<int> v1(4, 4); //array of 4 elements each one equal to 4 -> we are using different constructors

  print_vector(v0, "v0");
  print_vector(v1, "v1");

  v1 = v0; //copy element-wise -> also the length changes! v1.length = 3

  print_vector(v1, "v1 after copy");

  for (auto x : {7, 8, 9})
    v1.push_back(x); //to expand dinamically the vector -> push_back() adds an element at a time

  print_vector(v1, "v1 after push_back");

  for (auto i = 0u; i < v1.size(); ++i)
    std::cout << "v[" << i << "] = " << v1[i] << std::endl;  //v1[i] -> subscripting operator

  std::cout << v1[3] << " " << v1[78] << std::endl;        // no bounds checking
  std::cout << v1.at(3) << " " << v1.at(78) << std::endl;  // bounds checking

  return 0;
}

template <typename T>
void print_vector(const std::vector<T>& v, const std::string& s) {  //I can pass std::vectors by reference
  std::cout << s << ": ";
  for (const auto& x : v)
    std::cout << x << " ";
  std::cout << std::endl;
}

// an std::vector of std::vectors is a matrix!!!!

// a reference cannot have no value: I cannot assign to it nullptr
