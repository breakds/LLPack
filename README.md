# [Low Level Package for C++](http://www.azraelplanet.org/wikipages/doku.php?id=projects:llpack:start)

## Introduction

Low Level Package (LLPack) is a C++ utility library built on top of the C++ Standard Library STL (and only STL). This project originates from my research project in Computer Vision, but is rather general-purpose. It is consists two components:

* [Lisp Parser](http://www.azraelplanet.org/wikipages/doku.php?id=projects:llpack:start#lisp_configuration_file_parser): An S-expression format configuration file parser.
* [Utilities](http://www.azraelplanet.org/wikipages/doku.php?id=projects:llpack:start#untilities): Macro syntax sugars, I/O Wrappers, timer, configuration file parser, etc.
* [Algorithms](http://www.azraelplanet.org/wikipages/doku.php?id=projects:llpack:start#algorithms_and_data_structures): Algorithms (sorting, random generator, etc) and Data Structures (heap, disjoint set, etc).


## Author

**BreakDS**

+ breakds@gmail.com
+ https://github.com/breakds

## Quick Start

All components come in the form of [header files](http://en.wikipedia.org/wiki/Header_file) (.hpp/.h). To use them, 
just include the corresponding header files into your program. Please make sure that the include path is
correctly configured so that LLPack can be located by the compiler.


Below is a step-by-step tutorial that creates a sample c++ program with using LLPack. It demonstrates how to 
use LLPack fixed size heap to maintain a list of top 3 closest city to Cornell University.

### Step 1

First, download the library and put it somewhere. Let's say the directory LLPack is under the path **/some/where/**.

### Step 2


Create the test.cpp file, as below:

```c++
#include <iostream>
#include <string>
#include "LLPack/algorithms/heap.hpp"


int main() {

  int K = 3; // we want top K closest cities
  
  // Create the ranker (fixed K-size heap)
  heap<int, std::string> ranker(K);


  // Adding the (Grade, Name) pairs
  ranker.add( 2, "Ithaca" );
  ranker.add( 814, "Madison" );
  ranker.add( 332, "Boston" );
  ranker.add( 1007, "Ames" );
  ranker.add( 876, "St. Louis" );

  // print out top K cities
  std::cout << "---------- Closest Cities ----------\n"; 
  for ( int i=0; i<K; i++ ) {
    std::cout << ranker[i] << "\n";
  }
  std::cout << "\n";

  // Adding a new city
  ranker.add( 222, "New York" );
  
  
  // print out the updated top K cities
  std::cout << "---------- Updated Closest Cities ----------\n"; 
  for ( int i=0; i<K; i++ ) {
    std::cout << ranker[i] << "\n";
  }
  std::cout << "\n";
  
  return 0;
}
```

### Step 3

Compile with (Assuming GCC)

```bash
g++ test.cpp -I/some/where -o test -std=c++0x
```

Note that c++0x is necessary since c++11 syntax is extensively used in LLPack.

### Step 4

Run the compiled program, and we will get:
```bash
---------- Closest Cities ----------
Madison
Ithaca
Boston

---------- Updated Closest Cities ----------
Boston
Ithaca
New York
```

## Lisence

This is free and unencumbered software released into the public domain.

Anyone is free to copy, modify, publish, use, compile, sell, or
distribute this software, either in source code form or as a compiled
binary, for any purpose, commercial or non-commercial, and by any
means.

In jurisdictions that recognize copyright laws, the author or authors
of this software dedicate any and all copyright interest in the
software to the public domain. We make this dedication for the benefit
of the public at large and to the detriment of our heirs and
successors. We intend this dedication to be an overt act of
relinquishment in perpetuity of all present and future rights to this
software under copyright law.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

For more information, please refer to <http://unlicense.org/>


