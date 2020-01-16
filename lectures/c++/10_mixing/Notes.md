# Link different languages

A library doesn't have a main! You split between headers and functions



How to link `c` and `c++` libraries?

We can use inside `Python` our `c++` code! And use `Fortran` libraries in `c++`! 

```bash
$ cd lectures/c++/10_mixing/

$ ls
01_symbols     03_cpp_from_c  05_ctypes   Makefile  readme.md
02_c_from_cpp  04_libdl       06_fortran  Notes.md

```

To see the symboly declared into an object file:

```bash
$ cd 01_symbols/

$ make
cc    -c -o 01_hello.o 01_hello.c
cc    -c -o 03_visibility.o 03_visibility.c
c++    -c -o 02_hello.o 02_hello.cpp
c++    -c -o 04_extern.o 04_extern.cpp

$ cat 01_hello.c 
#include <stdio.h>

int main() {
  printf("hello, world\n");
  return 0;
}

$ nm 01_hello.o
                 U _GLOBAL_OFFSET_TABLE_
0000000000000000 T main
                 U puts

```

Or

```bash
$ gcc -c 01_hello.c -fno-builtin

$ nm 01_hello.o
                 U _GLOBAL_OFFSET_TABLE_
0000000000000000 T main
                 U printf

```

`printf` in undefined and when we will link this `.o` file he will link the io-library and the compiler will resolve where that function is

We can immediately recognize that it is `c` because of the names of the symbols

```bash
$ cat 02_hello.cpp
#include <iostream>

void hello(){
  std::cout << "Hello, World" << std::endl;
}

int main(){
  hello();
}

$ nm 02_hello.o
                 U __cxa_atexit
                 U __dso_handle
                 U _GLOBAL_OFFSET_TABLE_
0000000000000088 t _GLOBAL__sub_I__Z5hellov
000000000000002f T main
000000000000003f t _Z41__static_initialization_and_destruction_0ii
0000000000000000 T _Z5hellov
                 U _ZNSolsEPFRSoS_E
                 U _ZNSt8ios_base4InitC1Ev
                 U _ZNSt8ios_base4InitD1Ev
                 U _ZSt4cout
                 U _ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
0000000000000000 r _ZStL19piecewise_construct
0000000000000000 b _ZStL8__ioinit
                 U _ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
```

In `C++` it is more complicated!!!!

The function `hello` is named `_Z5hellov`. While in `c` their names are equal to the names of the functions (verbatim copy).

The generated symbols MUS BE UNIQUE! So since in `c++` you can do overloading (different function with the same name but different arguments) they added more letters. In `C` you cannot do overloading so there is no problem



**Recap on the visisbility of the symbols:**

```bash
$ cat 03_visibility.c
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

static const int val1 = -5;
const int val2 = 10; // In c+++ they would have been equal, but here we are using c so they are not!
static int val3 = -20;
int val4 = -15;
extern int errno;

static int add_abs(const int v1, const int v2) {
  return abs(v1) + abs(v2);
}

int main() {
  int val5 = 20;
  printf("%d / %d / %d / %d\n", add_abs(val1, val2), add_abs(val3, val4),
         add_abs(val1, val5), errno);
  return 0;
}

$ nm 03_visibility.o
0000000000000000 t add_abs
                 U errno
                 U _GLOBAL_OFFSET_TABLE_
000000000000002a T main
                 U printf
0000000000000000 r val1
0000000000000004 R val2
0000000000000000 d val3 // internal linkage
0000000000000004 D val4 //external linkage
```

Weak symbols are implementation dependent! You can have surprises!!!!

If you write a `printf` function without putting any variable but only a string, the compiler will call the`puts`function because it is simpler!

In the code

```c
printf("%d / %d / %d / %d\n", add_abs(val1, val2), add_abs(val3, val4), add_abs(val1, val5), errno);
```

`%d` is called PRINT HOLDER.



The return type is not part of the name, of the symbol of the function!



## `C` library in `C++` code

The linker is agnostic of the language you used to produce the `.o` file!

```
$ ls
01_hello.c  02_hello.cpp  03_visibility.c  04_extern.cpp  Makefile
01_hello.o  02_hello.o    03_visibility.o  04_extern.o

$ cat 04_extern.cpp 
#include <iostream>
extern "C"{
  void hello(){
    std::cout << "Hello, World" << std::endl;
  }
}

int main(){
  hello();
}
```

`extern "C"` → Please export the symbols in `C` style

```
$ nm 04_extern.o
                 U __cxa_atexit
                 U __dso_handle
                 U _GLOBAL_OFFSET_TABLE_
0000000000000088 t _GLOBAL__sub_I_hello
0000000000000000 T hello
000000000000002f T main
000000000000003f t _Z41__static_initialization_and_destruction_0ii
                 U _ZNSolsEPFRSoS_E
                 U _ZNSt8ios_base4InitC1Ev
                 U _ZNSt8ios_base4InitD1Ev
                 U _ZSt4cout
                 U _ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_
0000000000000000 r _ZStL19piecewise_construct
0000000000000000 b _ZStL8__ioinit
                 U _ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
```

When you are in an ` extern "C"` block you cannot implement function overloading for example!

```
$ nano 04_extern.cpp
```

And we add the last lines:

```c++
v
```

The we compile:

```bash
$ g++ 04_extern.o

$ ldd a.out
	linux-vdso.so.1 (0x00007ffd89ded000)
	libstdc++.so.6 => /usr/lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007f87b0904000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f87b0513000)
	libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f87b0175000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f87b0e8f000)
	libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007f87aff5d000)
```

It linked automatically against `C` language! `libgcc_s.so.1`   ==???==



### `C` in `C++`

How can I call a `C` function from a Cc++` code?

```bash
$ cd ../02_c_from_cpp/

$ ls
hello.c  hello.h  main.cpp  Makefile

$ make
cc -c hello.c -o hello.o
c++ main.cpp -c -o main.o
c++ hello.o main.o -o exe
```

Always use the linker of the language in which the main is written!

```bash
$ cat hello.h
void hello_from_c();
```

It a bad header: the `#ifdef` is missing! → it's a simpler header: it contains only the prototype of the functions

```bash
$ cat main.cpp 
extern "C" {
#include "hello.h" // it contains the prototype of the function!
}

int main() {
  hello_from_c();
  return 0;
}
```

I have to inform the `C++` compiler that the compilation will be finenano

```
$ nm hello.o 
                 U _GLOBAL_OFFSET_TABLE_
0000000000000000 T hello_from_c
                 U puts

$ nm main.o
                 U _GLOBAL_OFFSET_TABLE_
                 U hello_from_c
0000000000000000 T main
```

`#include` is for the compiler

`extern "C"` is for the linker 



You can write the `C++` plug-in and then you have to figure out how to use them in the `C` code

`Python` id written in `C` so you cannot use `C++` inside it!

## `C++` from `C`

```bash
$ cd ../03_cpp_from_c/01_func/

$ ls
cpp2c.cc  main.c  Makefile

$ make
c++ -std=c++11 -c cpp2c.cc -o cpp2c.o
cc    -c -o main.o main.c
cc cpp2c.o main.o -lstdc++ -o exe

$ cat cpp2c.cc 
#include <iostream>

extern "C" {
void hello_from_cpp() {
  std::cout << "hello from cpp\n";
}
}

$ nm cpp2c.o
                 U __cxa_atexit
                 U __dso_handle
                 U _GLOBAL_OFFSET_TABLE_
0000000000000063 t _GLOBAL__sub_I_hello_from_cpp
0000000000000000 T hello_from_cpp
000000000000001a t _Z41__static_initialization_and_destruction_0ii
                 U _ZNSt8ios_base4InitC1Ev
                 U _ZNSt8ios_base4InitD1Ev
                 U _ZSt4cout
0000000000000000 r _ZStL19piecewise_construct
0000000000000000 b _ZStL8__ioinit
                 U _ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc
                 
$ cat main.c
extern void hello_from_cpp(void); // could be avoided: functions takes external linkage by default

int main(int argc, char* argv[]) {
  hello_from_cpp();
  return 0;
}

```

Now:

```bash
$ make -B
c++ -std=c++11 -c cpp2c.cc -o cpp2c.o
cc    -c -o main.o main.c
cc cpp2c.o main.o -lstdc++ -o exe // the compiler is the one of the main!

$ cat cpp2c.cc 
#include <iostream>

extern "C" {
void hello_from_cpp() {
  std::cout << "hello from cpp\n";
}
}
```

For the compiler

```c
void hello(); /* C only not C++*/
int main(){
	hello(1, 2, 3, 4);
}
```

this is fine, but if the linker doesn't find an hello() function that take 4 arguments it complains. So you can write `void` as argument for the hello function:

```c
void hello(void); /* C only not C++*/
int main(){
	hello(1, 2, 3, 4);
}
```

`C` → Strongly typed weakly checked

`C++` → Strongly typed strongly checked



​             LD                                                         (assembly)             ELF

| src |  →  | IL |                     → | opt | →        | as |          → | .o |

​                (Intermediate Language)

`-lstdc++` → we link against a `C++` library!



```bash
$ ls
cpp2c.cc  cpp2c.o  exe  main.c  main.o  Makefile

$ make -B
c++ -std=c++11 -c cpp2c.cc -o cpp2c.o
cc    -c -o main.o main.c
cc cpp2c.o main.o -lstdc++ -o exe

$ ls
cpp2c.cc  cpp2c.o  exe  main.c  main.o  Makefile
```



```bash
$ cd ../02_class/

$ ls
class_c_interface.cpp  class.cpp  c-main.c      Makefile
class_c_interface.h    class.hpp  cpp-main.cpp

$ cat class.hpp 
#ifndef _CLASS_H_
#define _CLASS_H_

#include <iostream>

class Foo {
  int a;

 public:
  Foo(int b) : a{b} {}
  void print();
  int& get_a() { return a; }
};

#endif /* _CLASS_H_ */
```

How can I use this function in `C`?

```bash
$ cat class.cpp 
#include "class.hpp"
#include <iostream>
void Foo::print() {
  std::cout << a << std::endl;
}

$ cat cpp-main.cpp 
#include "class.hpp"

#include <iostream>

int main() {
  Foo f(10);
  f.print();
  f.get_a() = 7;
  f.print();
  return 0;
}
```

To generate just the `C++` code:

```bash
$ make cpp-main
c++ -c class.cpp -o class.o -std=c++11
c++ cpp-main.cpp class.o -o cpp-main -std=c++11
```

I link against `class.o`



Now I want to use this class in `C`:

```bash
$ ls
class_c_interface.cpp  class.cpp  class.o   cpp-main      Makefile
class_c_interface.h    class.hpp  c-main.c  cpp-main.cpp

$ cat c-main.c 
#include "class_c_interface.h"
#include <stdio.h>

int main() {
  Foo_c f = create_foo(11); // returns a pointer to a heap memory location
  print_foo(f);
  set_a(f, 7);
  print_foo(f);
  set_a(f, 9);
  printf("hello from c! a is %d\n", get_a(f));
  free_foo(f);  // so I have to free it to avoid memory leaks
  return 0;
}
```

We have to create a `C` interface for our class!

```bash
 ls
class_c_interface.cpp  class.cpp  class.o   cpp-main      Makefile
class_c_interface.h    class.hpp  c-main.c  cpp-main.cpp
```

We have a `class_c_interface.h` that has a `C` header and a `C++` implementation: so it have to be compiled with a `C++` compiler

```bash
$ cat class_c_interface.h
#ifndef _CLASS_C_INTERFACE_H_
#define _CLASS_C_INTERFACE_H_

typedef void* Foo_c; // pointer to void = pointer to whatever!

#ifdef __cplusplus
extern "C" {
#endif

Foo_c create_foo(int b); // constructor know just by the c++ compiler!
void free_foo(Foo_c);
void print_foo(Foo_c);
void set_a(Foo_c, int v);
int get_a(Foo_c); // cannot return a refernce, but retruns by vaue! I have to call the function set_a to change a → it is C!

#ifdef __cplusplus
}
#endif

#endif /* _CLASS_C_INTERFACE_H_ */
```

You compiler with:

```bash
$ make
c++ -c class_c_interface.cpp -o class_c_interface.o -std=c++11
cc c-main.c class.o class_c_interface.o -lstdc++ -o c-main
```

We have:

```bash
$ cat class_c_interface.cpp 
#include "class_c_interface.h"
#include "class.hpp"

extern "C" { /* otherwise there is a mismatch! The wll have different symbols */

Foo_c create_foo(int b) {
  return new Foo(b);
}
void free_foo(Foo_c f) {
  delete static_cast<Foo*>(f);
}
void print_foo(Foo_c f) {
  static_cast<Foo*>(f)->print();
}
void set_a(Foo_c f, int v) {
  static_cast<Foo*>(f)->get_a() = v;
};
int get_a(Foo_c f) {
  return static_cast<Foo*>(f)->get_a();
}
}
```

We need to write `#ifdef __cplusplus` 



You are able only to export non templated symbols, because `C` doesn't know templates! You have to write the `int` function, the `double` function, ecc ... → there are packages that does this, but they are not standard and they underneath do this thing

If `foo` was tmplated, we should write like this:

```
$ cat class_c_interface.cpp 
#include "class_c_interface.h"
#include "class.hpp"

extern "C" { /* otherwise there is a mismatch! The wll have different symbols */

Foo_c create_foo(int b) {
  return new Foo<int>(b);
}
void free_foo(Foo_c f) {
  delete static_cast<Foo<int>*>(f);
}
void print_foo(Foo_c f) {
  static_cast<Foo<int>*>(f)->print();
}
void set_a(Foo_c f, int v) {
  static_cast<Foo<int>*>(f)->get_a() = v;
};
int get_a(Foo_c f) {
  return static_cast<Foo<int>*>(f)->get_a();
}
}
```

Templates are not supported in `C`! We need to explicitly instantiate tehm!



## Python

You cannot call `C++` from `Python`! `Python` is written in `C ` so it doesn't know `C++`! If you want to use your `C++` interface it must me a shared library!

```bash
$ cd ../../05_ctypes/

$ ls
hello.c  main.py  Makefile

$ make
cc -shared -fpic -o libhello.so hello.c -std=c11
```

The file `main.py`

```python
#/usr/bin/env python3

from ctypes import *
dso = CDLL("./libhello.so") # import shared object on POSIX compatib$

## functions w/o args
dso.hello()


## strings
dso.repeat.argtypes = [c_char_p]
dso.repeat.restype = c_int
res = dso.repeat(b"ctypes are great") # use b to pass read-only variable → b transform the string in bytes!

# use create_string_buffer for a "mutable string"
buf = create_string_buffer(b"this could be modified")
dso.repeat(buf)


## arrays
size = 10
d_array = (c_double*size)()  # better do the allocation on the python side

for i in range(size):
    d_array[i] = i

array_sum = dso.array_sum

array_sum.argtypes = [POINTER(c_double), c_size_t] # note the use of POINTERS
array_sum.restype = c_double

print("the sum of d_array is", array_sum(d_array,size))

## structs
class data(Structure): # Python class that intherits from Structure
    _fields_ = [("i",c_int),
                ("name",c_char_p),
                ("energy",c_double)] # order is crucial:must be the same otherwise seg-fault

param = data(name=b"Alberto", energy=99.9, i=42)

#dso.use_by_value.argtypes = [data] # to be pedantic uncomment this line
dso.use_by_value(param) # default is by value

param.i=77
param.name=b"ciao ciao"

# dso.use_by_reference.argtypes = [POINTER(data)]
# dso.use_by_reference(param)
dso.use_by_reference(byref(param))

dso.set_energy.argtypes = [POINTER(data), c_double]

dso.set_energy(param, 32.45)

dso.use_by_value(param)
```

and

```bash
$ cat hello.c
#include <stdio.h>

void hello() {
  puts("Hello from shared lib");
}

int repeat(char* c) {
  printf("Cow say: %s\n", c);
  return 0;
}

double array_sum(const double* p, const size_t l) {
  double sum = 0;
  for (size_t i = 0; i < l; ++i)
    sum += p[i];
  return sum;
}

struct data {
  int i;
  char* name;
  double energy;
};

void use_by_value(struct data d) {
  printf("i=%d, name=%s, energy=%g\n", d.i, d.name, d.energy);
}

void use_by_reference(struct data* d) {
  printf("i=%d, name=%s, energy=%g\n", d->i, d->name, d->energy);
}

void set_energy(struct data* d, double e) {
  d->energy = e;
}
```



Python is a typed language, but the type is associated with the global variable, not to the named variable as in `C`

Write a `C` interface if you want to call a `C++` library in `Python`



## `Fortran` from `C++`

```bash
$ cd ../06_fortran/

$ ls
c-main.c  cpp-main.cpp  f-sum.f90  Makefile

$ cat f-sum.f90 

! sum up absolute of "num" integers in array "inp", store result in "asum" 
subroutine sum_abs(inp, num, asum)
  implicit none
  integer, intent(in) :: inp(*), num
  integer, intent(out) :: asum
  integer :: i,s

   s = 0
   do i=1,num
     s = s + abs(inp(i)); 
   end do
   asum = s;
end subroutine sum_abs

```

It's a `Fortran` function that makes the sum of an array.

```bash
$ make -B
cc c-main.c -c -o c-main.o
gfortran -c f-sum.f90 -o f-sum.o
cc c-main.o f-sum.o -o c-exe
c++ cpp-main.cpp -c -o cpp-main.o
c++ cpp-main.o f-sum.o -o cpp-exe

$ ./c-exe 
sum=10

$ nm f-sum.o
0000000000000000 T sum_abs_

$ cat c-main.c
#include <stdio.h>

#define NUM 5

void sum_abs_(int *, int *, int *); /* trailing underscore, pointers */

int main(int argc, char **argv) {
  int data[NUM], sum, num, i;

  num = NUM;
  for (i = 0; i < num; i++) {
    data[i] = i;
  }

  sum_abs_(data, &num, &sum);
  printf("sum=%d\n", sum);
  return 0;
}
```

`Fortran` appends an underscore in the functions' names and passes averything by reference: so pointers everywhere!





## Other

```bash
$ cd ../04_libdl/

$ ls
hello.c  main.c  Makefile

$ cat main.c
#include <dlfcn.h>

int main(int argc, char* argv[]) {
  void* handle; /* handle for dynamic object */
  void (*hi)(); /* function pointer for symbol */
  int (*rep)(char*);
  handle = dlopen("./libhello.so", RTLD_LAZY);
  if (handle) {
    hi = (void (*)())dlsym(handle, "hello");
    (*hi)();
    rep = (int (*)(char*))dlsym(handle, "repeat");
    rep("I dont't care what fox says");
    dlclose(handle);
  }
  return 0;
}

$ make -B
cc -shared -fpic -o libhello.so hello.c
cc -o main main.c -ldl

```

