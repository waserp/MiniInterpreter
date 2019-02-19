#include <gtest/gtest.h> // googletest header file
#include "include/CMiniInterpreter.h"

#include <string>

TEST(TestStrings, Simple )
{
  CMiniInterpreter interp;
  interp.InterpretCode(" string name; string color = \"green\"; string abc = \"aa\" \"bb\" ,\"cc\" color; ");
  EXPECT_STREQ(interp.GetStringValue("color").c_str(),"green");
  EXPECT_STREQ(interp.GetStringValue("abc").c_str(),"aabbccgreen");
  interp.InterpretCode(" float zz = 1.1; abc = abc + zz; print(abc); ");
}
