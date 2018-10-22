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

    template<typename R, typename C, typename... Args>
    struct FunctionWrapper
    {
      using type = R (C::*)(Args...);
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
    auto accessFunction(Instance & instance, Args ...args)
    {
      return (instance.*accessEntity<Sig>)(args...);
    }

    template<typename Sig, class Instance>
    auto accessMember(Instance & instance)
    {
        return std::ref(instance.*accessEntity<Sig>);
    }

}

#endif // ACCESSOR_SRC_ACCESSOR_HPP
