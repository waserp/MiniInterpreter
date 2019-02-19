#include <gtest/gtest.h> // googletest header file
#include "include/CMiniInterpreter.h"

TEST(TestIfFlowControl, Simple )
{
  CMiniInterpreter interp;
  interp.InterpretCode(" float globVar = 1; if (globVar==1) { globVar=3; } else { globVar=0; } print(globVar);  ");
  EXPECT_FLOAT_EQ( interp.GetFloatValue("globVar"), 3);
  interp.InterpretCode(" globVar = 1; if (globVar!=1) { globVar=3; } else { globVar=0; } print(globVar);  ");
  EXPECT_FLOAT_EQ( interp.GetFloatValue("globVar"), 0);
  interp.InterpretCode("  globVar = 1; if (globVar==1) { globVar=3; print(\"no else case\n\"); }  print(globVar);  ");
  EXPECT_FLOAT_EQ( interp.GetFloatValue("globVar"), 3);
  interp.InterpretCode("  globVar = 7; if (globVar<7) { globVar=3; print(\"no else case\n\"); }  print( \"if not executed:\", globVar);  ");
  EXPECT_FLOAT_EQ( interp.GetFloatValue("globVar"), 7);
  interp.InterpretCode("  globVar = 7; float cnt = 3; if (globVar<7) { while (cnt>0) { cnt = cnt -1; print( \"inwhl \"); } } print( \"done\", globVar);  ");
  EXPECT_FLOAT_EQ( interp.GetFloatValue("globVar"), 7);
  EXPECT_FLOAT_EQ( interp.GetFloatValue("cnt"), 3);
  interp.InterpretCode("  globVar = 7;  cnt = 3; if (globVar<7.08) { while (cnt>0) { cnt = cnt -1; print( \"inwhl \"); } } print( \"done\", globVar);  ");
  EXPECT_FLOAT_EQ( interp.GetFloatValue("cnt"), 0);

}
