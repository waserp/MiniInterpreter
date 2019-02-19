#include <gtest/gtest.h> // googletest header file
#include "include/CMiniInterpreter.h"

TEST(TestWhileFlowControl, Simple )
{
  CMiniInterpreter interp;
  interp.InterpretCode("  float bar = 2; while(bar < 4) { print(\"{}{{bar=\",bar); bar = bar +1;}  print(\"exit\");  ");
  interp.InterpretCode("  float statusbar = 2; float count = 0; while(count == 0 ) { print(\"{}{{statusbar=\",statusbar); statusbar = statusbar +1; count = 1 + count; }  print(\"exit\");  ");
  interp.InterpretCode("  float cucumber = 4; while(cucumber != 0 ) { print(\"{}{{cucumber=\",cucumber); cucumber = cucumber -1; }  print(\"by cucumber\");  ");
  EXPECT_FLOAT_EQ( interp.GetFloatValue("bar"), 4);
  EXPECT_FLOAT_EQ( interp.GetFloatValue("statusbar"), 3);
  EXPECT_FLOAT_EQ( interp.GetFloatValue("cucumber"), 0);
}
