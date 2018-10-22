
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
struct CustomM : accessor::MemberWrapper<int, Custom> {};

template class accessor::MakeProxy<CustomF, &Custom::privateF>;
template class accessor::MakeProxy<CustomM, &Custom::mPriv>;


int main()
{
  Custom c1, c2;

  std::cout << "Accessing C1 object" << "\n\n";

  std::cout << "privateF output:    ";
  accessor::accessFunction<CustomF>(c1);

  std::cout << "C1.mPrivate value:    "<< accessor::accessMember<CustomM>(c1) << "\n\n";

  std::cout << "Changing C1 C2 private member values" << "\n\n";
  auto c1Member = accessor::accessMember<CustomM>(c1);
  c1Member.get() = 1000;

  std::cout << "New C1.mPrivate value: " << accessor::accessMember<CustomM>(c1) << '\n';

  auto c2Member = accessor::accessMember<CustomM>(c2);
  c2Member.get() = 2000;

  std::cout << "New C2.mPrivate value: " << accessor::accessMember<CustomM>(c2) << '\n';

  return 0;
}
