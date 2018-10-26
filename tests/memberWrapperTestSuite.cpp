#include "test_helper.hpp"
#include <accessor/accessor.hpp>
#include <iostream>
#include <vector>

class Test
{
  int mFoo;
  const float mBar;
  std::vector<int> mFooBar;
};

bool checkSignatureBasic()
{
  using fooSig = int(Test::*);
  return std::is_same<fooSig, ::accessor::MemberWrapper<Test, int>::type>::value;
}

bool checkConstSignatureBasic()
{
  using barSig = const float(Test::*);
  return std::is_same<barSig, ::accessor::MemberWrapper<Test, const float>::type>::value;
}

bool checkCollectionSignatureBasic()
{
  using foobarSig = std::vector<int>(Test::*);
  return std::is_same<foobarSig, ::accessor::MemberWrapper<Test, std::vector<int>>::type>::value;
}

int main()
{
  ::testHelper::validateTest(checkSignatureBasic());
  ::testHelper::validateTest(checkConstSignatureBasic());
  ::testHelper::validateTest(checkCollectionSignatureBasic());

  return ::testHelper::failedTests();
}

