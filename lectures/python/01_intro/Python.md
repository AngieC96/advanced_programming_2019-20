# Python

```bash
angela@angipc:~/Documenti/Advanced Programming/advanced_programming_2019-20/lectures/python/01_intro$ python3 --version
Python 3.6.9
angela@angipc:~/Documenti/Advanced Programming/advanced_programming_2019-20/lectures/python/01_intro$ python3
Python 3.6.9 (default, Nov  7 2019, 10:44:02) 
[GCC 8.3.0] on linux
Type "help", "copyright", "credits" or "license" for more information.
>>> 2*4
8
>>> 3/2
1.5
>>> exit
Use exit() or Ctrl-D (i.e. EOF) to exit
>>> exit()
```

It doesn't remember the commands you wrote!
The division is always **`double`**! Instead in Python2 it is an **`integer`**:

```bash
$ python2
Python 2.7.15+ (default, Oct  7 2019, 17:39:04) 
[GCC 7.4.0] on linux2
Type "help", "copyright", "credits" or "license" for more information.
>>> 3/2
1
>>>
```

In Python2:

```bash
$ emacs hello.py
	print "Hello world!"
$ python3 hello.py
```

In Python3: (print è passato da essere un operatore ad essere una funzione!)

```bash
$ emacs hello.py
	print("Hello world!")
$ python3 hello.py
Hello world!
```

Specify the version of the interpreter you want to use! In `hello.py` put:

```
#!/usr/bin/env python3

print("Hello world!")
```

Linux reads the first bites of a file to decide the type of file, not the extension (that's Windows)!



Let's create the file `secret.txt` (`$ nano secret.txt`) that contains:

```bash
#!/bin/rm

you will never read this
```

Then make:

```bash
$ chmod u+x secret.txt
$ ls
01_jupyter_intro.ipynb  04_tuples.ipynb        07_functions.ipynb  readme.md
02_surving_kit.ipynb    05_dictionaries.ipynb  hello.py            secret.txt
03_lists.ipynb          06_sets.ipynb          Python.md
$ ./secret.txt
$ ls
01_jupyter_intro.ipynb  05_dictionaries.ipynb  Python.md
02_surving_kit.ipynb    06_sets.ipynb          readme.md
03_lists.ipynb          07_functions.ipynb
04_tuples.ipynb         hello.py
```

It invokes that command on this file! So it erases itself when you run it.

---

```bash
$ file hello.py 
hello.py: ASCII text
```

Let's see another way to execute files in Python:

```bash
$ chmod u+x hello.py
$ ls
01_jupyter_intro.ipynb  05_dictionaries.ipynb  Python.md
02_surving_kit.ipynb    06_sets.ipynb          readme.md
03_lists.ipynb          07_functions.ipynb
04_tuples.ipynb         hello.py
$ ls -lrt
-rwxr--r-- 1 angela angela    46 dic 10 17:14 hello.py*
$ ./hello.py
Hello world!
```



## Jupyter notebook

```
$ conda activate lab
$ jupyter-notebook
# RECOMMENDED
$ jupyter-lab
```

jupyter notebook → Combine markdown code and actual code in different languages