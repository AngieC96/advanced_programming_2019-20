#include <iostream>

int main() {

   int a{5};  //integer
   int* p{&a}; //pointer to integer
   int& r{a}; //reference to integer -> it is an alias of a
   //int * x = &a
   //r --> (*x)

   std::cout << a << "\n"
             << p << "\n"
             << r << "\n"
	     << &a << "\n"
             << &p << "\n"
             << &r << "\n"
             << *p << "\n"
             << &(*p) << std::endl;

   return 0;
}
