#include "test_helper.hpp"
#include <accessor/accessor.hpp>
#include <iostream>
#include <vector>

class Test
{
public:
  Test() = default;
  Test(std::vector<int> data) : mFooBar{data} {}

private:
  int mFoo {0};
  std::vector<int> mFooBar;
};


using TestFoo = ::accessor::MemberWrapper<Test, int>;
template class ::accessor::MakeProxy<TestFoo, &Test::mFoo>;

bool accessSimpleMember()
{
  Test t;

  return (::accessor::accessMember<TestFoo>(t) == 0);
}

bool changeValueOfSimpleMember()
{
  Test t;

  ::accessor::accessMember<TestFoo>(t).get() = 100;
  return (::accessor::accessMember<TestFoo>(t) == 100);
}

using TestFooBar = ::accessor::MemberWrapper<Test, std::vector<int>>;
template class ::accessor::MakeProxy<TestFooBar, &Test::mFooBar>;

bool accessContainerType()
{
  std::vector<int> testData = {0, 1, 2, 4, 5, 6, 7, 8, 9};
  Test t(testData);

  bool testResult = false;

  for (uint8_t i = 0; i < testData.size(); ++i)
  {
    testResult = (testData[i] == ::accessor::accessMember<TestFooBar>(t).get()[i]);
  }

  return testResult;
}

bool emplaceElementsToContainer()
{
  Test t;
  std::vector<int> testData = {0, 1, 2, 4, 5, 6, 7, 8, 9};

  auto refFooBar = ::accessor::accessMember<TestFooBar>(t);
  for (auto item: testData)
  {
    refFooBar.get().emplace_back(item);
  }

  return (testData.size() == ::accessor::accessMember<TestFooBar>(t).get().size());
}

int main()
{
  ::testHelper::validateTest(accessSimpleMember());
  ::testHelper::validateTest(changeValueOfSimpleMember());
  ::testHelper::validateTest(accessContainerType());
  ::testHelper::validateTest(emplaceElementsToContainer());

  return ::testHelper::failedTests();
}

