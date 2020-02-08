#include <array>
#include <iostream>
#include <vector>

// c++ at the beginning meant 'c with classes'
// Difference between c structs and c++ classes: in classes I can put data AND functions! I can group them together in a single box
//difference between c++ structs and c++ classes: the default visibility of the symbols. In struct everything is pubblic: from
// the outside I can see everything that is in the struct, while in the classes everything is private: from outside I cannot access to anything

struct Point_s {
  double x;
  double y;
  void print();
};  // note ; at the end

void Point_s::print() { //fully qualified name
  std::cout << "Structure. x = " << x << "; y = " << y << std::endl; //I can use x and y because I am in the struct
}

class Point_c {
  double x;
  double y;

 public:  // I can modify the visibility -> it's not for the class itself but from the others
  void print() { //I can both define a function outside or inside
    std::cout << "Class. x = " << x << "; y = " << y << std::endl;
  }  // note no ; at the end -> you get a warning if you put it
};   // note ; at the end

int main() {
  //How can I access data = members of the class from outside?
  Point_s ps;
  ps.x = 9.9;  //. = dot operator
  ps.y = 3. / 7;

  ps.print();

  Point_c pc;  // Instantiations of the class
  // pc.x =7.6; // error
  pc.print();  // I can access private data through public functions

  Point_s* p = &ps; // Pointer to a class: I can initialize it with a variable of that class
  // Size of a class >= sum of the sizes of its elements
  p->x = 0.0; // How can I access the data of a pointer? I CANNOT use "." I need to use the arrow opertor '->'
  p->print(); // It's the same with functions

  auto& pr = ps; // pr is a reference to the class object ps, instantiation of the struct
  ++pr.x;
  pr.print(); // equal to ps.print() -> a reference is an alias!
  // How can I know the type of pr? Trigger a compiler error: use a template function and call pr

  Point_s array_of_structs[8];  // built-in array
  array_of_structs[0].x = 1;
  array_of_structs[0].y = 2;

  std::array<Point_s, 5> as;
  as[3].x = 3;

  std::vector<Point_s> vs;
  vs.push_back(ps);  // It's COPYING the value
  vs[0].x = 999;
  ps.x = 11;
  ps.print();
  vs[0].print();

  return 0;
}
