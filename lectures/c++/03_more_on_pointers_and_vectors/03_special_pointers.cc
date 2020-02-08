#include <cstring>  // strcmp
#include <iostream>

int func1(const char* a);
int func2(const char* a);
void func3(const char* a);

int main() {
  int a{8};
  int* pi{&a};

  char** ppc; //pointer to a pointer char

  int* ap[7]; //array of 7 elements that are pointers to integer

  void* pv{pi}; //void* = special type of pointer that can implicily convert each pointer to void*
  // *pv; // we cannot dereference void*
  // ++pv; // we cannot increment and use pointer arithmetic. Why? We don't know its size!
  int* pi2{static_cast<int*>(pv)};  //different types of cast(conversion between types): this one static cast: cast performed a compile time (and also checked: you cannot do an int cast of a string!)
  //double * a = (double *) malloc(sizeof(double)*N)  //c style cast -> strongly checked!
  //double * a = malloc(sizeof(double)*N)  //c is weakly checked so this is acepted
  //double * a = static_cast<double*> (malloc(sizeof(double)*N)) //c++ style cast -> strongly checked!

  pv = ppc;
  pv = ap;
  pv = pi;

  pi = nullptr;  //nullptr = 'nothing' -> new type -> it points to nothing. There exist implicit conversions from nullptr to null pointer value of any pointer type and any pointer to member type
  ppc = nullptr;
  // ap = nullptr;  // error, why? -> error: incompatible types in assignment of ‘std::nullptr_t’ to ‘int* [7]’ -> it isn't automatically deferentiated!
  // ap is a vector, not a pointer!
  ap[0] = nullptr;
  int** bbb; //pointer to a pointer integer
  bbb = ap; // bbb points to the pointer of the frist element
  pv = nullptr;
  pi2 = 0;  // older codes. gets the nullptr -> older codes: #define NULL = 0, now #define NULL nullptr

  // pi = NULL; // please don't do this. Never mix NULL and nullptr, use ONLY nullptr

  double* da{new double[5]{}};
  delete[] da;  // dangling pointer = pointer that points to a memory location that was freed -> it is still pointing to that memory location!
  da = nullptr;  //to be sure not to access it later

  if (pi != nullptr)
    std::cout << "pi is not nullptr and I can dereference it " << *pi
              << std::endl;

  if (pi) //equal to before, because 0 is false while all the rest is true, and if pi is a nullptr his value is 0
    std::cout << "pi is not nullptr and I can dereference it " << *pi
              << std::endl;

  if (pi == nullptr)
    std::cout << "pi is nullptr and I CANNOT dereference it \n";

  if (!pi)
    std::cout << "pi is nullptr and I CANNOT dereference it \n";


  // strings are special type of char[] (array of char): they have one more last element to understand that the string is finished
  // string literal: "Hello" -> it is a const char[6] that contains 'H', 'e', 'l', 'l', 'o', '\0'
  // A string literal is not necessarily a c string: if a string literal has embedded a null characters \0, it represents an array that contains morethan one string.
  const char *parola = "abc\0efg"; // std::strlen(p)==3, but the array has size 8
  char word[]{"Hello"};
  char word2[]{'H', 'e', 'l', 'l', 'o', 0};
  if (strcmp(word, word2) == 0)  // word == word2 is
                                 // implementation-dependent (it might
                                 // compare the two pointers, i.e. the
                                 // two addresses of word and word2)
    std::cout << "same\n";
  else
    std::cout << "different\n";

  int (*fp)(const char*); //I'm defining a pointer to function called fp that points to all the functions that takes a const char * and returns an int -> parenthesis are mandatory!
  //int *fp(const char*);  //defining a funtion fp that returns a int* and takes a const char*
  fp = func1;

  fp("hello");

  fp = &func2;
  fp("world");

  // fp = func3; // error: wrong signature -> func3 returns a void and not an integer!
  auto xx = func3;

  xx("auto");

  //decltype -> Inspects the declared type of an entity or the type and value category of an expression
  decltype(&func3) x = func3; //I'm declaring a varible of type whatever is the returning type of the func3 function. It is instead of:
  //void (*x) (const char *) = func3; -> if I change the signature of func3 after having written this line I have to change this line manually
  x("decltype");

  return 0;
}

int func1(const char* a) {
  std::cout << "1111: " << a << std::endl;
  return 1;
}

int func2(const char* a) {
  std::cout << "2222: " << a << std::endl;
  return 2;
}

void func3(const char* a) {
  std::cout << "3333: " << a << std::endl;
}
