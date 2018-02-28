# MiniInterpreter

## Introduction

This project implements a very simple interpreter with the emphasis on ease of use and integration.

Features:
- Small Code footprint, standard C++11
- C-esque syntax
- Variable Types: float, string, boolean and one dimensional arrays of those.
- script functions can be defined.
- Easy to add function-calls to C++ functions

## State
in early development, check back in April, I'm coding.


## Example application


Hello world in script:

```c
#include "CWppInterpreter.h"
int main(int argc, char **argv)
{
  CMiniInterpreter interp;
  interp.InterpretCode("print(\"Hello Slartibartfast\n\");");
  return 0;
}
```

Compile it under Linux:

```bash
$ g++ --std=c++11 main.cpp CWppInterpreter.cpp -o Hello
$ ./HelloWorld
Hello Slartibartfast
$
```

## Script examples
```c
// the script needs a main function, it is executed first
function float main()
{
  float a = 3;
  float b = a + 2 * 5;
  print("Result is " string(b));  // note: this does not work yet
  foo(3 * a);
}

function float foo(float n)
{
  float vals[];
  pi = 3.1415;
  for ( i = 0; i < 180; i = i + 1) {
    vals[i] = sin(i/2/pi);
  }
  plot(vals);  // the idea : a GUI window pops up and displays the array graphicaly
  dump(vals);  // textual dump of the array or variable, style vals=[0,1,2,3,4 ...];
  dumpall();   // dumps all variables
}


```






