#include <gtest/gtest.h> // googletest header file
#include "include/CMiniInterpreter.h"

TEST(TestFloatArrays, Simple )
{

  CMiniInterpreter interp;
  interp.InterpretCode(" float[] foo; ");
  interp.InterpretCode(" foo[7]= 7.12;");
  interp.InterpretCode(" float a = foo[7] * 3.12;");
  EXPECT_FLOAT_EQ( interp.GetFloatValue("a"), 22.2144);
  interp.InterpretCode(" float[] data; ");
  interp.InterpretCode(" data[0] = 1.1; data[1] = 20.4;  data[2] = 300.12; float onV = 0; float cnt = 0; while (cnt<3) {  onV = onV + data[cnt]; cnt = cnt + 1;}   print(onV)");
  EXPECT_FLOAT_EQ( interp.GetFloatValue("onV"), 321.62);
  interp.InterpretCode(" data[ 1 + 4 * 2] = 88.32; onV = data[9];");
  EXPECT_FLOAT_EQ( interp.GetFloatValue("onV"), 88.32);


  interp.InterpretCode(" float[] bad;\n bad[1]= 1;\n bad[2]= 3;\n bad[3]= 1;\n bad[3] = bad[1] + bad[2];\n float enval = bad[3];\n ");
  EXPECT_FLOAT_EQ( interp.GetFloatValue("enval"), 4);
  //std::cout << "k-------------------------------\n";
  interp.InterpretCode("  float[] sindata;\n float t = 0.5;\n  sindata[4]= sin(t);\n float retval = sindata[4];\nprint(sindata[-1]);");
  EXPECT_FLOAT_EQ(interp.GetFloatValue("retval"),sin(0.5F) );
  interp.InterpretCode(" print(\"data=\",data[])");
  interp.InterpretCode(" data[0] = 1; data[1]=0; print(data[]); print(\"data\",data[0]);");
  interp.InterpretCode(" data[0] = 1; data[1]=0; float d1 = data[1]; float sd0 = sin(data[0]);");
  //std::cout << "k-------------------------------\n";
  EXPECT_FLOAT_EQ(interp.GetFloatValue("sd0"),sin(1.0F) );
  interp.InterpretCode(" float ix = -1; data[0] = 1.8; data[1]=0.65; data[2]=2.0; data[3]=0; data[4]= data[2] + data[1] * sin(data[ix + 1]); float sd4=data[4];");
  interp.InterpretCode(" print(data[],\"   \",sd4);");
  //std::cout << "k-------------------------------\n";
  EXPECT_FLOAT_EQ(interp.GetFloatValue("sd4"),(2.0 + 0.65 * sin(1.8F) ) );
  interp.InterpretCode(" data[0] = 2; data[1]=0.65; data[2]=27; data[3]=log10(data[data[0]]); float sd3 = data[3];");
  EXPECT_FLOAT_EQ(interp.GetFloatValue("sd3"),(log10(27) ) );
}

TEST(TestFloatArrays, Initializers )
{
  CMiniInterpreter interp;
  interp.InterpretCode(" float[] data = [1,3 * 7 + 1,2.3,8]; print(\"data=\",data[-1]);\n float a0 = data[0];float a1 = data[1];float a2 = data[2];float a3 = data[3];");
  EXPECT_FLOAT_EQ( interp.GetFloatValue("a0"), 1);
  EXPECT_FLOAT_EQ( interp.GetFloatValue("a1"), 22);
  EXPECT_FLOAT_EQ( interp.GetFloatValue("a2"), 2.3);
  EXPECT_FLOAT_EQ( interp.GetFloatValue("a3"), 8);
}
