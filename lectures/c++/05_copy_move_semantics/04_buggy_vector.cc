#include <iostream>

template <typename T>
class Vector {
  T* elem;
  std::size_t _size;

 public:
  // A constructor that takes a single argument defines a conversion from its argument type to its class.
  // A constructor defined explicit provides only the usual construction semantics and not the implicit conversions.
  explicit Vector(const std::size_t length)  // Only in the constructors with one arguments: puts in front of each constructor
  //Vector(const std::size_t length)
      : elem{new T[length]{}}, _size{length} {}  // elem{new T[length]} (= malloc) doesn't initialize the vector, while  elem{new T[length]{}} (= calloc) initializes the elements of the vector to 0

  ~Vector() { delete[] elem; }

  const T& operator[](const std::size_t& i) const { return elem[i]; }
  T& operator[](const std::size_t& i) { return elem[i]; }

  std::size_t size() const { return _size; }

  // range-for
  const T* begin() const { return elem; }  // const -> I invoke the function but I cannot modify the value
  T* begin() { return elem; }

  const T* end() const { return elem + size(); }
  T* end() { return elem + size(); }   // I have to be one after the last element
};

void print (const Vector<int>& v){
  for (auto x : v)
    std::cout << x << std::endl;
}

int main() {
  Vector<int> v1{3};
  v1[0] = 1;
  v1[1] = 2;
  v1[2] = 3;

  print(v1);
  //print(1); // Whitout explicit in the constructor it compiles anyway! And prints 0 -> it creaes a vector of 1 element
  // With explicit: compile error: invalid initialization of reference of type ‘const Vector<int>&’ from expression of type ‘int’

  std::cout << "v1: ";
  for (const auto x : v1)   /* v1 is the container. Since c++11: requires a begin() and an end() function.
  This is equivalent to:
  {
    auto it = v1.begin()
    auto stop = v1.end()
    for (; it != stop; ++it){
      const auto x = *it;
    }
  } */
    std::cout << x << " ";
  std::cout << std::endl;

  Vector<int> v2{v1};  // default copy constructor -> it compiles: apparently I can copy, but the copy is element-wise or not?
  // Let's check the copy
  std::cout << "v2 after default copy ctor: ";
  for (const auto x : v2)
    std::cout << x << " ";
  std::cout << std::endl;

  v1[0] = 99;

  std::cout << "v2 after v1 has been changed: ";
  for (const auto x : v2)
    std::cout << x << " ";
  std::cout << std::endl;

  v2[1] = -999;

  std::cout << "v1 after v2 has been changed: ";
  for (const auto x : v1)
    std::cout << x << " ";
  std::cout << std::endl;

  // v1.elem = v2.elem!!!! -> shallow copy: a cheap copy! But they refers to the same array in the heap -> v1 and v2 are entangled, linked
  // If I call twice the destructor, once on v2 nd once in v1 I get an error
  // free(): double free detected
  // Aborted.
  // RAII = resource aquisistion is initialization

  return 0;
}
