//****************************************************//
// File accessor.hpp                                  //
// Autor Hubert Liberacki (hliberacki@gmail.com)      //
//****************************************************//

// This is a simple library which provides functionality to access private and protected member, without neccessity of using
// "friend" or define private/protected as public.

#ifndef ACCESSOR_SRC_ACCESSOR_HPP
#define ACCESSOR_SRC_ACCESSOR_HPP

#include <functional>

namespace accessor
{
    template<typename T, typename C>
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

    template<class T>
    const auto accessEntity = Proxy<T, T>::value;

    template<typename Sig, class Instance, typename... Args>
    auto callFunction(Instance & instance, Args ...args)
    {
      return (instance.*accessEntity<Sig>)(args...);
    }

    template<typename Sig, class Instance>
    auto accessMember(Instance & instance)
    {
        return std::ref(instance.*accessEntity<Sig>);
    }
}

#define MAKE_FUNCTION_HELPER(...)                                           \
  accessor::FunctionWrapper<__VA_ARGS__>

#define MAKE_CONST_FUNCTION_HELPER(...)                                     \
  accessor::ConstFunctionWrapper<__VA_ARGS__>

#define CREATE_FUNCTION_ACCESSOR(accessor_name, base, method, ...)          \
  using accessor_name = MAKE_FUNCTION_HELPER(base, __VA_ARGS__);            \
  template class accessor::MakeProxy<accessor_name, &base::method>;

#define CREATE_CONST_FUNCTION_ACCESSOR(accessor_name, base, method, ...)    \
  using accessor_name = MAKE_CONST_FUNCTION_HELPER(base, __VA_ARGS__);      \
  template class accessor::MakeProxy<accessor_name, &base::method>;

#define CREATE_MEMBER_ACCESSOR(accessor_name, base, member, ret_type)       \
  using accessor_name = accessor::MemberWrapper<ret_type, base>;            \
  template class accessor::MakeProxy<accessor_name, &base::member>;

#endif // ACCESSOR_SRC_ACCESSOR_HPP
