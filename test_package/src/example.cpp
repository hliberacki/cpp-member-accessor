// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: Copyright (c) 2017-2025 Hubert Liberacki <hliberacki@gmail.com>
//
// cpp-member-accessor – header-only C++ library for accessing private members
// Project home: https://github.com/hliberacki/cpp-member-accessor

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
