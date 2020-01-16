#include <iostream>
extern "C"{
  void hello(){
    std::cout << "Hello, World" << std::endl;
  }
}

int main(){
  hello();
  printf("Hello world\n");
  printf("Ciao\n");
}
