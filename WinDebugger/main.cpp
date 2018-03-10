#include <iostream>
#include <fstream>
#include "../include/CWppInterpreter.h"
#include "../include/CwppWindowsDebugger.h"
using namespace std;


CMiniInterpreter interp;


int main(int argc, const char * argv[])
{
  const char * fname = "test.wpp";
  if (argc == 2) {
      fname = argv[1];
  }
  std::ifstream scriptFile(fname, ios::binary | ios::ate);
  size_t fisz = scriptFile.tellg();
  scriptFile.close();
  char * Script = new char [fisz + 1000];
  scriptFile.open(fname,ios::binary);
  if (!scriptFile.is_open()) { std::cout << "could not open scriptfile " << fname << std::endl; return -1;}
  scriptFile.read(Script,fisz);
  size_t readBytes = scriptFile.gcount();
  Script[readBytes] = 0;
  scriptFile.close();

  std::cout << Script << std::endl;


  interp.RegisterStatementCallBack(StepCallBack);
  OpenDebugger(Script);
  interp.InterpretCode(Script);
  EndDebugger();
  return 0;
}
