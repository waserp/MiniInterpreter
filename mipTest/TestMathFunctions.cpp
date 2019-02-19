#include <gtest/gtest.h> // googletest header file
#include "include/CMiniInterpreter.h"

TEST(TestMathFunctions, Simple )
{
    CMiniInterpreter interp;
  interp.InterpretCode("\nfloat[] data; data[2] = 435; data[1] = log10(data[2]); float bs1=data[1];");
  EXPECT_FLOAT_EQ( interp.GetFloatValue("bs1"),log10(435.0F));
  interp.InterpretCode("\n data[2] = 435; data[1] = sqrt(data[2]);  bs1=data[1];");
  EXPECT_FLOAT_EQ( interp.GetFloatValue("bs1"),sqrt(435.0F));
  interp.InterpretCode("\n data[2] = 435; data[1] = log(data[2]);  bs1=data[1];");
  EXPECT_FLOAT_EQ( interp.GetFloatValue("bs1"),log(435.0F));
  interp.InterpretCode("\n data[2] = 43; data[1] = cos(data[2]);  bs1=data[1];");
  EXPECT_FLOAT_EQ( interp.GetFloatValue("bs1"),cos(43.0F));
  interp.InterpretCode("\n data[2] = 43; data[1] = cos(data[2]);  bs1=data[1];");
  EXPECT_FLOAT_EQ( interp.GetFloatValue("bs1"),cos(43.0F));

  const char * ym_script = R"(
     print(-1);
     float t=0;
     float index = 0; // sorry have to use float for index
     while ( index < 60) {
       t = index / 10;
       data[index] = 14.3 + sin(t);
       index = index + 1;
     }
     float meanval = mean(data[]);
     float stddevval = stddev(data[]);
     float minval = min(data[]);
     float minval2 = min(data[],1.0);
     float minval3 = min(data[],-1.0);
     float minval4 = min(-3,data[],16.0);
     float maxval1 = max(-3,data[],16.0);
     float maxval2 = max(-3,data[]);
     print("meanval=",meanval," stddev=", stddevval, "  ", data[]);
   )";
  interp.InterpretCode(ym_script);
  EXPECT_FLOAT_EQ( interp.GetFloatValue("meanval"),14.308961);
  EXPECT_FLOAT_EQ( interp.GetFloatValue("stddevval"),0.728280);
  EXPECT_FLOAT_EQ( interp.GetFloatValue("minval"),13.300077);
  EXPECT_FLOAT_EQ( interp.GetFloatValue("minval2"),1);
  EXPECT_FLOAT_EQ( interp.GetFloatValue("minval3"),-1);
  EXPECT_FLOAT_EQ( interp.GetFloatValue("minval4"),-3);
  EXPECT_FLOAT_EQ( interp.GetFloatValue("maxval1"),16);
  EXPECT_FLOAT_EQ( interp.GetFloatValue("maxval2"),15.299574);

}
