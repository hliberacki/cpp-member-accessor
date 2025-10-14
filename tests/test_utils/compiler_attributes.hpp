// SPDX-License-Identifier: MIT
// SPDX-FileCopyrightText: Copyright (c) 2017-2025 Hubert Liberacki <hliberacki@gmail.com>
//
// cpp-member-accessor – header-only C++ library for accessing private members
// Project home: https://github.com/hliberacki/cpp-member-accessor

#ifndef ACCESSOR_TESTS_TESTS_UTILS_COMPILER_ATTRIBUTES_HPP
#define ACCESSOR_TESTS_TESTS_UTILS_COMPILER_ATTRIBUTES_HPP

#if __cplusplus >= 201703L
#define UNUSED [[maybe_unused]]
#elif defined(__clang__)
#define UNUSED __attribute__((unused))
#elif defined(__GNUC__)
#define UNUSED
#else
#define UNUSED
#endif

#endif // ACCESSOR_TESTS_TESTS_UTILS_COMPILER_ATTRIBUTES_HPP
