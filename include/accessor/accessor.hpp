//************************************************************************************
// Copyright Hubert Liberacki (hliberacki@gmail.com)
// Copyright Krzysztof Ostrowski
//
// Project home: https://github.com/hliberacki/cpp-member-accessor
//
// MIT LICENSE : https://github.com/hliberacki/cpp-member-accessor/blob/master/LICENSE
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

    template<class Tag, class T>
    struct Proxy
    {
      static typename T::type value;
    };

    template <class Tag, class T>
    typename T::type Proxy<Tag, T>::value;

    template<class T, typename T::type AccessPointer>
    class MakeProxy
    {
      struct Setter { Setter() { Proxy<T, T>::value = AccessPointer; } };
      static Setter instance;
    };

    template<class T, typename T::type AccessPointer>
    typename MakeProxy<T, AccessPointer>::Setter MakeProxy<T, AccessPointer>::instance;

    template<typename Sig, class Instance, typename... Args>
    auto callFunction(Instance & instance, Args ...args)
    {
      return (instance.*(Proxy<Sig, Sig>::value))(args...);
    }

    template<typename Sig, class Instance>
    auto accessMember(Instance & instance)
    {
        return std::ref(instance.*(Proxy<Sig, Sig>::value));
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
