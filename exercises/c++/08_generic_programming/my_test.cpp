#include "my_find_if.hpp"
#include <vector>
#include <numeric>
#include <algorithm>
#include <iostream>
#include <chrono>  // for timing


// function object -> to pass the right predicate
template <typename T>
class predicate_template{

  T value;

public:
  predicate_template(const T& x): value{x} {}
  bool operator()(const T& x) const noexcept { return x == value; } // functions declared inside a function are inlined -> no function call -> super fast!
};


template <class T>
class predicate_virtual : public predicate_base<T> { // an object of predicate_ virtual can be passed to an object of predicate_base
  T value;

public:
  predicate_virtual(const T& x) : value{x} {}
  vistual bool operator()(const T& x) const noexcept override { return x == value; }
}


int main(){
  constexpr std::size_t N = 1024*1024*100;
constexpr int target = 99'000'000;  // since c++?
  std::vector<int> v(N);
  std::iota(v.begin(), v.end(), -1024); // since c++11

  auto t0 = std::chrono::high_resolution_clock::now();
  auto it = find_if_hardcoded(v.begin(), v.end(), target);  // an iterator
  auto t1 = std::chrono::high_resolution_clock::now();
  std::cout << "hardcoded " << std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count() << std::endl;
  if (it != v.end())
    std::cout << "found " << *it << "at position " << std::distance(v.begin(), it) << std::endl; // distance override the function for each type: iterators is the difference, linked list are the steps


  t0 = std::chrono::high_resolution_clock::now();
  it = find_if_template(v.begin(), v.end(), predicate_template<int>{target}); // will create a temporary object that will act as a predicate
  t1 = std::chrono::high_resolution_clock::now();
  std::cout << "template " << std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count() << std::endl;
  if (it != v.end())
    std::cout << "found " << *it << "at position " << std::distance(v.begin(), it) << std::endl;


  t0 = std::chrono::high_resolution_clock::now();
  it = find_if_template(v.begin(), v.end(), 
									//["capture"]("arguments"){ "body"; } // lambda functions -> since c++11 -> the compiler will create a function object
                                   // [target](int x){}  // target is an int so is better to capture it by value and not by reference
                                      [target](auto x){ return x == target;}  // lambda function -> define a function in the middle in the code!
                     );
  t1 = std::chrono::high_resolution_clock::now();
  std::cout << "template - lambda " << std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count() << std::endl;
  if (it != v.end())
    std::cout << "found " << *it << "at position " << std::distance(v.begin(), it) << std::endl;

  t0 = std::chrono::high_resolution_clock::now();
  it = find_if_virtual(v.begin(), v.end(), predicate_virtual<int>{target});
  t1 = std::chrono::high_resolution_clock::now();
  std::cout << "template - lambda " << std::chrono::duration_cast<std::chrono::milliseconds>(t1-t0).count() << std::endl;
  if (it != v.end())
    std::cout << "found " << *it << "at position " << std::distance(v.begin(), it) << std::endl;

}
