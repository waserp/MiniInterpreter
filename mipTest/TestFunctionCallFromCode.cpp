
#include <gtest/gtest.h> // googletest header file
#include "include/CMiniInterpreter.h"

TEST(TestFunctionCallFromCode, Simple) {
  CMiniInterpreter interp;
  const char * ym_script = R"(


     function Incrementer() {
       cnt = cnt + 1;
     }

     function IncrementCaller() {
       Incrementer();
       Incrementer();
     }

     function WhileIncrementer() {
       float sbcntr = 5;
       while (sbcntr) {
         Incrementer();
         sbcntr = sbcntr - 1;
       }
     }

     float cnt = 0;


     function testfun() {
       cnt = cnt + 5;
       print("testfun");
     }


     testfun();
     float aCnt = cnt;
     print("aCnt=",aCnt);
     testfun();
     float bCnt = cnt;
     print("bCnt=",bCnt);

     IncrementCaller();
     float cCnt = cnt;
     print("cCnt=",cCnt);
     WhileIncrementer();
     WhileIncrementer();
     float dCnt = cnt;
     print("dCnt=",dCnt);
   )";
  interp.InterpretCode(ym_script);
  EXPECT_FLOAT_EQ( interp.GetFloatValue("aCnt"),5);
  EXPECT_FLOAT_EQ( interp.GetFloatValue("bCnt"),10);
  EXPECT_FLOAT_EQ( interp.GetFloatValue("cCnt"),12);
  EXPECT_FLOAT_EQ( interp.GetFloatValue("dCnt"),22);
}
