
#include <gtest/gtest.h> // googletest header file
#include "include/CMiniInterpreter.h"

TEST(TestMultilevelFun, Simple) {
    CMiniInterpreter interp;
  const char * ym_script = R"(

    float a = 0;
    float b = 11;
    float c = 16;
    float d = 19;





     function main() {
       afun();
       bfun();
       afun();

       print("main done");
     }

     function cfun() {
       c = c * 3;
     }

     function afun() {
       a = a + 11;
     }

     function bfun() {
       afun();
       b = b + 1;
       cfun();
     }


   )";
  interp.InterpretCode(ym_script);
  interp.ExecuteFunction("main");
  EXPECT_FLOAT_EQ( interp.GetFloatValue("a"),33);
  EXPECT_FLOAT_EQ( interp.GetFloatValue("b"),12);
  EXPECT_FLOAT_EQ( interp.GetFloatValue("c"),48);

}
