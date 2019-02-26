
#include <gtest/gtest.h> // googletest header file
#include "include/CMiniInterpreter.h"
#include <math.h>

TEST(TestPreloadVariable, Simple )
{

  CMiniInterpreter interp;
  ASSERT_EQ(interp.PreloadVariable("aa",34.56F),true);
  EXPECT_FLOAT_EQ( interp.GetFloatValue("aa"),34.56F);
  ASSERT_EQ(interp.PreloadVariable("aa",3.0F),false);
  EXPECT_FLOAT_EQ( interp.GetFloatValue("aa"),3.0F);
  ASSERT_EQ(interp.PreloadVariable("aast",std::string("kkkkl")),true);
  EXPECT_STREQ(interp.GetStringValue("aast").c_str(),"kkkkl");
  ASSERT_EQ(interp.PreloadVariable("aast",std::string("_____")),false);
  EXPECT_STREQ(interp.GetStringValue("aast").c_str(),"_____");
  interp.Clean();
  ASSERT_EQ(interp.PreloadVariable("aast",std::string("kkkkl")),true);
  ASSERT_EQ(interp.PreloadVariable("aa",34.56F),true);
  ASSERT_EQ(interp.PreloadVariable("azimut",56.99F),true);
  ASSERT_EQ(interp.PreloadVariable("sendero",-1.87F),true);

  ASSERT_EQ(interp.DeleteVariable("aa"),true);
  EXPECT_FLOAT_EQ( interp.GetFloatValue("azimut"),56.99F);
  ASSERT_TRUE(isnan(interp.GetFloatValue("aa")));
  ASSERT_EQ(interp.PreloadVariable("aa",99.56F),true);
  EXPECT_FLOAT_EQ( interp.GetFloatValue("azimut"),56.99F);
  EXPECT_FLOAT_EQ( interp.GetFloatValue("aa"),99.56F);
  ASSERT_EQ(interp.DeleteVariable("azimut"),true);
  ASSERT_TRUE(isnan( interp.GetFloatValue("azimut")));
  ASSERT_EQ(interp.PreloadVariable("azimut",99.56F),true);
  ASSERT_EQ(interp.PreloadVariable("azimut",99.56F),false);
  ASSERT_EQ(interp.DeleteVariable("inexistent"),false);

}
