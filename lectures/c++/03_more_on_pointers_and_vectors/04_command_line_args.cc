#include <iostream>

int main(int argc, char* argv[]) { //int argc is the argument counter, char* argv[] = array of char * (= array of strings!): it stores all the arguments we pass from the command line
  for (auto i = 0; i < argc; ++i)
    std::cout << "argv[" << i << "] = " << argv[i] << std::endl;
  return 0;
}

// $ ./04_command_line_args.x first second 3 45
// argv[0] = ./04_command_line_args.x
// argv[1] = first
// argv[2] = second
// argv[3] = 3
// argv[4] = 45
