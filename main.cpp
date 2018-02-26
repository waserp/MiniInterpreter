#include <stdio.h>


#include "CWppInterpreter.h"


const char* code = "\nfloat zebra = 33.7; float a = 5;\n   float b = a + 5 * a;\n   float c = (a + b) * 4";

#include <iostream>

CMiniInterpreter interp;
float Calculate(std::string p_expression);
int main(int argc, char **argv)
{
  //std::cout << Calculate("3 + 4 * 2 / ( 1 - 5 ) ^ 2 ^ 3;") << std::endl;

  
  if ( 9 != interp.EvaluateNumExpression("3 + 4 * 2 * 1.5 - 6; ")) { std::cout << "Error " << std::endl; return -1;  }
  if ( 110 != interp.EvaluateNumExpression("3 + 4 * 2 * 1.5 - 6 + 100.6 + 0.4; ")) { std::cout << "Error " << std::endl; return -1;  }
  if ( 159 != interp.EvaluateNumExpression("3 + 4 * 2 * 1.5 - 6 + 100 * 1.5; ")) { std::cout << "Error " << std::endl; return -1;  }
  if ( 7 != interp.EvaluateNumExpression("3 + 4; ")) { std::cout << "Error " << std::endl; return -1;  }
  if ( 3!= interp.EvaluateNumExpression("3 ; ")) { std::cout << "Error " << std::endl; return -1;  }
  if ( 3!= interp.EvaluateNumExpression("12 / 4 ; ")) { std::cout << "Error " << std::endl; return -1;  }
  if ( 127!= interp.EvaluateNumExpression("11+12+12 / 4 +101; ")) { std::cout << "Error " << std::endl; return -1;  }
  if ( 118!= interp.EvaluateNumExpression("11+(12+12) / 4 +101; ")) { std::cout << "Error " << std::endl; return -1;  }
  //interp.InterpretCode(code);
	
	return 0;
}
