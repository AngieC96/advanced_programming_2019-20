# Libraries



### Compiling

Distinguish implementation (in file `.cc`) from definition (in file `.h`).

header → file `.h` → collected inside a folder named `include` because they are meant to be included (include means to copy and paste the content of the file)

```bash
$ cd lectures/c++/09_symbols/01_greetings_library/

$ ls
include  Makefile  src

$ tree
.
├── include
│   ├── conclusion.h
│   └── greetings.h
├── Makefile
└── src
    ├── conclusion.cc
    └── greetings.cc

2 directories, 5 files

$ cat include/greetings.h 
#ifndef __GREETINGS__
#define __GREETINGS__

void print_greetings();

#endif

$ cat src/greetings.cc 
#include <greetings.h>
#include <iostream>

void print_greetings() {
#ifdef ITALIANO
  std::cout << "Benvenuti al corso di Advanced Programming\n";
#endif

#ifdef ENGLISH
  std::cout << "Welcome to the Advanced Programming course\n";
#endif
}
```

`ITALIANO` and `ENGLISH` are **macros** used when you compile! They enable or disable some part of the code

```
$ cat include/conclusion.h 
#ifndef __CONCLUSION__
#define __CONCLUSION__

void print_conclusion();

#endif
```

prototype of the function, while the .. contains the definition of the function.

Goal: generate a shared library

two types of library: **static** or **dynamic** →shared is preferred!

To compile, two steps that have their own flags:

- compile → `conclusion.cc` and `greeting.cc` → it's the slowest part, so try to not do it when it is not necessary
- link → 

| src | → | .o | → | bin| (binary, not executable because it doesn't have a main)

```bash
$ c++ -c src/greetings.cc
src/greetings.cc:1:10: fatal error: greetings.h: File o directory non esistente
 #include <greetings.h>
          ^~~~~~~~~~~~~
compilation terminated.
```

We need to tell the compiler where to find the headers!

```bash
$ c++ -c src/greetings.cc -I include
# $ c++ -c src/greetings.cc -I include -I another_folder
```

```bash
$ ls
greetings.o  include  Makefile  src

$ c++ -c src/conclusion.cc -I include

$ ls
conclusion.o  greetings.o  include  Makefile  src
```

Position independent code

The computer need to know where a symbol is located → offset from 0

The addresses of the symbols are not known, so you should use **position independent code** → FLAG `-fPIC`

```bash
$ c++ -c src/conclusion.cc -I include -fPIC
$ c++ -c src/greetings.cc -I include -fPIC
```

Convention: libraries starts with **lib** and ends with **.so**

```bash
$ c++ greetings.o conclusion.o -shared -o libgreetings.so
$ ls
conclusion.o  greetings.o  include  libgreetings.so  Makefile  src
```

So now we have our shared library!



But how can we do if we have a huge number of files to compile? If we have 10 files we have to repeat the almost exact line 10 times!

**Solution:** makefiles!

### Makefiles

There can be 3 thing in a makefile:

macros → when you define a variable: VAR = value		#macro, use $(VAR) to access the value [important: use ROUND parenthesis]

targets → we will see

comments → made with `#`

```bash
CXX = c++
LANG = ENGLISH # to know if we use ITALIAN or ENGLISH
```

To compile with a macro:

```bash
$ c++ -c src/conclusion.cc -I include -fPIC -D ITALIANO
```

You can put or not the space after `-D`.

target: dep1 dep2 ... depN
	<tab>		action
	<tab>		action2

The tab is really important, if they are spaces it doesn't work!

Each instruction is executed in a different sub-shell → if you want to write a file write it on a single line!!!

make → the first rule is executed! (if you don't specify the name of a target)

for target → write make + the name of the target

a name with the target is generated

```bash
SRC = src/greetings.cc src/conclusion.cc # contains all the sources files
OBJ = $(SRC:.cc=.o) # list of all the source files but with the change of .o instead of .cc
```

```bash
all: libgreetings.so
```

`all` → target that is first executed. If the file `libgreetings.so` exists I'm done (not true, check is `libgreetings.so` is up to date), if not how can I generate it? With the following lines!

```bash
libgreetings.so: $(OBJ)
	$(CXX) -shared -o $@ $^
```
Check is a target is up to date or not: compares the time-stamp of the `libgreetings.so` is equal or not to the time-stamp of the dependencies, so you don't recompile if you don't have to (so you cannot launch the compilation by mistake after you just compiled it)


DON'T DO GLOBBING!!!

`$@` is the name of the target, `$^` is a string that contains all the dependencies → useful to avoid code repetition!

`%o:%cc` → whatever `.o` depends on whatever `.cc`

```bash
%.o:%.cc
	$(CXX) -fpic -D$(LANG) -o $@ -c $< -Iinclude
```

`$(ccx)  -c $< $(cxxflags) → $@`

**Rule:** when you use % the file to be compiled is `$<`

Let's see the makefile!

```bash
$ make
c++ -fpic -DENGLISH -o src/greetings.o -c src/greetings.cc -Iinclude
c++ -fpic -DENGLISH -o src/conclusion.o -c src/conclusion.cc -Iinclude
c++ -shared -o libgreetings.so src/greetings.o src/conclusion.o

$ make
make: Nessuna operazione da eseguire per "all".

$ touch src/greetings.cc # because I'm lazy, yust to let the compiler thing that I changed it

$ make
c++ -fpic -DENGLISH -o src/greetings.o -c src/greetings.cc -Iinclude
c++ -shared -o libgreetings.so src/greetings.o src/conclusion.o
```

He recompiles only the file that was changed and then it links it.

What if I change the header?

```
src/greetings.o: include/greetings.h
```

You need to regenerate `libgreeting.so` if the file  `include/greetings.h` was changed

You can build the list of dependencies in many lines! The order of the rules doesn't matter, so you can refer to other targets before you have defined them (but try to keep the makefile readable!)

If I put:

```
#src/greetings.o: include/greetings.h
```

So when compiling

```
$ touch include/greetings.h
$ make
make: Nessuna operazione da eseguire per "all".
```

Uncommenting 

```bash
src/greetings.o: include/greetings.h
```

we have

```bash
$ make
c++ -fpic -DENGLISH -o src/greetings.o -c src/greetings.cc -Iinclude
c++ -shared -o libgreetings.so src/greetings.o src/conclusion.o
```

 → checks if a file named `clean` is present or not. Warning: if I have a file named `clean`

```bash
clean:
	@rm -f *~ */*~ libgreetings.so src/*.o
```

The `@` is for avoiding to print all the commands executed on screen

`.PHONY: clean all format` → I don't check if ... is .. or not, I just execute the action

You use `.PHONY` to flag targets that do not represent physical files on the system. A problem arises if you have a file named `clean` and you didn't used `.PHONY`: the compiler doesn't know what to do!

```bash
CXX = c++
LANG = ENGLISH

SRC = src/greetings.cc src/conclusion.cc
OBJ = $(SRC:.cc=.o)

all: libgreetings.so

.PHONY: all

libgreetings.so: $(OBJ)
	$(CXX) -shared -o $@ $^

%.o:%.cc
	$(CXX) -fpic -D$(LANG) -o $@ -c $< -Iinclude

src/greetings.o: include/greetings.h

src/conclusion.o: include/conclusion.h

.PHONY: format

format: $(SRC) include/greetings.h include/conclusion.h
	@clang-format -i $^ 2>/dev/null || echo "Please install clang-format to run this commands"

clean:
	@rm -f *~ */*~ libgreetings.so src/*.o

#.PHONY: clean all format
.PHONY: clean
```

### Flags of make

`man make`:

```bash
$ make -B
c++ -fpic -DENGLISH -o src/greetings.o -c src/greetings.cc -Iinclude
c++ -fpic -DENGLISH -o src/conclusion.o -c src/conclusion.cc -Iinclude
c++ -shared -o libgreetings.so src/greetings.o src/conclusion.o
```

`-B` to force the recompilation → Doesn't check the typedef

```
make -j 9
```

9 → number of processes plus one → allows to compile things in parallel

```bash
make -n
```

It prints all the commands that it would execute if you launch it but it doesn't launch them.

```bash
format: $(SRC) include/greetings.h include/conclusion.h
	@clang-format -i $^ 2>/dev/null || echo "Please install clang-format to run this commands"
```

→ To indent all the files properly

All the macros that you define should be put in a header that is include in every file.

## Linking

```bash
$ cd ../02_link_library/

$ ls
include  main.cc  Makefile  src

$ tree
.
├── include
│   ├── date.h
│   └── student.h
├── main.cc
├── Makefile
└── src
    ├── date.cc
    └── student.cc

2 directories, 6 files
```

How can I compile things and how can I link them?

```
$nano main.cc
```

```c++
#include <iostream>
#include <student.h>
#include <date.h>
#include <greetings.h>
#include <conclusion.h>

int main()
{
  print_greetings();
  date d {5,12,1986};

  std::cout << d << std::endl;

  student s {"alberto", {4, 5, 1492}, 3.1};
  std::cout << s << std::endl;

  print_conclusion();

  return 0;
}
```

c++ is a static compiled language → it needs to know at compile time all the symbols! →  I have to include the headers!

**Compilation:** I generate the `.o` files

```bash
$ c++ -c -I include -I ../01_greetings_library/include/ main.cc

$ c++ -c -I include -I ../01_greetings_library/include/ src/date.cc

$ c++ -c -I include -I ../01_greetings_library/include/ src/student.cc

$ ls
date.o  include  main.cc  main.o  Makefile  src  student.o
```

`-I` the path where I should find the headers

**Linking:** 

```bash
$ c++ *.o -l greetings -L ../01_greetings_library/
```

`-l` to link something named `greetings.sh` or `greetings.so`

`-L` the path where it should look for libraries!

```bash
$ ls
a.out  date.o  include  main.cc  main.o  Makefile  src  student.o
```

But if we try to execute:

```bash
$ ./a.out 
./a.out: error while loading shared libraries: libgreetings.so: cannot open shared object file: No such file or directory
```

He doesn't know where to find `greddings` library!

`LD_LIBRARY_PATH` where to find the libraries!

```bash
$ ldd a.out
	linux-vdso.so.1 (0x00007fffe67e8000)
	libgreetings.so => not found
	libstdc++.so.6 => /usr/lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007fdccac25000)
	libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007fdccaa0d000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007fdcca61c000)
	libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007fdcca27e000)
	/lib64/ld-linux-x86-64.so.2 (0x00007fdccb1b1000)
```

To define an environment variable use `export`

```
$ export LD_LIBRARY_PATH=../01_greetings_library/:$LD_LIBRARY_PATH
```

I prepend my library! (the libraries are speared by `:`)

```bash
$ ldd a.out 
	linux-vdso.so.1 (0x00007fff668ff000)
	libgreetings.so => ../01_greetings_library/libgreetings.so (0x00007f420d293000)
	libstdc++.so.6 => /usr/lib/x86_64-linux-gnu/libstdc++.so.6 (0x00007f420cf0a000)
	libgcc_s.so.1 => /lib/x86_64-linux-gnu/libgcc_s.so.1 (0x00007f420ccf2000)
	libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f420c901000)
	libm.so.6 => /lib/x86_64-linux-gnu/libm.so.6 (0x00007f420c563000)
	/lib64/ld-linux-x86-64.so.2 (0x00007f420d698000)
```

Now he is able to find my library!

```bash
$ ./a.out 
Welcome to the Advanced Programming course
5/12/1986

Student's name: alberto
alberto's date of birth 4/5/1492
alberto's average: 3.1

See you on Thursday
```

## Update libraries

```
CXX = c++
LANG = ITALIANO
...
```

I force recompilation

```bash
$ cd ../01_greetings_library/

$ make -B
c++ -fpic -DITALIANO -o src/greetings.o -c src/greetings.cc -Iinclude
c++ -fpic -DITALIANO -o src/conclusion.o -c src/conclusion.cc -Iinclude
c++ -shared -o libgreetings.so src/greetings.o src/conclusion.o
```

And now:

```bash
$ cd ../02_link_library/

$ ./a.out
Benvenuti al corso di Advanced Programming
5/12/1986

Student's name: alberto
alberto's date of birth 4/5/1492
alberto's average: 3.1

Ci vediamo giovedì
```

### Install a library

How do you install a library?

```
$ ./config

$ make

$ sudo make install
```

Why do we need `sudo`? Because all the headers will be put in the folder `/usr/local/include`, all the libraries in `/lib` or `/lib64` and all the binaries in `/bin`.

Since you may need different versions of the same libraries, make different folders!! Don't install everything in always the same folder!!! When you call `./config` specify `--prefix=/path/to/smart/place` to replace the prefix `/user/local/`.

Example: `./config --prefix=/opt/firefox_3.47` and the headers will be in `/opt/firefox_3.47/include`, the libraries will be in `/opt/firefox_3.47/lib` ecc

Ulysses: `/u/shared/modules/mpi/openmp/1.8.3/gnu` or `/u/shared/modules/mpi/openmp/1.8.3/intel` or `/u/shared/modules/libraries/mkl`

Let's have a look at the `Makefile`:

```bash
EXE = ap
GDIR=../01_greetings_library

LDFLAGS = -lgreetings -L $(GDIR)
CXX = c++
CXXFLAGS = -I include -I $(GDIR)/include -std=c++11

all: $(EXE)

%.o: %.cc
        $(CXX) -c $< -o $@ $(CXXFLAGS)


$(EXE): main.o src/date.o src/student.o
        $(CXX) $^ -o $(EXE) $(LDFLAGS)

main.o: src/student.o src/date.o

src/date.o: include/date.h

src/student.o: include/student.h

format: $(SRC) include/date.h include/student.h
        @clang-format -i $^ 2>/dev/null || echo "Please install clang-for$

clean:
        rm -rf src/*.o *.o $(EXE) */*~ *~ a.out*

.PHONY: clean all format
```

Now

```bash
$ cd ../02_link_library/

$ ./ap
Benvenuti al corso di Advanced Programming
5/12/1986

Student's name: alberto
alberto's date of birth 4/5/1492
alberto's average: 3.1

Ci vediamo giovedì
```

```
CXXFLAGS = -I include -I $(GDIR)/include -std=c++11 -Wl,-rpath,$(GDIR)
```

`-Wl,-rpath,$(GDIR)` to say: `-Wl` instruction for the compiler, `-rpath` path to be checked at run-time, `$(GDIR)`

```
$ make -B
```

`readelf -D`

```bash
$ readelf -D
Uso: readelf <opzioni> file-elf
 Visualizza informazioni sul contenuto dei file in formato ELF
 Options are:
  -a --all               Equivalent to: -h -l -S -s -r -d -V -A -I
  -h --file-header       Display the ELF file header
  -l --program-headers   Display the program headers
     --segments          An alias for --program-headers
  -S --section-headers   Display the sections' header
     --sections          An alias for --section-headers
  -g --section-groups    Display the section groups
  -t --section-details   Display the section details
  -e --headers           Equivalent to: -h -l -S
  -s --syms              Display the symbol table
     --symbols           An alias for --syms
  --dyn-syms             Display the dynamic symbol table
  -n --notes             Display the core notes (if present)
  -r --relocs            Display the relocations (if present)
  -u --unwind            Display the unwind info (if present)
  -d --dynamic           Display the dynamic section (if present)
  -V --version-info      Display the version sections (if present)
  -A --arch-specific     Display architecture specific information (if any)
  -c --archive-index     Display the symbol/file index in an archive
  -D --use-dynamic       Use the dynamic section info when displaying symbols
  -x --hex-dump=<number|name>
                         Dump the contents of section <number|name> as bytes
  -p --string-dump=<number|name>
                         Dump the contents of section <number|name> as strings
  -R --relocated-dump=<number|name>
                         Dump the contents of section <number|name> as relocated bytes
  -z --decompress        Decompress section before dumping it
  -w[lLiaprmfFsoRtUuTgAckK] or
  --debug-dump[=rawline,=decodedline,=info,=abbrev,=pubnames,=aranges,=macro,=frames,
               =frames-interp,=str,=loc,=Ranges,=pubtypes,
               =gdb_index,=trace_info,=trace_abbrev,=trace_aranges,
               =addr,=cu_index,=links,=follow-links]
                         Display the contents of DWARF debug sections
  --dwarf-depth=N        Non visualizza i DIE alla profondità N o superiore
  --dwarf-start=N        Visualizza i DIE partendo da N, alla stessa profondità
                         o superiore
  -I --histogram         Visualizza l'istogramma delle lunghezze degli elenchi dei bucket
  -W --wide              Permette all'output di superare gli 80 caratteri di ampiezza
  @<file>                Legge le opzioni dal <file>
  -H --help              Visualizza questo aiuto
  -v --version           Visualizza il numero di versione di readelf
```

`readelf -D -a ap | less`

```
Intestazione ELF:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  Classe:                            ELF64
  Dati:                              complemento a 2, little endian
  Versione:                          1 (current)
  SO/ABI:                            UNIX - System V
  Versione ABI:                      0
  Tipo:                              DYN (file oggetto condiviso)
  Macchina:                          Advanced Micro Devices X86-64
  Versione:                          0x1
  Indirizzo punto d'ingresso:               0xdb0
  Inizio intestazioni di programma          64 (byte nel file)
  Inizio intestazioni di sezione:          12496 (byte nel file)
  Flag:                              0x0
  Dimensione di questa intestazione: 64 (byte)
  Dimens. intestazioni di programma:  56 (byte)
  Numero intestazioni di programma:  9
  Dimens. intestazioni di sezione:   64 (byte)
  Numero di intestazioni di sezione: 30
  Indice della tabella di stringhe delle intestazioni di sezione: 29

Intestazioni di sezione:
  [N°] Nome              Tipo             Indirizzo         Offset
       Dimensione        DimEnt           Flag   Link  Info  Allin
  [ 0]                   NULL             0000000000000000  00000000
       0000000000000000  0000000000000000           0     0     0
  [ 1] .interp           PROGBITS         0000000000000238  00000238
       000000000000001c  0000000000000000   A       0     0     1
  [ 2] .note.ABI-tag     NOTE             0000000000000254  00000254
       0000000000000020  0000000000000000   A       0     0     4
  [ 3] .note.gnu.build-i NOTE             0000000000000274  00000274
       0000000000000024  0000000000000000   A       0     0     4
  [ 4] .gnu.hash         GNU_HASH         0000000000000298  00000298
       000000000000003c  0000000000000000   A       5     0     8
  [ 5] .dynsym           DYNSYM           00000000000002d8  000002d8
       00000000000002d0  0000000000000018   A       6     1     8
```

If I comment `-Wl,-rpath,$(GDIR)` there is no `RUNPATH`



------

## Internal - external

```bash
$ cd lectures/c++/09_symbols/

$ cd 03_internal_external/

$ ls
circle.cc  constants.h  greek.cc  main.cc  Makefile

$ cat main.cc 
#include "constants.h"
#include <iostream>

double area_circle(const double);
double golden_ratio(const double);
extern int circle_counter;

int main() {
  std::cout << area_circle(1) << std::endl;
  std::cout << area_circle(2) << std::endl;

  std::cout << golden_ratio(1) << std::endl;

  std::cout << circle_counter << std::endl;
  std::cout << "[main] pi = " << pi << std::endl;

  return 0;
}
```

If we comment line 6 `extern int circle_counter;`:

```bash
$ make
g++ -c greek.cc -o greek.o -g -std=c++11 -Wall -Wextra
g++ -c main.cc -o main.o -g -std=c++11 -Wall -Wextra
main.cc: In function ‘int main()’:
main.cc:15:16: error: ‘circle_counter’ was not declared in this scope
   std::cout << circle_counter << std::endl;
                ^~~~~~~~~~~~~~
Makefile:13: recipe for target 'main.o' failed
make: *** [main.o] Error 1
```

If I remove the keyword `extern`:

```
$ make
g++ -c main.cc -o main.o -g -std=c++11 -Wall -Wextra
g++ -c circle.cc -o circle.o -g -std=c++11 -Wall -Wextra
g++ -o exe greek.o main.o circle.o
circle.o:/home/angela/Documenti/Advanced Programming/advanced_programming_2019-20/lectures/c++/09_symbols/03_internal_external/circle.cc:4: definizione multipla di "circle_counter"
main.o:/home/angela/Documenti/Advanced Programming/advanced_programming_2019-20/lectures/c++/09_symbols/03_internal_external/main.cc:7: definito qui per la prima volta
collect2: error: ld returned 1 exit status
Makefile:10: recipe for target 'exe' failed
make: *** [exe] Error 1
```

→ `circle.cc` contains a variable named `circle_counter`, so you have a double definition!

If I leave the line as `extern int circle_counter;`:

```bash
$ make
g++ -c greek.cc -o greek.o -g -std=c++11 -Wall -Wextra
g++ -c main.cc -o main.o -g -std=c++11 -Wall -Wextra
g++ -c circle.cc -o circle.o -g -std=c++11 -Wall -Wextra
g++ -o exe greek.o main.o circle.o
```

It is in a different compilation unit! How to solve this problem?

`int circle_counter` the compiler will be happy but the linker not! → duplication of symbols!

```bash
$ make -n
g++ -c greek.cc -o greek.o -g -std=c++11 -Wall -Wextra
g++ -c main.cc -o main.o -g -std=c++11 -Wall -Wextra
g++ -c circle.cc -o circle.o -g -std=c++11 -Wall -Wextra
g++ -o exe greek.o main.o circle.o
```

 

`include` mean **copy and paste**!!! So the 

`extern` → this item is defined in a different compilation unit, the linker will find it!

`static` in front of a global symbol means internal linkage (a part of the warnings it works) → each compilation unit has its own copy of that variable. I can change the value of a static (= an internal linkage) variable

`static` can be seen as the opposite of a global variable.

c++ → `const` and `constexpr` implies `static`(= internal linkage) → in c NO!!!!! You have to write `static const`

With `constexp` you require that the computation is done at compile time → you can trigger a little more optimization!



```
$ nm -C greek.o
                 U __cxa_atexit
                 U __dso_handle
                 U _GLOBAL_OFFSET_TABLE_
00000000000000ac t _GLOBAL__sub_I__Z12golden_ratiod
0000000000000000 T golden_ratio(double)
0000000000000063 t __static_initialization_and_destruction_0(int, int)
0000000000000000 r pi
0000000000000008 r phi
                 U std::ostream::operator<<(double)
                 U std::ostream::operator<<(std::ostream& (*)(std::ostream&))
                 U std::ios_base::Init::Init()
                 U std::ios_base::Init::~Init()
                 U std::cout
                 U std::basic_ostream<char, std::char_traits<char> >& std::endl<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&)
0000000000000010 r std::piecewise_construct
0000000000000000 b std::__ioinit
                 U std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*)
```

`nm` → tool to read the symbols defined in a binary. Lower case → internal linkage, upper case → external linkage. t: text=functions

```bash
$ nm -C circle.o
0000000000000000 B circle_counter
                 U __cxa_atexit
                 U __dso_handle
                 U _GLOBAL_OFFSET_TABLE_
00000000000000c0 t _GLOBAL__sub_I_circle_counter
0000000000000000 T area_circle(double)
0000000000000077 t __static_initialization_and_destruction_0(int, int)
0000000000000000 r pi
0000000000000008 r phi
                 U std::ostream::operator<<(double)
                 U std::ostream::operator<<(std::ostream& (*)(std::ostream&))
                 U std::ios_base::Init::Init()
                 U std::ios_base::Init::~Init()
                 U std::cout
                 U std::basic_ostream<char, std::char_traits<char> >& std::endl<char, std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&)
0000000000000010 r std::piecewise_construct
0000000000000004 b std::__ioinit
                 U std::basic_ostream<char, std::char_traits<char> >& std::operator<< <std::char_traits<char> >(std::basic_ostream<char, std::char_traits<char> >&, char const*)
```





`static` → 3 meanings: create a static variable inside a scope of a function, static member creates a ... and they are not part of the class (they not occupy memory when you instantiate objects)





```bash
$ cat scr1.cc

$ cat src2.cc

$ nano func.h

$ cat main.cc
```



### Classes

```bash
$ cat class.h

$ cat src1.cc
```





If you don't have many many files, keep all the templates into a header → good advice, all the templates are safe (don't compile)

```bash
$ cat func.h

$ make
```





```bash
$ g++ src2.o src1.o main.o
```

