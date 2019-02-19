#include <gtest/gtest.h> // googletest header file
#include "include/CMiniInterpreter.h"

TEST(TestLocalVariables, Simple )
{
  CMiniInterpreter interp;
  const char * ym_script = R"(
     print("script start");
     float azimut = 3;
     float elevation = 22;
     float counter = 0;

     function measure() {
        float index = 3;
        while (index) {
          counter = counter + 1;
          index = index - 1;
        }
     }
     print(counter);

   )";
  interp.InterpretCode(ym_script);
  //isNanCheck(interp.GetFloatValue("index"));
  EXPECT_FLOAT_EQ( interp.GetFloatValue("counter"),0);
  ASSERT_EQ(interp.ExecuteFunction("measure"),true);
  EXPECT_FLOAT_EQ( interp.GetFloatValue("counter"),3);
  ASSERT_EQ(interp.ExecuteFunction("measure_bla"),false);
  //isNanCheck(interp.GetFloatValue("index"));
  ASSERT_EQ(interp.ExecuteFunction("measure"),true);
  EXPECT_FLOAT_EQ( interp.GetFloatValue("counter"),6);
  //isNanCheck(interp.GetFloatValue("index"));
}
