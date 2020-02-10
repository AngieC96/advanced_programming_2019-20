#include <iostream>

void dwim() {
  static int i = 0;  // this line is executed only once -> so it prints 1,2,3,4,5 and not 1,1,1,1,1
  ++i;
  std::cout << i << std::endl;
}

int main() {
  dwim();
  dwim();
  dwim();
  dwim();
  dwim();
  return 0;
}
