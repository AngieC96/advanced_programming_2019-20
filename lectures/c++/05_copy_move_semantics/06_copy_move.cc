#include <algorithm>  // std::copy
#include <iostream>
#include <memory>

template <typename T>
class Vector {
  std::size_t _size;
  std::unique_ptr<T[]> elem;  // Unique pointers

 public:
  // custom ctor
  explicit Vector(const std::size_t length)
      : _size{length}, elem{new T[length]{}} {
    std::cout << "custom ctor\n";
  }

// std::vector<int> v{4,2}; // vector of 2 elemnts: 4 and 2
// std::vector<int> v(4,2); // vector of 4 elements of value 2 each
// If there is ambiguity the initializer list wins:
// Vector<int> v{4}; -> is the initializer list or the constructor that takes the size? The standard says that is the initializer list

// std::vector<int> v{1, 2, 3}; //vector of 3 elements: 1, 2 , 3
// Our Vector class is not able to do that. How can we do that?
// Since c++11 we have the initializer list: list of elements of the same type, so when we write
// this it first makes a list of the values {1, 2, 3} and then it copies them int the vector
// deducing the size from the number of arguments

  // Vector(const std::initializer_list<T> args)
  //     : _size{args.size()}, elem{new T[_size]} {
  //   std::cout << "list ctor\n";
  //   std::copy(args.begin(), args.end(), begin());
  // }

  // default ctor
  Vector() { std::cout << "default ctor\n"; }  // _size uninitialized
  // Vector() : _size{}, elem{} { std::cout << "default ctor\n"; } // this could
  // be better Vector() = default;

  ~Vector() = default;

  /////////////////////////
  // copy semantics

  // copy ctor -- deep copy
  Vector(const Vector& v);

  // copy assignment -- deep copy
  Vector& operator=(const Vector& v);  // const because when you copy you shoudn't modify the vector!
  // end of copy semantics
  /////////////////////////

  /////////////////////////
  // move semantics

  // move ctor
  Vector(Vector&& v) : _size{std::move(v._size)}, elem{std::move(v.elem)} {  // For built-in type a move is a copy! For _size is just a copy, for elem I'm invoking the move semantics of unique pointers. Pointers are built-in types, and unique pointers are as fast as them
    // arg value 
    std::cout << "move ctor\n";
  }

  // Vector(Vector&& v) = default; // ok

  // move assignment: I do a move element-wise
  Vector& operator=(Vector&& v) {
    std::cout << "move assignment\n";
    _size = std::move(v._size);
    elem = std::move(v.elem);
    // Move is the best implementation of a SWAP!
    // In the transpose matrix exercise --->>>> A = std::move(transposed);
    return *this;  // A pointer to yourself = the instantiated object -> when you dereferentiate it you get the object
  }

  // Vector& operator=(Vector&& v) = default; // ok

  // end move semantics
  /////////////////////////

  const T& operator[](const std::size_t& i) const { return elem[i]; }
  T& operator[](const std::size_t& i) { return elem[i]; }

  std::size_t size() const { return _size; }

  // range-for
  const T* begin() const { return &elem[0]; }
  T* begin() { return &elem[0]; }

  const T* end() const { return &elem[_size]; }
  T* end() { return &elem[_size]; }
};

// copy ctor -> here we want to to a copy element-wises
template <typename T>
Vector<T>::Vector(const Vector& v) : _size{v._size}, elem{new T[_size]} {
  std::cout << "copy ctor\n";
  std::copy(v.begin(), v.end(), begin()); // Instead of doing a for loop
}

// copy assignment
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& v) {
  std::cout << "copy assignment (\n";

  //auto &ov = v;
  //ov = v; -> segmentation fault because you've deleted yourself and then you're trying to copy yourself
  // To avoid this we write:
  if (&v == this)
    return *this;

  // we could decide that this operation is allowed if and only if
  // _size == v._size
  //

  elem.reset();              // first of all clean my memory -> reset is a public function of the unique pointers
  auto tmp = v;              // then use copy ctor
  (*this) = std::move(tmp);  // finally move assignment

  // or we do everything by hand..
  // and we can do not reset and call new again if the sizes are suitable

  std::cout << ")\n";
  return *this;

  // is this approach consistent with self-assignment vx=vx?
}

template <typename T>
// why we return by value?
Vector<T> operator+(const Vector<T>& lhs, const Vector<T>& rhs) {
  const auto size = lhs.size();

  // how we should check that the two vectors have the same size?

  Vector<T> res(size);
  for (std::size_t i = 0; i < size; ++i)
    res[i] = lhs[i] + rhs[i];

  return res;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector<T>& v) {
  for (const auto& x : v)
    os << x << " ";
  os << std::endl;
  return os;
}

int main() {
  std::cout << "Vector<int> v0; calls\n";
  Vector<int> v0;
  std::cout << v0.size() << "\n";
  std::cout << "Vector<int> v00{}; calls\n";
  Vector<int> v00{};
  std::cout << v00.size() << "\n";

  std::cout << "\nVector<double> v1{5}; calls\n";
  Vector<double> v1{5};

  std::cout << "\nVector<double> v2 = v1; calls\n";
  Vector<double> v2 = v1;
  std::cout << "\nv2 = Vector<double>{7}; calls\n";
  v2 = Vector<double>{7};
  std::cout << "\nVector<double> v3{std::move(v1)}; calls\n";
  Vector<double> v3{std::move(v1)};  // now v1 should not be used
  std::cout << "\nv3 = v2; calls\n";
  v3 = v2;
  std::cout << "\nv2 = " << v2;
  std::cout << "v3 = " << v3;

  std::cout << "\nassign some values to v3\n";
  {
    // auto i = v3.size();
    // while (i--)
    //   v3[i] = i;

    int c = 0;
    for (auto& x : v3)
      x = c++;
  }
  // v3=v3;
  std::cout << "\nv2 = " << v2;
  std::cout << "v3 = " << v3;

  std::cout << "\nVector<double> v4{v3 + v3}; calls\n";
  Vector<double> v4{v3 + v3};

  std::cout << "v4 = " << v4;

  std::cout << "\nNRVO: Named Return Value Optimization\n";
  // v4 is created and then res is called inside it, so there's not a call to the move ctor -> It's faster!

  std::cout << "\nv4 = v3 + v3 + v2 + v3; calls\n";
  v4 = v3 + v3 + v2 + v3;
  std::cout << "v4 = " << v4;

  return 0;
}
