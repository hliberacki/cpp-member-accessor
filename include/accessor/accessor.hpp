//************************************************************************************
// cpp-member-accessor
//
// Copyright (c) 2017- Hubert Liberacki <hliberacki@gmail.com>
//
// SPDX-License-Identifier: MIT
// Project home: https://github.com/hliberacki/cpp-member-accessor
//************************************************************************************

#ifndef ACCESSOR_INCLUDE_ACCESSOR_HPP
#define ACCESSOR_INCLUDE_ACCESSOR_HPP

#include <functional>

namespace accessor
{
    template<typename C, typename T>
    struct MemberWrapper
    {
      using type = T (C::*);
    };

    template<class C, class R, typename... Args>
    struct FunctionWrapper
    {
      using type = R (C::*)(Args...);
    };

    template<class C, class R, typename... Args>
    struct ConstFunctionWrapper
    {
      using type = R (C::*)(Args...) const;
    };

    template<class Tag>
    struct Proxy
    {
      static typename Tag::type value;
    };

    template <class Tag>
    typename Tag::type Proxy<Tag>::value;

    template<class T, typename T::type AccessPointer>
    class MakeProxy
    {
      struct Setter { Setter() { Proxy<T>::value = AccessPointer; } };
      static Setter instance;
    };

    template<class T, typename T::type AccessPointer>
    typename MakeProxy<T, AccessPointer>::Setter MakeProxy<T, AccessPointer>::instance;

    template<typename Sig, class Instance, typename... Args>
    decltype(auto) callFunction(Instance & instance, Args &&...args)
    {
      return (instance.*(Proxy<Sig>::value))(std::forward<Args>(args)...);
    }

    template<typename Sig, class Instance>
    decltype(auto) accessMember(Instance & instance)
    {
        return instance.*(Proxy<Sig>::value);
    }
}

#define FUNCTION_HELPER(...)                                           \
  accessor::FunctionWrapper<__VA_ARGS__>

#define CONST_FUNCTION_HELPER(...)                                     \
  accessor::ConstFunctionWrapper<__VA_ARGS__>

#define FUNCTION_ACCESSOR(accessor_name, base, method, ...)            \
  struct accessor_name : FUNCTION_HELPER(base, __VA_ARGS__) {};            \
  template class accessor::MakeProxy<accessor_name, &base::method>;

#define CONST_FUNCTION_ACCESSOR(accessor_name, base, method, ...)      \
  struct accessor_name : CONST_FUNCTION_HELPER(base, __VA_ARGS__) {};      \
  template class accessor::MakeProxy<accessor_name, &base::method>;

#define MEMBER_ACCESSOR(accessor_name, base, member, ret_type)         \
  struct accessor_name : accessor::MemberWrapper<base, ret_type> {};       \
  template class accessor::MakeProxy<accessor_name, &base::member>;

#endif // ACCESSOR_INCLUDE_ACCESSOR_HPP
