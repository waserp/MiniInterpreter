#include <gtest/gtest.h> // googletest header file
#include "include/CMiniInterpreter.h"

TEST(TestNumericBooleanEvaluator, Simple ) {
  CMiniInterpreter interp;
  EXPECT_FLOAT_EQ( interp.EvaluateNumExpression("5 < 6;"),(5 < 6));
  EXPECT_FLOAT_EQ( interp.EvaluateNumExpression("5 > 6;"),(5 > 6));
  EXPECT_FLOAT_EQ( interp.EvaluateNumExpression("5 == 6;"),(5 == 6));
  EXPECT_FLOAT_EQ( interp.EvaluateNumExpression("-1 == -1;"),(-1 == -1));
  EXPECT_FLOAT_EQ( interp.EvaluateNumExpression("3 + 1 == 1 + 2;"),(3 + 1 == 1 + 2));
  EXPECT_FLOAT_EQ( interp.EvaluateNumExpression("9.6 + 1 < 2 + 2;"),(9.6 + 1 < 2 + 2));  // puh use a parenthesis for this things
}

TEST(TestNumericBooleanEvaluator, WithVariables ) {
  CMiniInterpreter interp;
  float pi = 3.1415926F; float a12zz = 34.523F; float zsa = 1.2F;
  interp.PreloadVariable("a12zz",a12zz);
  interp.PreloadVariable("pi",pi);
  interp.PreloadVariable("zsa",zsa);
  EXPECT_FLOAT_EQ( interp.EvaluateNumExpression(" pi < zsa;"),(pi < zsa));
  EXPECT_FLOAT_EQ( interp.EvaluateNumExpression(" pi < a12zz;"),(pi < a12zz));
}
