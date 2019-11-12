#include <cmath>
#include <iostream>

int main() {
  double d = std::sqrt(4);
  std::cout << d << " " << errno << std::endl;

  d = std::sqrt(-4);
  std::cout << d << " " << errno << std::endl;

  d = std::sqrt(4);
  std::cout << d << " " << errno << std::endl;
  // If there is an error but then I overwrite the variable with a good operation the eroor value doesn't change
  // Why it is not set to zero afterward? Because it's up to the user to decide what to do.
  //After an error is detected it is up to the user to do something: maybe you are fine with having a nan

  return 0;
}
