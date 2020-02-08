#include <iostream>

//CUSTOMED types -> we used some customed type from std: std::array, std::vector and std::string

//type: particular impelmentation of a concept -> int is a particular implementation of the integer numbers


//very first costumed type: enum
//traffic light: if I frst set 0 to green and 2 to red, and then I want to switch them, it's a mess because I have to change so many things in the code -> don't use magic numbers in the code! Put them in variables with meaningful names
enum color { red, yellow, green };
// enum color{red=0, yellow=1, green=2}; // equivalent
//If you have to use green+yellow or red+yellow use power of 2 as colours: red = 2, yellow = 4, green = 8 so they occupy a bit

void dwim(const color c) {
  switch (c) {  // instead of many if
    case red:  // way more readable than "case 0:"
      std::cout << "option 1: red\n";
      break;  // if I don't put break it executes also the following line
    case yellow:
      std::cout << "option 2: yellow\n";
      break;
    case green:
      std::cout << "option 3: green\n";
      break;
    default:  // what to do if no one of the cases apply to the condition -> ERROR HANDLING
      std::cout << "unknown option\n";  // should I exit the program?
      break;
  }
}

int main() {
  color opt{red};
  // opt = 3; // cannot assign int to enum
  int a{opt};  // but they implicitly converts to integers, so I can initialize an integer with an enum

  dwim(opt);

  dwim(yellow);  // I can also pass directly a value

  // dwim(2); // compile error: what is 2?!?
  dwim(color(2));  // works but why you may want to write this?

  dwim(color(6));  // ??? it works but since we don't have six colors it goes to the default option

  return 0;
}
