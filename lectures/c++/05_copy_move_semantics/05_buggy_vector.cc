#include <iostream>
#include <memory>

template <typename T>
class Vector {
  // A unique_ptr is an object that holds a pointer. We think of unique_ptr as a kind of pointer. However, the unique_ptr owns the object pointed to: when the unique_ptr is destroyed, it delete s the object it points to.
  // A unique_ptr is very much like an ordinary pointer, but it has one significant restriction: you cannot assign one unique_ptr to another to get two unique_ptr s to the same object. That has to be so, or confusion could arise about which unique_ptr owned the pointed-to object and had to delete it.
  // A unique_ptr has the interesting property of having no overhead compared to an ordinary pointer.
  // If you want to have a “smart” pointer that both guarantees deletion and can be copied, use a shared_ptr. However, that is a more heavyweight solution that involves a use count to ensure that the last copy destroyed destroys the object referred to.
  std::unique_ptr<T[]> elem; // With smart pointers it works? We're trying to fix the free() bug of shallow copy
  std::size_t _size;

 public:
  explicit Vector(const std::size_t length)
      : elem{new T[length]{}}, _size{length} {}

  const T& operator[](const std::size_t& i) const { return elem[i]; }
  T& operator[](const std::size_t& i) { return elem[i]; }

  std::size_t size() const { return _size; }

  // range-for
  const T* begin() const { return elem.get(); }
  T* begin() { return elem.get(); }

  const T* end() const { return elem.get() + _size; }
  T* end() { return elem.get() + _size; }
};

int main() {
  Vector<double> v1{7};
  //Vector<double> v2{v1}; // default copy ctor calls a deleted function by std::unique_ptr
  // You are the owner of that object, so no one can copy from you
  // If you decomment the line: error: use of deleted function ‘Vector<double>::Vector(const Vector<double>&)’

  return 0;
}
