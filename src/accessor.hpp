//****************************************************//
// File accessor.hpp                                  //
// Autor Hubert Liberacki (hliberacki@gmail.com)      //
//****************************************************//

// This is a simple library which provides functionality to access private and protected member, without neccessity of using
// "friend" or define private/protected as public.

#ifndef ACCESSOR_SRC_ACCESSOR_HPP
#define ACCESSOR_SRC_ACCESSOR_HPP

#include <string>
#include <functional>

template <typename ObjId>
struct resultValue
{
    typedef typename ObjId::type type;
    static type _ptr;
};

template<typename ObjId>
typename resultValue<ObjId>::type resultValue<ObjId>::_ptr;

template<typename ObjId, typename ObjId::type ptr>
struct access : resultValue<ObjId>
{
  struct setter
  {
      setter()
      {
          resultValue<ObjId>::_ptr = ptr;
      }
  };

  static setter _setter;
};

template<typename ObjId, typename ObjId::type ptr>
typename access<ObjId, ptr>::setter access<ObjId, ptr>::_setter;

#endif // ACCESSOR_SRC_ACCESSOR_HPP
