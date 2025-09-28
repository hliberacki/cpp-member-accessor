// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: Copyright (c) 2017-2025 Hubert Liberacki <hliberacki@gmail.com>
//
// cpp-member-accessor – header-only C++ library for accessing private members
// Project home: https://github.com/hliberacki/cpp-member-accessor

#include "accessor/accessor.hpp"
#include <iostream>
#include <vector>

class Test
{
public:
  Test() = default;
  Test(int i) : mBar{i} {}

private:
  void foo() { std::cout << "private method: Foo" << '\n'; }
  int mBar {1};
};

FUNCTION_ACCESSOR(TestFooView, Test, foo, void)
MEMBER_ACCESSOR(TestBarView, Test, mBar, int)

int main()
{
  std::vector<Test> collection;

  for(int i = 0; i < 5; ++i)
  {
    collection.emplace_back(i);
  }

  std::cout << "Applying the same accessors on each elemet of vector container" << '\n';

  for(auto item : collection)
  {
    std::cout << "\n################################" << '\n';
    accessor::callFunction<TestFooView>(item);
    std::cout << "mBar: " << accessor::accessMember<TestBarView>(item).get() << '\n';
  }

  return 0;
}
