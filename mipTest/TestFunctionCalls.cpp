#include <gtest/gtest.h> // googletest header file
#include "include/CMiniInterpreter.h"

TEST(TestFunctionCalls, Simple )
{
  CMiniInterpreter interp;
  interp.InterpretCode(" float globVar = 1; function fooNoPar () { print(\"fooNoPar\", globVar ,\"\n\"); globVar = 7; }  fooNoPar(2,3);  print(globVar);  ");
  EXPECT_FLOAT_EQ( interp.GetFloatValue("globVar"), 7); // set to 7 in function
}

TEST(TestFunctionCalls, ExecuteFunction )
{
  CMiniInterpreter interp;
  interp.InterpretCode(" print(\"before\"); \n//cmt \n print(\"after // this is not a comment\"); \n//commenrt ");
  interp.InterpretCode(" print(\"before\"); \n function foo(){ print(\"hello from foo\"); }   print(\"after\"); \n//commenrt ");
  std::cout << "-----------\n";
  ASSERT_EQ(interp.ExecuteFunction("foo"),true);
}
