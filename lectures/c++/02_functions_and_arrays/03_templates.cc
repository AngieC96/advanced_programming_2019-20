#include <iostream>

//Can I avoid to put the type? YES, with templates -> a mechanism to write a good code at compile time
template <typename T>
T dwim(const T a, const T b);

int main() {
  int a{5}, b{7};
  double c{3.332}, d{7.7};
  float e{23.4}, f{3.34e2};
  char g{'0'}, h{'6'};

  std::cout << dwim<int>(a, b) << '\n' //I can specifty what the compiler should use instead of T
            << dwim(a, b) << '\n'
            << dwim(c, d) << '\n' // if the compiler can infer the type of the template, you can omit <type>
            << dwim<int>(c, d) << '\n' // if you pass the arguments as int it makes the sum between integers!
            << dwim(e, f) << '\n'
            << dwim(g, h) << std::endl;
  return 0;
}

template <typename T>
T dwim(const T a, const T b) {
  return a + b;
}
