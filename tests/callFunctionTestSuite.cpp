//************************************************************************************
// Copyright Hubert Liberacki (hliberacki@gmail.com)
// Copyright Krzysztof Ostrowski
// SPDX-FileCopyrightText: Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
//
// Project home: https://github.com/hliberacki/cpp-member-accessor
//
// MIT LICENSE : https://github.com/hliberacki/cpp-member-accessor/blob/master/LICENSE
//************************************************************************************

#include "test_helper.hpp"
#include <accessor/accessor.hpp>
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

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
  T max(T& lhs, T& rhs)
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
using TestMax = ::accessor::FunctionWrapper<Test, T, T&, T&>;
template class ::accessor::MakeProxy<TestMax<int>, &Test::max>;
template class ::accessor::MakeProxy<TestMax<uint32_t>, &Test::max>;

bool calOnceTemplatedMax()
{
  Test t;
  bool testResult = false;

  {
    int a = 10, b = 20;
    testResult = (::accessor::callFunction<TestMax<int>>(t, a, b) == 20);
                 (t.getMethodVisitedCounter("max") > 0);
  }

  {
    uint32_t c = 100u, d = 200u;
    testResult = (::accessor::callFunction<TestMax<uint32_t>>(t, c, d) == 200u) &&
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
    int temp = callsNumber - i;
    auto maxRes = ::accessor::callFunction<TestMax<int>>(t, i, temp);
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
