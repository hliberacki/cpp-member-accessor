//************************************************************************************
// cpp-member-accessor
//
// Copyright (c) 2017- Hubert Liberacki <hliberacki@gmail.com>
//
// SPDX-License-Identifier: MIT
// Project home: https://github.com/hliberacki/cpp-member-accessor
//************************************************************************************

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


