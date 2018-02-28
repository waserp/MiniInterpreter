#include <stdio.h>


#include "CWppInterpreter.h"


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
  //std::cout << Calculate("3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3;") << std::endl;

  if ( 118!= interp.EvaluateNumExpression("11+(12+12) / 4 +101; ")) { std::cout << "Error " << std::endl; return -1;  }

  if ( 9 != interp.EvaluateNumExpression("3 + 4 * 2 * 1.5 - 6; ")) { std::cout << "Error " << std::endl; return -1;  }
  if ( 110 != interp.EvaluateNumExpression("3 + 4 * 2 * 1.5 - 6 + 100.6 + 0.4; ")) { std::cout << "Error " << std::endl; return -1;  }
  if ( 159 != interp.EvaluateNumExpression("3 + 4 * 2 * 1.5 - 6 + 100 * 1.5; ")) { std::cout << "Error " << std::endl; return -1;  }
  if ( 7 != interp.EvaluateNumExpression("3 + 4; ")) { std::cout << "Error " << std::endl; return -1;  }
  if ( 3!= interp.EvaluateNumExpression("3 ; ")) { std::cout << "Error " << std::endl; return -1;  }
  if ( 3!= interp.EvaluateNumExpression("12 / 4 ; ")) { std::cout << "Error " << std::endl; return -1;  }
  if ( 127!= interp.EvaluateNumExpression("11+12+12 / 4 +101; ")) { std::cout << "Error " << std::endl; return -1;  }
  if ( -1!= interp.EvaluateNumExpression("-1; ")) { std::cout << "Error " << std::endl; return -1;  }
  if ( -2!= interp.EvaluateNumExpression("2 * -1; ")) { std::cout << "Error " << std::endl; return -1;  }
  interp.PreloadVariable("12zz",34);
  interp.PreloadVariable("pi",3.1415926); float pi = 3.1415926;
  if ( -34!= interp.EvaluateNumExpression("12zz * -1; ")) { std::cout << "Error " << std::endl; return -1;  }
  if ( -34!= interp.EvaluateNumExpression("12zz*-1;")) { std::cout << "Error " << std::endl; return -1;  }
  equalFloat( interp.EvaluateNumExpression("3 + 4 * 2 * 1.5 - 6; "),(3 + 4 * 2 * 1.5 - 6)  );
  equalFloat( interp.EvaluateNumExpression("1.3 +-3.4 * 2 * 1.5 - 6; "),(1.3 +-3.4 * 2 * 1.5 - 6)  );
  equalFloat( interp.EvaluateNumExpression("1.3 +-3.4 * 2 * (pi -6) + 0.001; "),(1.3 +-3.4 * 2.0F * (pi -6.0F) + 0.001F)  );
  //interp.InterpretCode(code);

	return 0;
}
