# intro
Those code is mainly written during reading book"A Tour of C++  2e", served as C++ syntax/feature review, developed & test under Linux, using VS Code

Most code follow the C++17 standard, to find out the C++ standard supported by your compiler

```bash
$ g++ -v
$ man g++
    -std=
    c++1z
```

# dump the class layout

```bash
$ g++ -fdump-class-hierarch Container.h  //the file where class is defined
$ cat Container.h.002t.class 

```

