#include <gtest/gtest.h> // googletest header file
#include "include/CMiniInterpreter.h"

TEST(TestSyntaxErrors, Simple )
{
  CMiniInterpreter interp;
  interp.InterpretCode("");
  bool CatchFlag = false;
  try {
    interp.InterpretCode(" ' ");
  } catch (const std::exception& e) {
    std::cout << "Script failed totaly expected with: " << e.what() << std::endl;
    CatchFlag = true;
  }
  ASSERT_EQ(CatchFlag,true);
  CatchFlag = false;
  try {
    interp.InterpretCode(" print('df'); ");
  } catch (const std::exception& e) {
    std::cout << "Script failed totaly expected with: " << e.what() << std::endl;
    CatchFlag = true;
  }
  ASSERT_EQ(CatchFlag,true);
//  CatchFlag = false;
//  try {
//    interp.InterpretCode(" float a=1;\n if (a) { ");
//  } catch (const std::exception& e) {
//    std::cout << "Script failed totaly expected with: " << e.what() << std::endl;
//    CatchFlag = true;
//  }
//  ASSERT_EQ(CatchFlag,true);
  CatchFlag = false;
  try {
    interp.InterpretCode(" function bla() { float a=1;\n if (a) { }");
  } catch (const std::exception& e) {
    std::cout << "Script failed totaly expected with: " << e.what() << std::endl;
    CatchFlag = true;
  }
  ASSERT_EQ(CatchFlag,true);

  CatchFlag = false;
  try {
    interp.InterpretCode(" function bla() { ' float a=1;\n if (a) {  }   }");
  } catch (const std::exception& e) {
    std::cout << "Script failed totaly expected with: " << e.what() << std::endl;
    CatchFlag = true;
  }
  ASSERT_EQ(CatchFlag,true);
}
