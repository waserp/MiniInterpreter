#include <gtest/gtest.h> // googletest header file
#include "include/CMiniInterpreter.h"

TEST(Arithmetic, preloadVariables ) {
  CMiniInterpreter interp;
  float pi = 3.1415926;
  float a12zz = 34.523;
  interp.PreloadVariable("a12zz",a12zz);
  interp.PreloadVariable("pi",pi);
  EXPECT_FLOAT_EQ(interp.EvaluateNumExpression("pi;"),pi);
  EXPECT_FLOAT_EQ(interp.EvaluateNumExpression("a12zz;"),a12zz);
  EXPECT_FLOAT_EQ(interp.EvaluateNumExpression(" pi ; "),pi);
  EXPECT_FLOAT_EQ(interp.EvaluateNumExpression(" a12zz ; "),a12zz);
  EXPECT_FLOAT_EQ(interp.EvaluateNumExpression(" \n pi ; "),pi);
  EXPECT_FLOAT_EQ(interp.EvaluateNumExpression(" \n  a12zz ; "),a12zz);
}

TEST(Arithmetic, numericLiterals) {
  CMiniInterpreter interp;
  EXPECT_FLOAT_EQ( interp.EvaluateNumExpression("11+(12+12) / 4 +101;"),(11+(12+12) / 4 +101));
  EXPECT_FLOAT_EQ( interp.EvaluateNumExpression("3 + 4 * 2 * 1.5 - 6;"),(3 + 4 * 2 * 1.5 - 6));
  EXPECT_FLOAT_EQ( interp.EvaluateNumExpression("3 + 4 * 2 * 1.5 - 6 + 100 * 1.5;"),(3 + 4 * 2 * 1.5 - 6 + 100 * 1.5));
  EXPECT_FLOAT_EQ( interp.EvaluateNumExpression("3 + 4;"),(3 + 4));
  EXPECT_FLOAT_EQ( interp.EvaluateNumExpression(" 3 ;"),(3 ));
  EXPECT_FLOAT_EQ( interp.EvaluateNumExpression("12 / 4;"),(12 / 4));
}

TEST(Arithmetic, Mixed) {
  CMiniInterpreter interp;
  float pi = 3.1415926;
  float a12zz = 34.523;
  interp.PreloadVariable("a12zz",a12zz);
  interp.PreloadVariable("pi",pi);
  EXPECT_FLOAT_EQ( interp.EvaluateNumExpression("(1.0+1.0)/345;"),((1.0+1.0)/345.0));
  EXPECT_FLOAT_EQ( interp.EvaluateNumExpression("11+12+12 / 4 +101;"),(11+12+12 / 4 +101));
  EXPECT_FLOAT_EQ( interp.EvaluateNumExpression("-1;"),(-1));
  EXPECT_FLOAT_EQ( interp.EvaluateNumExpression("2 * -1;"),(2 * -1));
  EXPECT_FLOAT_EQ( interp.EvaluateNumExpression("a12zz * -1;"),(a12zz * -1));
  EXPECT_FLOAT_EQ( interp.EvaluateNumExpression("a12zz*-1;"),(a12zz*-1));

  EXPECT_FLOAT_EQ( interp.EvaluateNumExpression("3 + 4 * 2 * 1.5 - 6; "),(3 + 4 * 2 * 1.5 - 6)  );
  EXPECT_FLOAT_EQ( interp.EvaluateNumExpression("1.3 +-3.4 * 2 * 1.5 - 6; "),(1.3 +-3.4 * 2 * 1.5 - 6)  );
  EXPECT_FLOAT_EQ( interp.EvaluateNumExpression("1.3 \n +-3.4 * 2 * (pi -6) + 0.001; "),(1.3 +-3.4 * 2.0F * (pi -6.0F) + 0.001F)  );
}
