#include <iostream>

int main() {

  //loops

  for (int i = 0; i < 10; ++i) {  //for(;;) -> never ending loop
       //for(what to do at the beginning of the loop; condition checked at the beginning of each opertion; condition esegiuted at the end of an iteration)
    std::cout << i << " "; // if the action is just one line, {} can be omitted
  }

  // std::cout << i << '\n';	// error, i is out of scope -> i exixts only inside the curly brackets of the loop

  std::cout << std::endl;

  int i{};

  while (i < 10) //  while the condition is true, evaluate the content of the scope
    std::cout << i++ << " ";

  std::cout << "\n after while i is " << i << "\n"; // I have defined i OUT of the while! If I initialize it inside the scope, it will be created and destroied at each iterations

  std::cout << std::endl;

  do {					//first executes the scope, then evaluates the condition -> it executes the scope always one time
    std::cout << "inside do \n";
  } while (i < 2); // note ; at the end

  std::cout << "\n break at i=2" << std::endl;

  for (i = 0; i < 5; ++i) {
    if (i == 2)
      break;  // exit the innermost loop
    std::cout << i << std::endl;
  }

  std::cout << "\n continue at i=2" << std::endl;

  for (i = 0; i < 5; ++i) {
    if (i == 2)
      continue;  //
    std::cout << i << std::endl;
  }

  std::cout << std::endl;
}
