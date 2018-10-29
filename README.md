
# Acessor
Header only, fully template based library which enables accessing private data members. Techniques used by this library to achive its purpouse are fully legal and allowed by the standard. 
Library is based on __Explicit instantiation__ of __class template instantion__.

>Explicit instantiation definitions ignore member access specifiers: parameter types and return types may be private.

_source: https://en.cppreference.com/w/cpp/language/class_template_

[Here](https://github.com/insooth/insooth.github.io/blob/master/accessing-private-members.md) can be found article by Krzysztof Ostrowski, describing how this technique has been implemented.

## Motivation

This library is not meant to break any C++ designe rules, even though it's fully legal from standard point of view. Purpouse of this library is to use it when neccesarry within tests. Code shall be written in the way that it can be later tested, but as we all know in most cases and especially it applies for legacy code, there are situations where one need to access private member and no mocking can be applied anymore.

In situations like that provided technique is far better than common `#define private public`, using `friend` keyword or even flag `no-access-control` for gcc. 

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
## Usage

Full set of examples is enable [here](https://github.com/hliberacki/cpp-member-accessor/tree/master/examples). Below there is only quick _getting started_ section

There are two ways of using this library, first is using straight library API and second is by calling Macro which calls library API. 
Both ways will be presented, choose which one is better for you, yet both will use the same test class to access its data.

```cpp
class Test
{
  void foo() { std::cout << "private method: Foo" << '\n'; }

  int getSum(int first, int second ) const { return first + second; }

  template<typename T>
  T max(T& lhs, T& rhs) { return (lhs > rhs) ? lhs : rhs; }
  
  int mFooBar {1};
};
```

### Macroless

First step for accessing private data, is to create own type or alias which will be further passed for accessing functions.

```cpp
struct TestFoo : ::accessor::FunctionWrapper<Test, void>;
struct TestFooBar : ::accessor::MemberWrapper<Test, int>;
```
Or
```cpp
using TestFoo = ::accessor::FunctionWrapper<Test, void>;
using TestFooBar = ::accessor::MemberWrapper<Test, int>;
```

Both ways are equal. `FunctionWrapper` takes types `<BaseClass, FunctionReturnType, FunctionArgsTypes...>`
`MemberWrapper` works similar to `FunctionWrapper` it takes types `<BaseClass, MemberType>`

When the type for accessing data member has been created, __explicit template instantantion__ shall be used

```cpp
using TestFoo = ::accessor::FunctionWrapper<Test, void>;
template class ::accessor::MakeProxy<TestFoo, &Test::foo>;

using TestFooBar = ::accessor::MemberWrapper<Test, int>;
template class ::accessor::MakeProxy<TestFoo, &Test::mFooBar>;
```

`MakProxy` takes as parameters `<CreatedType, MemberAddress>`

After those steps we can simply call private `foo` method of class `Test`

```cpp
Test t;
::accessor::callFunction<TestFoo>(t);
::accessor::accessMember<TestFoo>(t);
```

`callFunction` takes any `Test` object which has `Test::foo` method to call, and variadic arguments needed for that method.
`accessMember` works as `callFunction` yet it return `std::ref` to private data member of class `Test`

Examples of instantion and calling for rest of Test class methods.

```cpp
using TestGetSum = ::accessor::ConstFunctionWrapper<Test, int, int, int>;
template class ::accessor::MakeProxy<TestGetSum, &Test::getSum>;

template<typename T>
using TestMax = ::accessor::FunctionWrapper<Test, T, T&, T&>;
template class ::accessor::MakeProxy<TestMax<int>, &Test::max>;
template class ::accessor::MakeProxy<TestMax<uint32_t>, &Test::max>;

....

int main()
{
  int result = ::accessor::callFunction<TestGetSum>(t, 1, 1);
  result = ::accessor::callFunction<TestMax<int>>(t, 10, 20);
  uint32_t res = ::accessor::callFunction<TestMax<uint32_t>>(t, 100u, 200u);
  return 0;
}
```

### With Macros

If you are not happy with need of explicity calling template instantiation, then there are also macros which does it for you

```cpp
FUNCTION_ACCESSOR(TestFoo, Test, foo, void) // Test::foo
CONST_FUNCTION_ACCESSOR(TestSum, Test, getSum, int, int, int) //Test::getSum
FUNCTION_ACCESSOR(TestMaxInt, Test, max, int, int&, int&) //Test::max<int>
FUNCTION_ACCESSOR(TestMaxUInt, Test, max, uint32_t, uint32_t&, uint32_t&) //Test::max<uint32_t>
MEMBER_ACCESSOR(TestFooBar, Test, mFooBar, int) // Test::mFooBar
```

Below is what those Macros shall be satisfied with

```cpp
FUNCTION_ACCESSOR(TypeForAccessing, BaseClass, nameOfMemberToAccess, returnType, functionArgumentTypes...)
CONST_FUNCTION_ACCESSOR(TypeForAccessing, BaseClass, nameOfMemberToAccess, returnType, functionArgumentTypes...)
MEMBER_ACCESSOR(TypeForAccessing, BaseClass, nameOfMemberToAccess, MemberType)
```

Rest is done the very same way as it was done without macros, using `callFunction` and `accessMember`

## License

[MIT License](https://github.com/hliberacki/cpp-member-accessor/blob/master/LICENSE)
