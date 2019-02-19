#include <gtest/gtest.h> // googletest header file
#include "include/CMiniInterpreter.h"

bool DebugCallBack(uint32_t line, std::map<std::string, CVariable*>& Varmap)
{
  std::cout << "\n at line : " << line << "\n";
  for (auto var : Varmap) {
    std::cout << "   " << var.second->GetName() << "   " << var.second->GetString() << std::endl;
  }
  return false;
}

TEST(TestDebugCallback, Simple )
{

  CMiniInterpreter interp;
  bool CatchFlag = false;
  try {
    CatchFlag = false;
    interp.InterpretCode(" \n\n float a; float a; ");
  } catch (const std::exception& e) {
    std::cout << "Script failed totaly expected with: " << e.what() << std::endl;
    CatchFlag = true;
  }
  ASSERT_EQ(CatchFlag,true);
  try {
    CatchFlag = false;
    interp.InterpretCode(" \n\n float au = lk; ");
  } catch (const std::exception& e) {
    std::cout << "Script failed totaly expected with: " << e.what() << std::endl;
    CatchFlag = true;
  }
  ASSERT_EQ(CatchFlag,true);
  try {
    CatchFlag = false;
    interp.InterpretCode(" \n\n float aua  ");
  } catch (const std::exception& e) {
    std::cout << "Script failed totaly expected with: " << e.what() << std::endl;
    CatchFlag = true;
  }
  ASSERT_EQ(CatchFlag,true);
  try {
    CatchFlag = false;
    interp.InterpretCode(" \n\n float[] auat;\n auat = 8; ");
  } catch (const std::exception& e) {
    std::cout << "Script failed totaly expected with: " << e.what() << std::endl;
    CatchFlag = true;
  }
  ASSERT_EQ(CatchFlag,true);
  interp.Clean();
  interp.RegisterStatementCallBack(DebugCallBack);
  interp.InterpretCode(" \n\n float aurora = 8;\n float epsi = 8 + aurora; \n print(\"bla\");\n ");

}
