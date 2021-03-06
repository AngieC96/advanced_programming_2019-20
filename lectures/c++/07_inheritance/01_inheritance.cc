#include "ap_error.h"
#include <iostream>

struct Animal {  // parent class or base class or super class
  unsigned int age;
  double weight;

  //protected: from outside (main, function outside the class, ...) is like private but children can access protected data
  //also friend classes can access protected data -> A non-member function can access the private and protected members of a class if it is declared a friend of that class

  Animal(const unsigned int a, const double w) : age{a}, weight{w} {
    AP_ERROR(weight >= 0) << "invalid weight: " << weight << std::endl;
  }

  Animal() noexcept : Animal{0, 0} {}  // delegating constructor

  void speak() const noexcept { std::cout << "Unknown\n"; }
  void info() const noexcept {
    std::cout << "age:\t" << age << '\n' << "weight:\t" << weight << '\n';
  }
};

struct Dog : public Animal {  // Dog is an Animal -> it will have its variables and its methods
  // so here Dog has an age and a weight
  void speak() const noexcept { std::cout << "Bau\n"; } // Overriding
  Dog() noexcept = default;
  Dog(const unsigned int a, const double d) : Animal{a, d} {}  // delegating constructor -> much better than initializing directly the variables with Animal constructor
  // doesn't not implement info() because the Animal one is fine for Dog
};

struct Snake : public Animal {  // child class or derived class -> it inherits from Animal class
  bool dangerous;
  Snake(const unsigned int a, const double w, const bool b)
      : Animal{a, w}, dangerous{b} {}  // ORDER: fom top to down!!! First call the constructor of the parent and then initialize child's members
  explicit Snake(const bool b) noexcept : Animal{}, dangerous{b} {}
  void info() const noexcept {  // info() of Animal is not working anymore! -> Overriding
    Animal::info();
    std::cout << "dangerous:\t" << (dangerous ? "true" : "false") << std::endl;
  }
  void speak() const noexcept { std::cout << "ssss\n"; }
};

// run-time (dynamic) polymorphism -> with references and pointers, NOT values!
void print_animal(const Animal& a) noexcept { // no templates here!
  std::cout << "through ref\n";
  a.info();
  a.speak();
}

// compile-time (static) polymorphism
/// all the types must be known at compile time
// you can pass a Dog or a Snake (because they are an Animal! IS-A)
template <class T>
void print_animal_template(const T& a) noexcept {
  std::cout << "through template\n";
  a.info();
  a.speak();
}

int main() {
  try {
    Dog d;
    d.info();
    d.speak();

    std::cout << std::endl;

    Dog d1{1, 0.6};
    d1.info();
    d1.speak();

    std::cout << std::endl;

    Snake s{2, 1.4, true};
    s.info();
    s.speak();

    std::cout << std::endl;

    Animal* p = new Snake{1, 2.3, false};
    std::cout << "through pointer\n";
    p->info();
    p->speak(); // it doesn't print ssss! -> object slicing because it's an Animal* and NOT a Snake*!

    delete p;

    std::cout << std::endl;

    print_animal(s); // it is a Animal -> s is a reference!
    // it's wrong: it doesn't print ssss nor the dangerous variable -> it cannot access to the members of the children!
    //this is caled OBJECT SLICING -> the class is re-casted as its parent

    std::cout << std::endl;

    print_animal_template(s); // this works!

    return 0;
  } catch (std::runtime_error& e) {
    std::cerr << e.what() << std::endl;
    return 1;
  }
}
