//************************************************************************************
// cpp-member-accessor
//
// Copyright (c) 2017- Hubert Liberacki <hliberacki@gmail.com>
//
// SPDX-License-Identifier: MIT
// Project home: https://github.com/hliberacki/cpp-member-accessor
//************************************************************************************

#include <accessor/accessor.hpp>

class Test
{
  int mFooBar {1};
};

using TestFooBar = accessor::MemberWrapper<Test, int>;
template class accessor::MakeProxy<TestFooBar, &Test::mFooBar>;

int main()
{
    Test t;
    (void)accessor::accessMember<TestFooBar>(t);
}