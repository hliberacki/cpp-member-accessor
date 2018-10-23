
#include "accessor/accessor.hpp"
#include <iostream>
#include <vector>

class Test
{
public:
  Test() = default;
  Test(int i) : mFooBar{i} {}

private:
  void foo() { std::cout << "private method: Foo" << '\n'; }

  void bar(int i, double d)
  {
    std::cout << "private method: Bar. Args:[" << i << ", " << d << "]"<< '\n';
  }

  int getSum(int first, int second ) const { return first + second; }

  int mFooBar {1};
};

CREATE_FUNCTION_ACCESSOR(TestFoo, Test, foo, void)
CREATE_FUNCTION_ACCESSOR(TestBar, Test, bar, void, int, double)
CREATE_CONST_FUNCTION_ACCESSOR(TestSum, Test, getSum, int, int, int)
CREATE_MEMBER_ACCESSOR(TestFooBar, Test, mFooBar, int)

int main()
{
  Test first;

  std::cout << "\nCalling private method foo():    ";
  accessor::callFunction<TestFoo>(first);

  std::cout << "\nCalling private method bar(20, 30):    ";
  accessor::callFunction<TestBar>(first, 20, 30);

  std::cout << "\nCalling private method getSum(20, 30): ";
  auto result = accessor::callFunction<TestSum>(first, 20, 30);
  std::cout << "sum output: " << result << '\n';

  std::cout << "\nPrinting value of private member mFooBar: "
            << accessor::accessMember<TestFooBar>(first) << '\n';

  std::cout << "\nChanging mFooBar to 2000" << '\n';
  auto foobar = accessor::accessMember<TestFooBar>(first);
  foobar.get() = 2000;

  std::cout << "\nPrinting value of private member mFooBar: "
            << accessor::accessMember<TestFooBar>(first) << '\n';


  std::cout << "\nApplying the same View for collection of Test objects, std::vector<Test>" << '\n';

  std::vector<Test> testContainer =  {Test(0), Test(1)};

  for(auto test : testContainer)
  {
      std::cout << "\nCalling private method foo():    ";
      accessor::callFunction<TestFoo>(test);

      std::cout << "\nCalling private method bar(20, 30):    ";
      accessor::callFunction<TestBar>(test, 20, 30);

      std::cout << "\nCalling private method getSum(20, 30): ";
      auto result = accessor::callFunction<TestSum>(test, 20, 30);
      std::cout << "\nsum output: " << result << '\n';

      std::cout << "\nPrinting value of private member mFooBar: "
                << accessor::accessMember<TestFooBar>(test) << '\n';

      std::cout << "\nChanging mFooBar to 2000" << '\n';
      auto foobar = accessor::accessMember<TestFooBar>(test);
      foobar.get() = 2000;

      std::cout << "\nPrinting value of private member mFooBar: "
                << accessor::accessMember<TestFooBar>(test) << '\n';
  }

  return 0;
}
