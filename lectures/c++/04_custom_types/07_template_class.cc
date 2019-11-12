#include <iostream>
#include <string>

// LEt's write our class Vector
template <typename num>
class Vector {
  num* elem; // there will be an array creation
  std::size_t _size; // to store the size of the array

 public:
  // constructor
  Vector(const std::size_t size) : elem{new num[size]}, _size{size} {} //I don't need to put anything in the body, but I have to put the body

  // automatically release the acquired memory
  ~Vector() { delete[] elem; }

  // RAII (Resource Acquisition Is Initialization): you require an initialization and release it in the constructor -> no memory leaks!

  // try to remove the const and recompile
  std::size_t size() const { return _size; }  //const: when I use the object I will not modify it

  num& operator[](const std::size_t i) { return elem[i]; }

  // try to comment this line and recompile
  const num& operator[](const std::size_t i) const { return elem[i]; }
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v) { // const allows you to call ONLY the function with a const before the body (the last one)
  for (auto i = 0u; i < v.size(); ++i)
    os << "v[" << i << "] = " << v[i] << std::endl;
  return os;
}

int main() {
  Vector<double> v{10};

  for (auto i = 0u; i < v.size(); ++i)
    v[i] = i;

  std::cout << v << std::endl;

  Vector<double>* pv{&v}; //pointer to a vector double

  // first dereference the pointer, then I can use the defined operators
  (*pv)[0] = -99.999;

  pv->operator[](1) = 77777.3333;  // or I call the function by name

  std::cout << *pv << std::endl;

  Vector<double>& rv{v};

  rv[5] = 555;  //with reference works perfectly

  std::cout << v << std::endl;

  return 0;
}
