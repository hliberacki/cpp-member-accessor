
#include "accessor/accessor.hpp"
#include <iostream>
#include <string>
#include <vector>

struct Dummy
{
  int mVal {0};
};

class Test
{
  int mFoo {1};
  int mFoo2 {2};
  std::string mBar {"Hello World"};
  Dummy mFooBar;
  std::vector<int> mVec;
};

MEMBER_ACCESSOR(TestFoo, Test, mFoo, int)
MEMBER_ACCESSOR(TestFoo2, Test, mFoo2, int)
MEMBER_ACCESSOR(TestBar, Test, mBar, std::string)
MEMBER_ACCESSOR(TestFooBar, Test, mFooBar, Dummy)
MEMBER_ACCESSOR(TestVec, Test, mVec, std::vector<int>)

int main()
{
  Test t;

  std::cout << "\nmFoo             : "
            << accessor::accessMember<TestFoo>(t) << '\n';

  std::cout << "\nChanging mFoo to : " << 2000 << '\n';
  auto foobar = accessor::accessMember<TestFoo>(t);
  foobar.get() = 2000;

  std::cout << "\nmFoo             : "
            << accessor::accessMember<TestFoo>(t) << '\n';

  std::cout << "\nmFoo2             : "
            << accessor::accessMember<TestFoo2>(t) << '\n';

  std::cout << "\nmBar             : "
            << accessor::accessMember<TestBar>(t).get() << '\n';

  std::cout << "\nmFooBar          : "
            << accessor::accessMember<TestFooBar>(t).get().mVal << '\n';

  std::cout << "\nmVec size: " << accessor::accessMember<TestVec>(t).get().size()
            << " emplacing elements {0,1,2,3,4,5,6,7,8,9}" << '\n';

  for(int i = 0; i < 10 ; ++i)
  {
    accessor::accessMember<TestVec>(t).get().emplace_back(i);
  }

  std::cout << "\nmVec size: " << accessor::accessMember<TestVec>(t).get().size()
            << " elements: { ";

  for(auto item : accessor::accessMember<TestVec>(t).get())
  {
    std::cout << item << " ";
  }

  std::cout << "}\n";

  return 0;
}
