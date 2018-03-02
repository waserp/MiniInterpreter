#include <stdio.h>


#include "include/CWppInterpreter.h"
#include "include/CColors.h"

const char* code = "\nfloat zebra = 33.7; float a = 5;\n   float b = a + 5 * a;\n   float c = (a + b) * 4";

#include <iostream>

bool equalFloat(float a , float b)
{
  std::cout << "  diff  " << fabs(a-b) << std::endl;
  if (fabs(a-b)<0.0001) return true;
  std::cout << " ERROR " << " evaluated: " << a << " expected " << b << std::endl;
  (void) system("read a");
  exit(-1);
  return false;
}



CMiniInterpreter interp;
float Calculate(std::string p_expression);
int main(int argc, char **argv)
{
/*
  interp.PreloadVariable("12zz",34.523);
  interp.PreloadVariable("pi",3.1415926); float pi = 3.1415926; float a12zz = 34.523;


  equalFloat( interp.EvaluateNumExpression("pi;"),(pi));
  equalFloat( interp.EvaluateNumExpression("11+(12+12) / 4 +101;"),(11+(12+12) / 4 +101));
  equalFloat( interp.EvaluateNumExpression("3 + 4 * 2 * 1.5 - 6;"),(3 + 4 * 2 * 1.5 - 6));
  equalFloat( interp.EvaluateNumExpression("3 + 4 * 2 * 1.5 - 6 + 100 * 1.5;"),(3 + 4 * 2 * 1.5 - 6 + 100 * 1.5));
  equalFloat( interp.EvaluateNumExpression("3 + 4;"),(3 + 4));
  equalFloat( interp.EvaluateNumExpression(" 3 ;"),(3 ));
  equalFloat( interp.EvaluateNumExpression("12 / 4;"),(12 / 4));

  equalFloat( interp.EvaluateNumExpression("(1.0+1.0)/345;"),((1.0+1.0)/345.0));
  equalFloat( interp.EvaluateNumExpression("11+12+12 / 4 +101;"),(11+12+12 / 4 +101));
  equalFloat( interp.EvaluateNumExpression("-1;"),(-1));
  equalFloat( interp.EvaluateNumExpression("2 * -1;"),(2 * -1));
  equalFloat( interp.EvaluateNumExpression("12zz * -1;"),(a12zz * -1));
  equalFloat( interp.EvaluateNumExpression("12zz*-1;"),(a12zz*-1));

  equalFloat( interp.EvaluateNumExpression("3 + 4 * 2 * 1.5 - 6; "),(3 + 4 * 2 * 1.5 - 6)  );
  equalFloat( interp.EvaluateNumExpression("1.3 +-3.4 * 2 * 1.5 - 6; "),(1.3 +-3.4 * 2 * 1.5 - 6)  );
  equalFloat( interp.EvaluateNumExpression("1.3 \n +-3.4 * 2 * (pi -6) + 0.001; "),(1.3 +-3.4 * 2.0F * (pi -6.0F) + 0.001F)  );
  //interp.InterpretCode(code);
  try {
    interp.EvaluateNumExpression("1.3\n +-3.4 * 2 * (pi -6) + 0.001 z; ");
  }
  catch (const std::exception& e) {
    std::cout << "Script failed totaly expected with: " << e.what() << std::endl;
  }

  try {
    interp.InterpretCode(" \n\nfoo = 6 * (1 + 2);\n\n  bar=foo*1.23;   ");
  }
  catch (const std::exception& e) {
    std::cout << "Script failed totaly expected with: " << e.what() << std::endl;
  }

  interp.InterpretCode("float foo = 6 * (1 + 2);\n float bar=foo*1.23;\n   ");
  equalFloat( interp.GetFloatValue("foo"), (6 * (1 + 2)));
  equalFloat( interp.GetFloatValue("bar"), (6.0 * (1.0 + 2.0))*1.23 );

  interp.InsertFunPointer("moo",";");
  try {    interp.InsertFunPointer("moo",";");    }
  catch (const std::exception& e) {    std::cout << "Script failed totaly expected with: " << e.what() << std::endl;  }
*/



  interp.InterpretCode("float foo = 6 * (1 + 2);\n print(\" hello:\",34.3,\" foo is:\",foo);\n  print(\"\nkk\n\"); sin(0.1);  ");


  interp.InterpretCode("float a = (sin(0.1) + 1.1) *2;  print(\"a=\",a,\"\n\");");

  std::cout << Colors::red << "bold red text\n" << Colors::yellow << "kkk" << Colors::white;
	return 0;
}
