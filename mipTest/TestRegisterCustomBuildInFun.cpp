#include <gtest/gtest.h> // googletest header file
#include "include/CMiniInterpreter.h"

#include <string>

static std::string s_teststore;

float Test_Foo(std::vector<CVariable*>& plist)
{

  std::cout << "Sample Fun Called with parameter:";
  for (auto p : plist) {
    std::cout << p->GetString() << " ";
    s_teststore.append(p->GetString());
  }
  std::cout << "\n";
  return 0.0F;
}



TEST(TestRegisterCustomBuildInFun, Simple ) {

  CMiniInterpreter interp;
  interp.RegisterCustomBuiltIn("TestFoo", Test_Foo);
  interp.InterpretCode(" float zz=3.2;  TestFoo(\"A11\",34,zz );");
  EXPECT_STREQ(s_teststore.c_str(),"A11343.2");
}

