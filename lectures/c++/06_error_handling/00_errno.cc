#include <cmath>
#include <iostream>
#include <cstring> // for strerror() -> returns a text version of a given error code

int main() {
  double d = std::sqrt(4);
  std::cout << d << " " << errno << " " << std::strerror(errno) << std::endl; // errno is a preprocessor macro used for error indication, and it is implementation dependent

  d = std::sqrt(-4);
  std::cout << d << " " << errno << " " << std::strerror(errno) << std::endl;

  d = std::sqrt(4);
  std::cout << d << " " << errno << " " << std::strerror(errno) << std::endl;
  // If there is an error but then I overwrite the variable with a good operation the error value doesn't change
  // Why it is not set to zero afterward? Because it's up to the user to decide what to do.
  // After an error is detected it is up to the user to do something: maybe you are fine with having a nan

  return 0;
}
