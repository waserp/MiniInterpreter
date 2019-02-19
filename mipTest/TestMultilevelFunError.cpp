#include <gtest/gtest.h> // googletest header file
#include "include/CMiniInterpreter.h"

TEST(TestMultilevelFunError, Simple )
{
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
       UndefinedVariable = 9;
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
  bool CatchFlag = false;
  try {
    interp.ExecuteFunction("main");
  } catch (const std::exception& e) {
    std::cout << "Script failed totaly expected with: " << e.what() << std::endl;
    CatchFlag = true;
  }
  ASSERT_EQ(CatchFlag,true);

  CatchFlag = false;
  try {
    interp.Clean();
    interp.InterpretCode("\nfloat a=0;\n = print(\"a\");\n");
  } catch (const std::exception& e) {
    std::cout << "Script failed totaly expected with: " << e.what() << std::endl;
    CatchFlag = true;
    std::cout << "set catchflag\n";
  }
  ASSERT_EQ(CatchFlag,true);

}
