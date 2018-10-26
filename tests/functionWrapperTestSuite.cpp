#include "test_helper.hpp"
#include <accessor/accessor.hpp>
#include <iostream>
#include <vector>

class Test
{
  void foo() {}
  int bar(int, float) {}
  int & foobar(int&, float&, std::vector<int>, int*) {}

  template<typename T, typename... Args>
  T generic(T, Args...) {}

  void cfoo() const {}
};

bool checkSignatureBasic()
{
  using fooSig = void(Test::*)();
  return std::is_same<fooSig, ::accessor::FunctionWrapper<Test, void>::type>::value;
}

bool checkFunctionSignature()
{
  bool testResult = false;

  {
    using barSig = int(Test::*)(int, float);
    testResult = std::is_same<barSig,
                              ::accessor::FunctionWrapper<Test, int, int, float>::type>::value;
  }

  {
    using foobarSig = int&(Test::*)(int&, float&, std::vector<int>, int*);
    testResult = std::is_same<foobarSig,
                             ::accessor::FunctionWrapper<Test, int&, int&, float&,
                                                         std::vector<int>, int*>::type>::value;
  }

  return testResult;
}


template<typename T, typename... Args>
using genericSigInt = T(Test::*)(Args...);

bool checkTemplateFunctionSignature()
{
  bool testResult = false;

  {
    testResult = std::is_same<genericSigInt<int>,
                              ::accessor::FunctionWrapper<Test, int>::type>::value;
  }

  {
    testResult = std::is_same<genericSigInt<int, std::string, double, Test>,
                              ::accessor::FunctionWrapper<Test, int, std::string,
                                                          double, Test>::type>::value;
  }

  return testResult;
}

bool checkConstFunctionSignature()
{
  using cfooSig = void(Test::*)() const;
  return std::is_same<cfooSig, ::accessor::ConstFunctionWrapper<Test, void>::type>::value;
}

int main()
{
  ::testHelper::validateTest(checkSignatureBasic());
  ::testHelper::validateTest(checkFunctionSignature());
  ::testHelper::validateTest(checkTemplateFunctionSignature());
  ::testHelper::validateTest(checkConstFunctionSignature());

  return ::testHelper::failedTests();
}

