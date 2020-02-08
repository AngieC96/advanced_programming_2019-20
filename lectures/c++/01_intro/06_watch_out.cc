#include <iomanip>
#include <iostream>
//#include <cmath.h>

int main() {
  // size matters!
  int a = 1;
  for (int i = 0; i < 33; ++i) {
    a *= 2;				// OVERFLOW: the content is too big for the variable type! After some iterations a=0!
    std::cout << a << std::endl;
  }

  // never ever use == (or !=) with floating point numbers -> there is an error, a trashold, they are not accurate: they are approximated!

  // for (double d = 0.1; d != 1.0; d += 0.1)
  //   std::cout << d << std::endl;

  // std::cout << std::setprecision(50);
  // double d = 0;
  // for (int i = 0; i < 10; ++i) {	// use the < or > signs to compare them!
  //   d += 0.1;			// 0.100000000000000000555115 -> we NEVER reach 1.0 exactly! So the loop never ends
  //   std::cout << d << std::endl;
  // }

  double d1,d2;
  if(std::abs(d1-d2) < 1e-15)
	


  return 0;
}
