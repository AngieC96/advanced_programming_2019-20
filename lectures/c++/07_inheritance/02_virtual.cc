#include <ap_error.h>
#include <iostream>

struct Animal {
  // You inherit not only data but also the INTERFACE! -> I'm forced to inplement all the methods that the base class has!
  unsigned int age;
  double weight;

  Animal(const unsigned int a, const double w) : age{a}, weight{w} {
    AP_ERROR(!(weight < 0)) << "invalid weight!\n";
  }

  Animal() : Animal{0, 0} {}  // delegating constructor

   // functions of the children should be marked as virtual
  virtual void speak() const = 0;  // pure virtual function ==> abstract class -> you cannnot istantiate an object of this class -> an abstract class is a class with at least one virtual method
  virtual void info() const noexcept {
    std::cout << "age:\t" << age << '\n' << "weight:\t" << weight << '\n';
  }

  virtual ~Animal() {}  // why? see file 03_virtual_destructor.cc
};

struct Dog : public Animal {
  void speak() const noexcept override { std::cout << "Bau\n"; }
  // override -> with virual -> same function, very similar parameters, DIFFERENT classes
  // c++11 -> override keyword to do the override, instead of repeating virtual
  // once if you exchanged two paraemters the compiler created a new virtual function, instead with override the compiler
  // double checked that there is an equal virtual function in the base class, otherwise it doesn't compile
  // overload -> same name of function with different parameters
  Dog() = default;
  Dog(const unsigned int a, const double d) : Animal{a, d} {}
};

struct Snake : public Animal {
  bool dangerous;
  Snake(const unsigned int a, const double w, const bool b)
      : Animal{a, w}, dangerous{b} {}
  explicit Snake(const bool b) : Animal{}, dangerous{b} {}
  void info() const noexcept override {
    Animal::info();
    std::cout << "dangerous:\t" << (dangerous ? "true" : "false") << std::endl;
  }
  void speak() const noexcept override { std::cout << "ssss\n"; }
};

// now we have virtual so it works!
void print_animal(const Animal& a) noexcept {
  std::cout << "throught ref\n";
  a.info();
  a.speak();
}

int main() {
  try {
    Snake s{true};
    s.info();
    s.speak();

    std::cout << std::endl;

    Animal* p = new Snake{1, 2.3, false};

    std::cout << "through pointer\n"; // problem solved!
    p->info();
    p->speak();

    delete p;

    std::cout << std::endl;

    print_animal(s);

    return 0;
  } catch (std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}