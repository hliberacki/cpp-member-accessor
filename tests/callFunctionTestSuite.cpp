//************************************************************************************
// cpp-member-accessor
//
// Copyright (c) 2017- Hubert Liberacki <hliberacki@gmail.com>
//
// SPDX-License-Identifier: MIT
// Project home: https://github.com/hliberacki/cpp-member-accessor
//************************************************************************************

#include "test_helper.hpp"
#include <accessor/accessor.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <stdint.h>

class Test
{
public:
  Test()
  {
    mVisitedMethods.emplace("foo", 0);
    mVisitedMethods.emplace("getSum", 0);
    mVisitedMethods.emplace("max", 0);
  }

  int getMethodVisitedCounter(std::string methodName)
  {
    auto found = mVisitedMethods.find(methodName);
    return (found != std::end(mVisitedMethods)) ? found->second : -1;
  }

private:
  void incrementMethodVisitedCounter(std::string methodName)
  {
    auto found = mVisitedMethods.find(methodName);
    if (found != std::end(mVisitedMethods))
      ++found->second;
  }

  void foo() { incrementMethodVisitedCounter("foo"); }

  int getSum(int first, int second )
  {
    incrementMethodVisitedCounter("getSum");
    return first + second;
  }

  template<typename T>
  T max(const T& lhs, const T& rhs)
  {
    incrementMethodVisitedCounter("max");
    return (lhs > rhs) ? lhs : rhs;
  }

  std::map<std::string, int> mVisitedMethods;
};


using TestFoo = ::accessor::FunctionWrapper<Test, void>;
template class ::accessor::MakeProxy<TestFoo, &Test::foo>;

bool callOnceSimpleFoo()
{
  Test t;
  ::accessor::callFunction<TestFoo>(t);
  return (t.getMethodVisitedCounter("foo") == 1);
}

bool callMultipleSimpleFoo()
{
  Test t;
  int callsNumber = 10;

  for (int i = 0; i < callsNumber; ++i )
  {
    ::accessor::callFunction<TestFoo>(t);
  }

  return (t.getMethodVisitedCounter("foo") == 10);
}

using TestGetSum = ::accessor::FunctionWrapper<Test, int, int, int>;
template class ::accessor::MakeProxy<TestGetSum, &Test::getSum>;

bool callOnceGetSum()
{
  Test t;

  return (::accessor::callFunction<TestGetSum>(t, 1, 1) == 2) &&
         (t.getMethodVisitedCounter("getSum") > 0);
}

bool callMultipleGetSum()
{
  Test t;
  int callsNumber = 10;
  bool testResult = false;

  for (int i = 0; i < callsNumber; ++i)
  {
    int expectedSum = i + callsNumber;
    testResult = (::accessor::callFunction<TestGetSum>(t, i, callsNumber) == expectedSum) &&
                 (t.getMethodVisitedCounter("getSum") > i);
  }

  return testResult;
}

template<typename T>
using TestMax = ::accessor::FunctionWrapper<Test, T, const T&, const T&>;
template class ::accessor::MakeProxy<TestMax<int>, &Test::max>;
template class ::accessor::MakeProxy<TestMax<uint32_t>, &Test::max>;

bool calOnceTemplatedMax()
{
  Test t;
  bool testResult = false;

  {
    testResult = (::accessor::callFunction<TestMax<int>>(t, 10, 20) == 20) &&
                 (t.getMethodVisitedCounter("max") > 0);
  }

  {
    testResult = (::accessor::callFunction<TestMax<uint32_t>>(t, 100u, 200u) == 200u) &&
                 (t.getMethodVisitedCounter("max") > 1);
  }

  return testResult;
}


bool calMultipleTemplatedMax()
{
  Test t;
  int callsNumber = 10;
  bool testResult = false;

  for (int i = 0; i < callsNumber; ++i)
  {
    auto maxRes = ::accessor::callFunction<TestMax<int>>(t, i, callsNumber - i);
    testResult = (maxRes == std::max(i, callsNumber - i)) &&
                 (t.getMethodVisitedCounter("max") > i);
  }

  return testResult;
}

int main()
{
  ::testHelper::validateTest(callOnceSimpleFoo());
  ::testHelper::validateTest(callMultipleSimpleFoo());
  ::testHelper::validateTest(callOnceGetSum());
  ::testHelper::validateTest(callMultipleGetSum());
  ::testHelper::validateTest(calOnceTemplatedMax());
  ::testHelper::validateTest(calMultipleTemplatedMax());

  return ::testHelper::failedTests();
}
