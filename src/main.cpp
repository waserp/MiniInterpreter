#include <stdio.h>


#include "include/CWppInterpreter.h"
#include "include/CColors.h"

const char* code = "\nfloat zebra = 33.7; float a = 5;\n   float b = a + 5 * a;\n   float c = (a + b) * 4";

#include <iostream>


static uint32_t testCountPassed = 0;
static uint32_t TotaltestCountPassed = 0;
static uint32_t testSetsPassed = 0;

bool equalFloat(float a , float b)
{
  std::cout << "  diff  " << fabs(a-b) << std::endl;
  if (fabs(a-b)<0.0001) {testCountPassed++; return true;}
  std::cout << Colors::red << " ERROR " << " evaluated: " << a << " expected " << b << Colors::white << std::endl;
  (void) system("read a");
  exit(-1);
  return false;
}




#define PassedMessage() std::cout << Colors::green << __func__  << ": Number of Tests passed: " << testCountPassed << Colors::white << std::endl; TotaltestCountPassed += testCountPassed; testCountPassed = 0; testSetsPassed+=1;

#define EndReport() std::cout << Colors::green << "Total " << TotaltestCountPassed << " Tests passed in " << testSetsPassed << " test-sets\n";

void TestNumericEvaluator()
{
  CMiniInterpreter interp;
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

  PassedMessage();
}


void TestNumericBoleanEvaluator() {
  CMiniInterpreter interp;
  equalFloat( interp.EvaluateNumExpression("5 < 6;"),(5 < 6));
  equalFloat( interp.EvaluateNumExpression("5 > 6;"),(5 > 6));
  equalFloat( interp.EvaluateNumExpression("5 == 6;"),(5 == 6));
  equalFloat( interp.EvaluateNumExpression("-1 == -1;"),(-1 == -1));
  equalFloat( interp.EvaluateNumExpression("3 + 1 == 1 + 2;"),(3 + 1 == 1 + 2));
  equalFloat( interp.EvaluateNumExpression("9.6 + 1 < 2 + 2;"),(9.6 + 1 < 2 + 2));  // puh use a parenthesis for this things
  PassedMessage();
}

void TestWhileFlowControl() {
  CMiniInterpreter interp;
  interp.InterpretCode("  float bar = 2; while(bar < 4) { print(\"{}{{bar=\",bar); bar = bar +1;}  print(\"exit\");  ");
  interp.InterpretCode("  float statusbar = 2; float count = 0; while(count == 0 ) { print(\"{}{{statusbar=\",statusbar); statusbar = statusbar +1; count = 1 + count; }  print(\"exit\");  ");
  interp.InterpretCode("  float cucumber = 4; while(cucumber != 0 ) { print(\"{}{{cucumber=\",cucumber); cucumber = cucumber -1; }  print(\"by cucumber\");  ");
  equalFloat( interp.GetFloatValue("bar"), 4);
  equalFloat( interp.GetFloatValue("statusbar"), 3);
  equalFloat( interp.GetFloatValue("cucumber"), 0);
  PassedMessage();
}



//float Calculate(std::string p_expression);
int main(int argc, char **argv)
{
  TestNumericEvaluator();
  TestNumericBoleanEvaluator();
  TestWhileFlowControl();

  EndReport();

/*
  interp.PreloadVariable("12zz",34.523);
  interp.PreloadVariable("pi",3.1415926); float pi = 3.1415926; float a12zz = 34.523;

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



//  interp.InterpretCode("float foo = 6 * (1 + 2);\n print(\" hello:\",34.3,\" foo is:\",foo);\n  print(\"\nkk\n\"); sin(0.1);  ");


//  interp.InterpretCode("        float bar = (sin(0.1) + 1.1) *2.0;  print(\"bar=\",bar,\"\n\");");
//  equalFloat( interp.GetFloatValue("bar"), ((sin(0.1) + 1.1) *2.0 ));

  //interp.InterpretCode("  foo = 6 * (1 + 2);  bar=foo*1.23;   ");
  //interp.InterpretCode("  float bar = 2;  bar= bar - 1;  ");

  //interp.InterpretCode("  float bar = 2; while(bar) { print(\"{}{{bar=\",bar); bar = bar -1;}  print(\"exit\");  ");


  //interp.InterpretCode("  float bar = 2; while(bar < 4) { print(\"{}{{bar=\",bar); bar = bar +1;}  print(\"exit\");  ");


	return 0;
}
