
# Acessor
Header only, fully template based library which enables accessing private data members. Techniques used by this library to achive its purpouse are fully legal and allowed by the standard. 
Library is based on __Explicit instantiation__ of __class template instantion__.

>Explicit instantiation definitions ignore member access specifiers: parameter types and return types may be private.

_source: https://en.cppreference.com/w/cpp/language/class_template_

[Here](https://github.com/insooth/insooth.github.io/blob/master/accessing-private-members.md) can be found article by Krzysztof Ostrowski, describing how this technique has been implemented.

## Installation

Installation is done using CMake
```
mkdir build
cd build
cmake ..
make && make install
```

## Building examples

There is set of mini [examples](https://github.com/hliberacki/cpp-member-accessor/tree/master/examples), which shows how various data members and methods can be accessed. To build them, additional CMake flag shall be passed.

```
cmake -DEXAMPLES=1 ..
make
```

## Running tests

There is set of [tests](https://github.com/hliberacki/cpp-member-accessor/tree/master/tests) using only CMake [CTest](https://cmake.org/cmake/help/v3.0/manual/ctest.1.html).

```
make test
```

