// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: Copyright (c) 2017-2025 Hubert Liberacki <hliberacki@gmail.com>
//
// cpp-member-accessor – header-only C++ library for accessing private members
// Project home: https://github.com/hliberacki/cpp-member-accessor

#ifndef ACCESSOR_TESTS_TEST_HELPER_HPP
#define ACCESSOR_TESTS_TEST_HELPER_HPP
#include <iostream>
namespace testHelper
{
   inline static int & failedTests()
   {
     static int testFailed = 0;
     return testFailed;
   }

   void validateTest(bool expression)
   {
     if (!expression)
        ++failedTests();
   }
}

#endif // ACCESSOR_TESTS_TEST_HELPER_HPP
