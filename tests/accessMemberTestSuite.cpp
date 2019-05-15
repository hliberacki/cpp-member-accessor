#include "test_helper.hpp"
#include <accessor/accessor.hpp>
#include <iostream>
#include <vector>

class Test
{
public:
  Test() = default;
  Test(std::vector<int> data, std::vector<int> data2) :
        mFooBar{data}, mFooBar2 {data2} {}

private:
  int mFoo {0};
  int mFoo2 {1};
  std::vector<int> mFooBar;
  std::vector<int> mFooBar2;
};


struct TestFoo : ::accessor::MemberWrapper<Test, int> {};
template class ::accessor::MakeProxy<TestFoo, &Test::mFoo>;

struct TestFoo2 : ::accessor::MemberWrapper<Test, int> {};
template class ::accessor::MakeProxy<TestFoo2, &Test::mFoo2>;

bool accessSimpleMember()
{
  Test t;

  return (::accessor::accessMember<TestFoo>(t) == 0)
      && (::accessor::accessMember<TestFoo2>(t) == 1);
}

bool changeValueOfSimpleMember()
{
  Test t;

  ::accessor::accessMember<TestFoo>(t).get() = 100;
  ::accessor::accessMember<TestFoo2>(t).get() = 101;
  return (::accessor::accessMember<TestFoo>(t) == 100)
      && (::accessor::accessMember<TestFoo2>(t) == 101);
}

struct TestFooBar : ::accessor::MemberWrapper<Test, std::vector<int>> {};
template class ::accessor::MakeProxy<TestFooBar, &Test::mFooBar>;

struct TestFooBar2 : ::accessor::MemberWrapper<Test, std::vector<int>> {};
template class ::accessor::MakeProxy<TestFooBar2, &Test::mFooBar2>;

bool accessContainerType()
{
  std::vector<int> testData = {0, 1, 2, 4, 5, 6, 7, 8, 9};
  std::vector<int> testData2 = {10, 11, 12, 14, 15, 16, 17, 18, 19};
  Test t(testData, testData2);

  bool testResult = true;

  for (uint8_t i = 0; i < testData.size(); ++i)
  {
    testResult = testResult && (testData[i] == ::accessor::accessMember<TestFooBar>(t).get()[i]);
  }
  for (uint8_t i = 0; i < testData2.size(); ++i)
  {
    testResult = testResult && (testData2[i] == ::accessor::accessMember<TestFooBar2>(t).get()[i]);
  }

  return testResult;
}

bool emplaceElementsToContainer()
{
  Test t;
  std::vector<int> testData = {0, 1, 2, 4, 5, 6, 7, 8, 9};
  std::vector<int> testData2 = {10, 11, 12, 14, 15, 16, 17, 18, 19};

  auto refFooBar = ::accessor::accessMember<TestFooBar>(t);
  for (auto item: testData)
  {
    refFooBar.get().emplace_back(item);
  }

  auto refFooBar2 = ::accessor::accessMember<TestFooBar2>(t);
  for (auto item: testData2)
  {
    refFooBar2.get().emplace_back(item);
  }

  bool testResult = true;

  for (uint8_t i = 0; i < testData.size(); ++i)
  {
    testResult = testResult && (testData[i] == ::accessor::accessMember<TestFooBar>(t).get()[i]);
  }
  for (uint8_t i = 0; i < testData2.size(); ++i)
  {
    testResult = testResult && (testData2[i] == ::accessor::accessMember<TestFooBar2>(t).get()[i]);
  }

  return testResult;
}

int main()
{
  ::testHelper::validateTest(accessSimpleMember());
  ::testHelper::validateTest(changeValueOfSimpleMember());
  ::testHelper::validateTest(accessContainerType());
  ::testHelper::validateTest(emplaceElementsToContainer());

  return ::testHelper::failedTests();
}

