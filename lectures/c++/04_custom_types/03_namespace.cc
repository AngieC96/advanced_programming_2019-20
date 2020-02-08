#include <iostream>

// namespace: puts the name of the space where the variable lives before the name of the variable -> avoids name crashing

namespace choose_a_name {

  int variable;

  namespace nested {

    void hello1();
    void hello2();
    void hello3();

  }  // namespace nested
}  // namespace choose_a_name

// we travel in the namesaces using the :: operator, called SCOPE RESOLUTOR

int main() {
  // variable = 42; // error
  choose_a_name::variable = 42;
  // hello1(); // error
  choose_a_name::nested::hello1();
  choose_a_name::nested::hello2();
  choose_a_name::nested::hello3();
  return 0;
}

void choose_a_name::nested::hello1() {
  std::cout << "hello1 from nested\n"
            << "variable is " << choose_a_name::variable << std::endl;
} //I'm not in any namespace, so the variable 'variable' is visible only using its fully qualified name

namespace choose_a_name {
  namespace nested {
    void hello2() {
      std::cout << "hello2 from nested\n"
                << "variable is " << variable << std::endl;
    }
  }  // namespace nested
}  // namespace choose_a_name

using namespace choose_a_name; // I'm in the namespace choose_a_name. From now on, I don't need to repeat choose_a_name:: 

void nested::hello3() {
  std::cout << "hello3 from nested\n"
            << "variable is " << variable << std::endl;
}
