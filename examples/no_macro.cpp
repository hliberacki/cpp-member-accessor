//************************************************************************************
// cpp-member-accessor
//
// Copyright (c) 2017- Hubert Liberacki <hliberacki@gmail.com>
//
// SPDX-License-Identifier: MIT
// Project home: https://github.com/hliberacki/cpp-member-accessor
//************************************************************************************

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

  int mFooBar {1};
};

using TestFoo      = accessor::FunctionWrapper<Test, void>;
using TestBar      = accessor::FunctionWrapper<Test, void, int, double>;
using TestSum      = accessor::ConstFunctionWrapper<Test, int, int, int>;
using TestMaxInt   = accessor::FunctionWrapper<Test, int, int&, int&>;
using TestMaxFloat = accessor::FunctionWrapper<Test, float, float&, float&>;

template<typename T>
using TestMax      = accessor::FunctionWrapper<Test, T, T&, T&>;

using TestFooBar   = accessor::MemberWrapper<Test, int>;

template class accessor::MakeProxy<TestFoo, &Test::foo>;
template class accessor::MakeProxy<TestBar, &Test::bar>;
template class accessor::MakeProxy<TestSum, &Test::getSum>;
template class accessor::MakeProxy<TestMaxInt, &Test::max>;
template class accessor::MakeProxy<TestMaxFloat, &Test::max>;
template class accessor::MakeProxy<TestMax<double>, &Test::max>;
template class accessor::MakeProxy<TestFooBar, &Test::mFooBar>;

int main()
{
  Test t;

  std::cout << "\nfoo()                  : ";
  accessor::callFunction<TestFoo>(t);

  std::cout << "\nbar(20, 30)            : ";
  accessor::callFunction<TestBar>(t, 20, 30);

  std::cout << "\ngetSum(20, 30)         : ";
  auto result = accessor::callFunction<TestSum>(t, 20, 30);
  std::cout << "sum output: " << result << '\n';

  std::cout << "\nmax<int>(20, 30)       : ";
  auto maxInt = accessor::callFunction<TestMaxInt>(t, 20, 30);
  std::cout  << maxInt << '\n';

  std::cout << "\nmax<float>(0.7f, 0.5f) : ";
  auto maxFloat = accessor::callFunction<TestMaxFloat>(t, 0.7f, 0.5f);
  std::cout  << maxFloat << '\n';

  std::cout << "\nmax<double>(0.37, 0.56): ";
  auto maxDouble = accessor::callFunction<TestMax<double>>(t, 0.37, 0.56);
  std::cout  << maxDouble << '\n';

  std::cout << "\nmFooBar                : " << accessor::accessMember<TestFooBar>(t)
            << '\n';
  auto fooBar = accessor::accessMember<TestFooBar>(t);
  fooBar.get() *= 2;

  std::cout << "\nMultiply mFooBar by 2" << '\n';
  std::cout << "mFooBar                : " << accessor::accessMember<TestFooBar>(t)
            << '\n';
  return 0;
}
