
#include "accessor/accessor.hpp"
#include <iostream>


class Custom
{
 public:
 Custom() : mPriv{1}{}
 ~Custom() = default;

 private:

 int mPriv;
 void privateF()
 {
   std::cout << "private method" << std::endl;
 }
};

struct CustomF : accessor::FunctionWrapper<void, Custom> {};
template class accessor::MakeProxy<CustomF, &Custom::privateF>;

int main()
{
  Custom c;
  (c.*accessor::accessEntity<CustomF>)();
  return 0;
}
