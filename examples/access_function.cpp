// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: Copyright (c) 2017-2025 Hubert Liberacki <hliberacki@gmail.com>
//
// cpp-member-accessor – header-only C++ library for accessing private members
// Project home: https://github.com/hliberacki/cpp-member-accessor

#include "accessor/accessor.hpp"
#include <iostream>

class Test
{
  void foo() { std::cout << "private method: Foo" << '\n'; }

  void bar(int i, double d)
  {
    std::cout << "private method: Bar. Args:[" << i << ", " << d << "]"<< '\n';
  }

  int getSum(int first, int second ) const { return first + second; }

  template<typename T>
  T max(T& lhs, T& rhs) { return (lhs > rhs) ? lhs : rhs; }
};

FUNCTION_ACCESSOR(TestFoo, Test, foo, void)
FUNCTION_ACCESSOR(TestBar, Test, bar, void, int, double)
CONST_FUNCTION_ACCESSOR(TestSum, Test, getSum, int, int, int)

FUNCTION_ACCESSOR(TestMaxInt, Test, max, int, int&, int&)
FUNCTION_ACCESSOR(TestMaxFloat, Test, max, float, float&, float&)

int main()
{
  Test t;

  std::cout << "\nfoo()                 : ";
  accessor::callFunction<TestFoo>(t);

  std::cout << "\nbar(20, 30)           : ";
  accessor::callFunction<TestBar>(t, 20, 30);

  std::cout << "\ngetSum(20, 30)        : ";
  auto result = accessor::callFunction<TestSum>(t, 20, 30);
  std::cout << "sum output: " << result << '\n';

  std::cout << "\nmax<int>(20, 30)      : ";
  auto maxInt = accessor::callFunction<TestMaxInt>(t, 20, 30);
  std::cout  << maxInt << '\n';

  std::cout << "\nmax<float>(0.7f, 0.5f): ";
  auto maxFloat = accessor::callFunction<TestMaxFloat>(t, 0.7f, 0.5f);
  std::cout  << maxFloat << '\n';

  return 0;
}
