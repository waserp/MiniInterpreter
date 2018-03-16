#include <stdio.h>


#include "include/CWppInterpreter.h"
#include "include/CColors.h"
#include <map>
#include <string>
#include <cmath>

const char* code = "\nfloat zebra = 33.7; float a = 5;\n   float b = a + 5 * a;\n   float c = (a + b) * 4";

#include <iostream>


static uint32_t testCountPassed = 0;
static uint32_t TotaltestCountPassed = 0;
static uint32_t testSetsPassed = 0;

bool equalBool(bool a, bool b)
{
  if (a==b) {testCountPassed++; return true;}
  std::cout << Colors::red << " ERROR " << " evaluated: " << a << " expected " << b << Colors::white << std::endl;
  exit(-1);
  return false;
}

bool equalFloat(float a , float b)
{
  //std::cout << "  diff  " << fabs(a-b) << std::endl;
  if (fabs(a-b)<0.0001) {testCountPassed++; return true;}
  std::cout << Colors::red << " ERROR " << " evaluated: " << a << " expected " << b << Colors::white << std::endl;
  std::cout << system("read a");
  exit(-1);
  return false;
}

bool equalString(std::string a, std::string b)
{
  if (a.compare(b)== 0) { testCountPassed++; return true;}
  std::cout << Colors::red << " ERROR " << " evaluated: " << a << " expected " << b << Colors::white << std::endl;
  exit(-1);
  return false;
}

bool isNanCheck(float a)
{
  std::cout << "nan check" << std::endl;
  if (std::isnan(a)==0) {
    std::cout << Colors::red << " ERROR " << " Expected nan but found: " << a << Colors::white << std::endl;
    exit(-1);
    return false;
  }
  testCountPassed++; return true;
}

#define EnterTest() std::cout << Colors::green << "\n--------------------------------------------------------------------------\nentering " << __func__  << std::endl;
#define PassedMessage() std::cout << Colors::green << __func__  << ": Number of Tests passed: " << testCountPassed << Colors::white << std::endl; TotaltestCountPassed += testCountPassed; testCountPassed = 0; testSetsPassed+=1;

#define EndReport() std::cout << Colors::green << "Total " << TotaltestCountPassed << " Tests passed in " << testSetsPassed << " test-sets\n";

void TestNumericEvaluator()
{
  EnterTest();
  CMiniInterpreter interp;
  interp.PreloadVariable("a12zz",34.523);
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
  equalFloat( interp.EvaluateNumExpression("a12zz * -1;"),(a12zz * -1));
  equalFloat( interp.EvaluateNumExpression("a12zz*-1;"),(a12zz*-1));

  equalFloat( interp.EvaluateNumExpression("3 + 4 * 2 * 1.5 - 6; "),(3 + 4 * 2 * 1.5 - 6)  );
  equalFloat( interp.EvaluateNumExpression("1.3 +-3.4 * 2 * 1.5 - 6; "),(1.3 +-3.4 * 2 * 1.5 - 6)  );
  equalFloat( interp.EvaluateNumExpression("1.3 \n +-3.4 * 2 * (pi -6) + 0.001; "),(1.3 +-3.4 * 2.0F * (pi -6.0F) + 0.001F)  );

  PassedMessage();
}


void TestNumericBoleanEvaluator() {
  EnterTest();
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
  EnterTest();
  CMiniInterpreter interp;
  interp.InterpretCode("  float bar = 2; while(bar < 4) { print(\"{}{{bar=\",bar); bar = bar +1;}  print(\"exit\");  ");
  interp.InterpretCode("  float statusbar = 2; float count = 0; while(count == 0 ) { print(\"{}{{statusbar=\",statusbar); statusbar = statusbar +1; count = 1 + count; }  print(\"exit\");  ");
  interp.InterpretCode("  float cucumber = 4; while(cucumber != 0 ) { print(\"{}{{cucumber=\",cucumber); cucumber = cucumber -1; }  print(\"by cucumber\");  ");
  equalFloat( interp.GetFloatValue("bar"), 4);
  equalFloat( interp.GetFloatValue("statusbar"), 3);
  equalFloat( interp.GetFloatValue("cucumber"), 0);
  PassedMessage();
}

void TestFunctionCalls() {
  EnterTest();
  CMiniInterpreter interp;
  interp.InterpretCode(" float globVar = 1; function fooNoPar () { print(\"fooNoPar\", globVar ,\"\n\"); globVar = 7; }  fooNoPar(2,3);  print(globVar);  ");
  equalFloat( interp.GetFloatValue("globVar"), 7); // set to 7 in function
  //interp.InterpretCode("  function foo (float cc, float dd) { print(\"fromfoo\",cc,\"\",dd,\"\") return cc + dd; }  foo(2,3);");
  PassedMessage();
}

void TestIfFlowControl() {
  EnterTest();
  CMiniInterpreter interp;
  interp.InterpretCode(" float globVar = 1; if (globVar==1) { globVar=3; } else { globVar=0; } print(globVar);  ");
  equalFloat( interp.GetFloatValue("globVar"), 3);
  interp.InterpretCode(" globVar = 1; if (globVar!=1) { globVar=3; } else { globVar=0; } print(globVar);  ");
  equalFloat( interp.GetFloatValue("globVar"), 0);
  interp.InterpretCode("  globVar = 1; if (globVar==1) { globVar=3; print(\"no else case\n\"); }  print(globVar);  ");
  equalFloat( interp.GetFloatValue("globVar"), 3);
  interp.InterpretCode("  globVar = 7; if (globVar<7) { globVar=3; print(\"no else case\n\"); }  print( \"if not executed:\", globVar);  ");
  equalFloat( interp.GetFloatValue("globVar"), 7);
  interp.InterpretCode("  globVar = 7; float cnt = 3; if (globVar<7) { while (cnt>0) { cnt = cnt -1; print( \"inwhl \"); } } print( \"done\", globVar);  ");
  equalFloat( interp.GetFloatValue("globVar"), 7);
  equalFloat( interp.GetFloatValue("cnt"), 3);
  interp.InterpretCode("  globVar = 7;  cnt = 3; if (globVar<7.08) { while (cnt>0) { cnt = cnt -1; print( \"inwhl \"); } } print( \"done\", globVar);  ");
  equalFloat( interp.GetFloatValue("cnt"), 0);
  PassedMessage();
}

void TestFloatArrays()
{
  EnterTest();
  CMiniInterpreter interp;
  interp.InterpretCode(" float[] foo; ");
  interp.InterpretCode(" foo[7]= 7.12;");
  interp.InterpretCode(" float a = foo[7] * 3.12;");
  equalFloat( interp.GetFloatValue("a"), 22.2144);
  interp.InterpretCode(" float[] data; ");
  interp.InterpretCode(" data[0] = 1.1; data[1] = 20.4;  data[2] = 300.12; float onV = 0; float cnt = 0; while (cnt<3) {  onV = onV + data[cnt]; cnt = cnt + 1;}   print(onV)");
  equalFloat( interp.GetFloatValue("onV"), 321.62);
  interp.InterpretCode(" data[ 1 + 4 * 2] = 88.32; onV = data[9];");
  equalFloat( interp.GetFloatValue("onV"), 88.32);


  interp.InterpretCode(" float[] bad;\n bad[1]= 1;\n bad[2]= 3;\n bad[3]= 1;\n bad[3] = bad[1] + bad[2];\n float enval = bad[3];\n ");
  equalFloat( interp.GetFloatValue("enval"), 4);
  //std::cout << "k-------------------------------\n";
  interp.InterpretCode("  float[] sindata;\n float t = 0.5;\n  sindata[4]= sin(t);\n float retval = sindata[4];\nprint(sindata[-1]);");
  equalFloat(interp.GetFloatValue("retval"),sin(0.5F) );
  interp.InterpretCode(" print(\"data=\",data[])");
  interp.InterpretCode(" data[0] = 1; data[1]=0; print(data[]); print(\"data\",data[0]);");
  interp.InterpretCode(" data[0] = 1; data[1]=0; float d1 = data[1]; float sd0 = sin(data[0]);");
  //std::cout << "k-------------------------------\n";
  equalFloat(interp.GetFloatValue("sd0"),sin(1.0F) );
  interp.InterpretCode(" float ix = -1; data[0] = 1.8; data[1]=0.65; data[2]=2.0; data[3]=0; data[4]= data[2] + data[1] * sin(data[ix + 1]); float sd4=data[4];");
  interp.InterpretCode(" print(data[],\"   \",sd4);");
  //std::cout << "k-------------------------------\n";
  equalFloat(interp.GetFloatValue("sd4"),(2.0 + 0.65 * sin(1.8F) ) );
  interp.InterpretCode(" data[0] = 2; data[1]=0.65; data[2]=27; data[3]=log10(data[data[0]]); float sd3 = data[3];");
  equalFloat(interp.GetFloatValue("sd3"),(log10(27) ) );
  PassedMessage();
}

void TestStrings()
{
  EnterTest();
  CMiniInterpreter interp;
  interp.InterpretCode(" string name; string color = \"green\"; string abc = \"aa\" \"bb\" ,\"cc\" color; ");
  equalString(interp.GetStringValue("color"),"green");
  equalString(interp.GetStringValue("abc"),"aabbccgreen");
  interp.InterpretCode(" float zz = 1.1; abc = abc + zz; print(abc); ");
  PassedMessage();
}

void TestFloatArrayInitializers()
{
  EnterTest();
  CMiniInterpreter interp;
  interp.InterpretCode(" float[] data = [1,3 * 7 + 1,2.3,8]; print(\"data=\",data[-1]);\n float a0 = data[0];float a1 = data[1];float a2 = data[2];float a3 = data[3];");
  equalFloat( interp.GetFloatValue("a0"), 1);
  equalFloat( interp.GetFloatValue("a1"), 22);
  equalFloat( interp.GetFloatValue("a2"), 2.3);
  equalFloat( interp.GetFloatValue("a3"), 8);
  PassedMessage();
}

float SampleMoveXY(std::vector<CVariable*>& plist)
{

  std::cout << "Sample Fun Called with parameter:";
  for (auto p : plist) {
    std::cout << p->GetString() << " ";
  }
  std::cout << "\n";
  return 0.0F;
}

void TestRegisterCustomBuiltInFun()
{
  EnterTest();
  CMiniInterpreter interp;
  interp.RegisterCustomBuiltIn("MoveXY", SampleMoveXY);
  interp.InterpretCode(" float zz=3.2;  MoveXY(\"A11\",34,zz );");
  PassedMessage();
}

void TestPreloadVariable()
{
  EnterTest();
  CMiniInterpreter interp;
  equalBool(interp.PreloadVariable("aa",34.56F),true);
  equalFloat( interp.GetFloatValue("aa"),34.56F);
  equalBool(interp.PreloadVariable("aa",3.0F),false);
  equalFloat( interp.GetFloatValue("aa"),3.0F);
  equalBool(interp.PreloadVariable("aast",std::string("kkkkl")),true);
  equalString(interp.GetStringValue("aast"),"kkkkl");
  equalBool(interp.PreloadVariable("aast",std::string("_____")),false);
  equalString(interp.GetStringValue("aast"),"_____");
  interp.Clean();
  equalBool(interp.PreloadVariable("aast",std::string("kkkkl")),true);
  equalBool(interp.PreloadVariable("aa",34.56F),true);
  equalBool(interp.PreloadVariable("azimut",56.99F),true);
  equalBool(interp.PreloadVariable("sendero",-1.87F),true);

  equalBool(interp.DeleteVariable("aa"),true);
  equalFloat( interp.GetFloatValue("azimut"),56.99F);
  isNanCheck( interp.GetFloatValue("aa"));
  equalBool(interp.PreloadVariable("aa",99.56F),true);
  equalFloat( interp.GetFloatValue("azimut"),56.99F);
  equalFloat( interp.GetFloatValue("aa"),99.56F);
  equalBool(interp.DeleteVariable("azimut"),true);
  isNanCheck( interp.GetFloatValue("azimut"));
  equalBool(interp.PreloadVariable("azimut",99.56F),true);
  equalBool(interp.PreloadVariable("azimut",99.56F),false);
  equalBool(interp.DeleteVariable("inexistent"),false);
  PassedMessage();
}
void TestExecuteFunction()
{
  EnterTest();
  CMiniInterpreter interp;
  interp.InterpretCode(" print(\"before\"); \n//cmt \n print(\"after // this is not a comment\"); \n//commenrt ");
  interp.InterpretCode(" print(\"before\"); \n function foo(){ print(\"hello from foo\"); }   print(\"after\"); \n//commenrt ");
  std::cout << "-----------\n";
  equalBool(interp.ExecuteFunction("foo"),true);
  PassedMessage();
}

//std::function<bool(uint32_t,      std::map<std::string, CVariable*>&)>
bool DebugCallBack(uint32_t line, std::map<std::string, CVariable*>& Varmap)
{
  std::cout << "\n at line : " << line << "\n";
  for (auto var : Varmap) {
    std::cout << "   " << var.second->GetName() << "   " << var.second->GetString() << std::endl;
  }
  return false;
}


void TestErrorChecking()
{
  EnterTest();
  CMiniInterpreter interp;
  bool CatchFlag = false;
  try {
    CatchFlag = false;
    interp.InterpretCode(" \n\n float a; float a; ");
  } catch (const std::exception& e) {
    std::cout << "Script failed totaly expected with: " << e.what() << std::endl;
    CatchFlag = true;
  }
  equalBool(CatchFlag,true);
  try {
    CatchFlag = false;
    interp.InterpretCode(" \n\n float au = lk; ");
  } catch (const std::exception& e) {
    std::cout << "Script failed totaly expected with: " << e.what() << std::endl;
    CatchFlag = true;
  }
  equalBool(CatchFlag,true);
  try {
    CatchFlag = false;
    interp.InterpretCode(" \n\n float aua  ");
  } catch (const std::exception& e) {
    std::cout << "Script failed totaly expected with: " << e.what() << std::endl;
    CatchFlag = true;
  }
  equalBool(CatchFlag,true);
  try {
    CatchFlag = false;
    interp.InterpretCode(" \n\n float[] auat;\n auat = 8; ");
  } catch (const std::exception& e) {
    std::cout << "Script failed totaly expected with: " << e.what() << std::endl;
    CatchFlag = true;
  }
  equalBool(CatchFlag,true);
  interp.Clean();
  interp.RegisterStatementCallBack(DebugCallBack);
  interp.InterpretCode(" \n\n float aurora = 8;\n float epsi = 8 + aurora; \n print(\"bla\");\n ");
  PassedMessage();
}

void TestMathFun()
{
  EnterTest();
  CMiniInterpreter interp;
  interp.InterpretCode("\nfloat[] data; data[2] = 435; data[1] = log10(data[2]); float bs1=data[1];");
  equalFloat( interp.GetFloatValue("bs1"),log10(435.0F));
  interp.InterpretCode("\n data[2] = 435; data[1] = sqrt(data[2]);  bs1=data[1];");
  equalFloat( interp.GetFloatValue("bs1"),sqrt(435.0F));
  interp.InterpretCode("\n data[2] = 435; data[1] = log(data[2]);  bs1=data[1];");
  equalFloat( interp.GetFloatValue("bs1"),log(435.0F));
  interp.InterpretCode("\n data[2] = 43; data[1] = cos(data[2]);  bs1=data[1];");
  equalFloat( interp.GetFloatValue("bs1"),cos(43.0F));
  interp.InterpretCode("\n data[2] = 43; data[1] = cos(data[2]);  bs1=data[1];");
  equalFloat( interp.GetFloatValue("bs1"),cos(43.0F));

  const char * ym_script = R"(
     print(-1);
     float t=0;
     float index = 0; // sorry have to use float for index
     while ( index < 60) {
       t = index / 10;
       data[index] = 14.3 + sin(t);
       index = index + 1;
     }
     float meanval = mean(data[]);
     float stddevval = stddev(data[]);
     float minval = min(data[]);
     float minval2 = min(data[],1.0);
     float minval3 = min(data[],-1.0);
     float minval4 = min(-3,data[],16.0);
     float maxval1 = max(-3,data[],16.0);
     float maxval2 = max(-3,data[]);
     print("meanval=",meanval," stddev=", stddevval, "  ", data[]);
   )";
  interp.InterpretCode(ym_script);
  equalFloat( interp.GetFloatValue("meanval"),14.308961);
  equalFloat( interp.GetFloatValue("stddevval"),0.728280);
  equalFloat( interp.GetFloatValue("minval"),13.300077);
  equalFloat( interp.GetFloatValue("minval2"),1);
  equalFloat( interp.GetFloatValue("minval3"),-1);
  equalFloat( interp.GetFloatValue("minval4"),-3);
  equalFloat( interp.GetFloatValue("maxval1"),16);
  equalFloat( interp.GetFloatValue("maxval2"),15.2996);
  PassedMessage();
}

void TestLocalVariablesFun()
{
  EnterTest();
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
  isNanCheck(interp.GetFloatValue("index"));
  equalFloat( interp.GetFloatValue("counter"),0);
  equalBool(interp.ExecuteFunction("measure"),true);
  equalFloat( interp.GetFloatValue("counter"),3);
  equalBool(interp.ExecuteFunction("measure_bla"),false);
  isNanCheck(interp.GetFloatValue("index"));
  equalBool(interp.ExecuteFunction("measure"),true);
  equalFloat( interp.GetFloatValue("counter"),6);
  isNanCheck(interp.GetFloatValue("index"));
  PassedMessage();
}

//float Calculate(std::string p_expression);
int main(int argc, char **argv)
{
  TestNumericEvaluator();
  TestNumericBoleanEvaluator();
  TestWhileFlowControl();
  TestFunctionCalls();
  TestIfFlowControl();
  TestFloatArrays();
  TestStrings();
  TestFloatArrayInitializers();
  TestRegisterCustomBuiltInFun();
  TestPreloadVariable();
  TestExecuteFunction();
  TestErrorChecking();
  TestMathFun();
  TestLocalVariablesFun();
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

	return 0;
}
