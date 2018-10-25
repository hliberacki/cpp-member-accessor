#ifndef ACCESSOR_TESTS_FUNCTION_WRAPPER_HPP
#define ACCESSOR_TESTS_FUNCTION_WRAPPER_HPP

#include "test_helper.hpp"
#include <accessor/accessor.hpp>
#include <iostream>
#include <vector>
class Test
{
  void foo() {}
  int  bar(int, float) {}
  int & foobar(int&, float&, std::vector<int>, int*) {}

  template<typename T, typename... Args>
  T generic(T, )

};

bool checkSignatureBasic()
{
  using fooSig = void(Test::*)();
  return std::is_same<fooSig, ::accessor::FunctionWrapper<Test, void>::type>::value;
}

bool checkFunctionSignature()
{


}
int main()
{
  ::testHelper::validateTest(checkSignatureBasic());

  return ::testHelper::failedTests();
}

#endif // ACCESSOR_TESTS_FUNCTION_WRAPPER_HPP
