
#include "accessor/accessor.hpp"
#include <iostream>
class Custom
{
 public:
 Custom() : _private{1}{};
 ~Custom() = default;

 private:

 int _private;
 void privateF()
 {
   std::cout << "private method" << std::endl;
 }
};

struct CustomAccessed 
{
  typedef void(Custom::*type)();	
}; 

struct CustomAccessedInt
{
  typedef int(Custom::*type);
};

template class access<CustomAccessed, &Custom::privateF>;
template class access<CustomAccessedInt, &Custom::_private>;
int main()
{
 Custom c;
 (c.*resultValue<CustomAccessed>::_ptr)(); 
 std::cout << c.*resultValue<CustomAccessedInt>::_ptr<<std::endl;
  
  return 0;
}
