
#include <gtest/gtest.h> // googletest header file
#include "include/CMiniInterpreter.h"



TEST(DeviceCommands, Simple ) {
  CMiniInterpreter interp;
  //interp.SetDevice("ExaDeviceA");
  const char * ym_script = R"(


    //Result = ExaDeviceA.ExaCommand();



    function OnError()
    {

    }

  )";
  interp.InterpretCode(ym_script);


}
