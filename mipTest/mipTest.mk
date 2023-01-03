##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=mipTest
ConfigurationName      :=Debug
WorkspacePath          :=/home/wasp/Projects/codelite
ProjectPath            :=/home/wasp/Projects/MiniInterpreter/mipTest
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Patrick Waser
Date                   :=28/11/22
CodeLitePath           :=/home/wasp/.codelite
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="mipTest.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -lpthread -lgtest
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)../. 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)pthread $(LibrarySwitch)gtest 
ArLibs                 :=  "pthread" "gtest" 
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O2 -std=c++11 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/TestSyntaxErrors.cpp$(ObjectSuffix) $(IntermediateDirectory)/TestRegisterCustomBuildInFun.cpp$(ObjectSuffix) $(IntermediateDirectory)/TestNumericBooleanEvaluator.cpp$(ObjectSuffix) $(IntermediateDirectory)/TestMultilevelFun.cpp$(ObjectSuffix) $(IntermediateDirectory)/TestStrings.cpp$(ObjectSuffix) $(IntermediateDirectory)/TestMathFunctions.cpp$(ObjectSuffix) $(IntermediateDirectory)/TestLocalVariablescpp.cpp$(ObjectSuffix) $(IntermediateDirectory)/TestMultilevelFunError.cpp$(ObjectSuffix) $(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/TestPreloadVariable.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/up_src_CVariable.cpp$(ObjectSuffix) $(IntermediateDirectory)/TestFunctionCallFromCode.cpp$(ObjectSuffix) $(IntermediateDirectory)/TestDeviceCommands.cpp$(ObjectSuffix) $(IntermediateDirectory)/TestWhileFlowControl.cpp$(ObjectSuffix) $(IntermediateDirectory)/TestDebugCallBack.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_src_CColors.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_src_MiniInterpreterEnums.cpp$(ObjectSuffix) $(IntermediateDirectory)/TestFloatArrays.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_src_CMiniInterpreter.cpp$(ObjectSuffix) $(IntermediateDirectory)/TestArithmeticExpressionsSimple.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/up_src_MathFun.cpp$(ObjectSuffix) $(IntermediateDirectory)/TestIfFlowControl.cpp$(ObjectSuffix) $(IntermediateDirectory)/TestFunctionCalls.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/TestSyntaxErrors.cpp$(ObjectSuffix): TestSyntaxErrors.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestSyntaxErrors.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestSyntaxErrors.cpp$(DependSuffix) -MM TestSyntaxErrors.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/wasp/Projects/MiniInterpreter/mipTest/TestSyntaxErrors.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestSyntaxErrors.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestSyntaxErrors.cpp$(PreprocessSuffix): TestSyntaxErrors.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestSyntaxErrors.cpp$(PreprocessSuffix) TestSyntaxErrors.cpp

$(IntermediateDirectory)/TestRegisterCustomBuildInFun.cpp$(ObjectSuffix): TestRegisterCustomBuildInFun.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestRegisterCustomBuildInFun.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestRegisterCustomBuildInFun.cpp$(DependSuffix) -MM TestRegisterCustomBuildInFun.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/wasp/Projects/MiniInterpreter/mipTest/TestRegisterCustomBuildInFun.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestRegisterCustomBuildInFun.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestRegisterCustomBuildInFun.cpp$(PreprocessSuffix): TestRegisterCustomBuildInFun.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestRegisterCustomBuildInFun.cpp$(PreprocessSuffix) TestRegisterCustomBuildInFun.cpp

$(IntermediateDirectory)/TestNumericBooleanEvaluator.cpp$(ObjectSuffix): TestNumericBooleanEvaluator.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestNumericBooleanEvaluator.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestNumericBooleanEvaluator.cpp$(DependSuffix) -MM TestNumericBooleanEvaluator.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/wasp/Projects/MiniInterpreter/mipTest/TestNumericBooleanEvaluator.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestNumericBooleanEvaluator.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestNumericBooleanEvaluator.cpp$(PreprocessSuffix): TestNumericBooleanEvaluator.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestNumericBooleanEvaluator.cpp$(PreprocessSuffix) TestNumericBooleanEvaluator.cpp

$(IntermediateDirectory)/TestMultilevelFun.cpp$(ObjectSuffix): TestMultilevelFun.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestMultilevelFun.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestMultilevelFun.cpp$(DependSuffix) -MM TestMultilevelFun.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/wasp/Projects/MiniInterpreter/mipTest/TestMultilevelFun.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestMultilevelFun.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestMultilevelFun.cpp$(PreprocessSuffix): TestMultilevelFun.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestMultilevelFun.cpp$(PreprocessSuffix) TestMultilevelFun.cpp

$(IntermediateDirectory)/TestStrings.cpp$(ObjectSuffix): TestStrings.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestStrings.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestStrings.cpp$(DependSuffix) -MM TestStrings.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/wasp/Projects/MiniInterpreter/mipTest/TestStrings.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestStrings.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestStrings.cpp$(PreprocessSuffix): TestStrings.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestStrings.cpp$(PreprocessSuffix) TestStrings.cpp

$(IntermediateDirectory)/TestMathFunctions.cpp$(ObjectSuffix): TestMathFunctions.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestMathFunctions.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestMathFunctions.cpp$(DependSuffix) -MM TestMathFunctions.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/wasp/Projects/MiniInterpreter/mipTest/TestMathFunctions.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestMathFunctions.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestMathFunctions.cpp$(PreprocessSuffix): TestMathFunctions.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestMathFunctions.cpp$(PreprocessSuffix) TestMathFunctions.cpp

$(IntermediateDirectory)/TestLocalVariablescpp.cpp$(ObjectSuffix): TestLocalVariablescpp.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestLocalVariablescpp.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestLocalVariablescpp.cpp$(DependSuffix) -MM TestLocalVariablescpp.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/wasp/Projects/MiniInterpreter/mipTest/TestLocalVariablescpp.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestLocalVariablescpp.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestLocalVariablescpp.cpp$(PreprocessSuffix): TestLocalVariablescpp.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestLocalVariablescpp.cpp$(PreprocessSuffix) TestLocalVariablescpp.cpp

$(IntermediateDirectory)/TestMultilevelFunError.cpp$(ObjectSuffix): TestMultilevelFunError.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestMultilevelFunError.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestMultilevelFunError.cpp$(DependSuffix) -MM TestMultilevelFunError.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/wasp/Projects/MiniInterpreter/mipTest/TestMultilevelFunError.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestMultilevelFunError.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestMultilevelFunError.cpp$(PreprocessSuffix): TestMultilevelFunError.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestMultilevelFunError.cpp$(PreprocessSuffix) TestMultilevelFunError.cpp

$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/wasp/Projects/MiniInterpreter/mipTest/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/TestPreloadVariable.cpp$(ObjectSuffix): TestPreloadVariable.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestPreloadVariable.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestPreloadVariable.cpp$(DependSuffix) -MM TestPreloadVariable.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/wasp/Projects/MiniInterpreter/mipTest/TestPreloadVariable.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestPreloadVariable.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestPreloadVariable.cpp$(PreprocessSuffix): TestPreloadVariable.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestPreloadVariable.cpp$(PreprocessSuffix) TestPreloadVariable.cpp

$(IntermediateDirectory)/up_src_CVariable.cpp$(ObjectSuffix): ../src/CVariable.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_src_CVariable.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_src_CVariable.cpp$(DependSuffix) -MM ../src/CVariable.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/wasp/Projects/MiniInterpreter/src/CVariable.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_src_CVariable.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_src_CVariable.cpp$(PreprocessSuffix): ../src/CVariable.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_src_CVariable.cpp$(PreprocessSuffix) ../src/CVariable.cpp

$(IntermediateDirectory)/TestFunctionCallFromCode.cpp$(ObjectSuffix): TestFunctionCallFromCode.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestFunctionCallFromCode.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestFunctionCallFromCode.cpp$(DependSuffix) -MM TestFunctionCallFromCode.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/wasp/Projects/MiniInterpreter/mipTest/TestFunctionCallFromCode.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestFunctionCallFromCode.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestFunctionCallFromCode.cpp$(PreprocessSuffix): TestFunctionCallFromCode.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestFunctionCallFromCode.cpp$(PreprocessSuffix) TestFunctionCallFromCode.cpp

$(IntermediateDirectory)/TestDeviceCommands.cpp$(ObjectSuffix): TestDeviceCommands.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestDeviceCommands.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestDeviceCommands.cpp$(DependSuffix) -MM TestDeviceCommands.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/wasp/Projects/MiniInterpreter/mipTest/TestDeviceCommands.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestDeviceCommands.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestDeviceCommands.cpp$(PreprocessSuffix): TestDeviceCommands.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestDeviceCommands.cpp$(PreprocessSuffix) TestDeviceCommands.cpp

$(IntermediateDirectory)/TestWhileFlowControl.cpp$(ObjectSuffix): TestWhileFlowControl.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestWhileFlowControl.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestWhileFlowControl.cpp$(DependSuffix) -MM TestWhileFlowControl.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/wasp/Projects/MiniInterpreter/mipTest/TestWhileFlowControl.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestWhileFlowControl.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestWhileFlowControl.cpp$(PreprocessSuffix): TestWhileFlowControl.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestWhileFlowControl.cpp$(PreprocessSuffix) TestWhileFlowControl.cpp

$(IntermediateDirectory)/TestDebugCallBack.cpp$(ObjectSuffix): TestDebugCallBack.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestDebugCallBack.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestDebugCallBack.cpp$(DependSuffix) -MM TestDebugCallBack.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/wasp/Projects/MiniInterpreter/mipTest/TestDebugCallBack.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestDebugCallBack.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestDebugCallBack.cpp$(PreprocessSuffix): TestDebugCallBack.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestDebugCallBack.cpp$(PreprocessSuffix) TestDebugCallBack.cpp

$(IntermediateDirectory)/up_src_CColors.cpp$(ObjectSuffix): ../src/CColors.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_src_CColors.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_src_CColors.cpp$(DependSuffix) -MM ../src/CColors.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/wasp/Projects/MiniInterpreter/src/CColors.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_src_CColors.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_src_CColors.cpp$(PreprocessSuffix): ../src/CColors.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_src_CColors.cpp$(PreprocessSuffix) ../src/CColors.cpp

$(IntermediateDirectory)/up_src_MiniInterpreterEnums.cpp$(ObjectSuffix): ../src/MiniInterpreterEnums.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_src_MiniInterpreterEnums.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_src_MiniInterpreterEnums.cpp$(DependSuffix) -MM ../src/MiniInterpreterEnums.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/wasp/Projects/MiniInterpreter/src/MiniInterpreterEnums.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_src_MiniInterpreterEnums.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_src_MiniInterpreterEnums.cpp$(PreprocessSuffix): ../src/MiniInterpreterEnums.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_src_MiniInterpreterEnums.cpp$(PreprocessSuffix) ../src/MiniInterpreterEnums.cpp

$(IntermediateDirectory)/TestFloatArrays.cpp$(ObjectSuffix): TestFloatArrays.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestFloatArrays.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestFloatArrays.cpp$(DependSuffix) -MM TestFloatArrays.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/wasp/Projects/MiniInterpreter/mipTest/TestFloatArrays.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestFloatArrays.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestFloatArrays.cpp$(PreprocessSuffix): TestFloatArrays.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestFloatArrays.cpp$(PreprocessSuffix) TestFloatArrays.cpp

$(IntermediateDirectory)/up_src_CMiniInterpreter.cpp$(ObjectSuffix): ../src/CMiniInterpreter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_src_CMiniInterpreter.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_src_CMiniInterpreter.cpp$(DependSuffix) -MM ../src/CMiniInterpreter.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/wasp/Projects/MiniInterpreter/src/CMiniInterpreter.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_src_CMiniInterpreter.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_src_CMiniInterpreter.cpp$(PreprocessSuffix): ../src/CMiniInterpreter.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_src_CMiniInterpreter.cpp$(PreprocessSuffix) ../src/CMiniInterpreter.cpp

$(IntermediateDirectory)/TestArithmeticExpressionsSimple.cpp$(ObjectSuffix): TestArithmeticExpressionsSimple.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestArithmeticExpressionsSimple.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestArithmeticExpressionsSimple.cpp$(DependSuffix) -MM TestArithmeticExpressionsSimple.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/wasp/Projects/MiniInterpreter/mipTest/TestArithmeticExpressionsSimple.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestArithmeticExpressionsSimple.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestArithmeticExpressionsSimple.cpp$(PreprocessSuffix): TestArithmeticExpressionsSimple.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestArithmeticExpressionsSimple.cpp$(PreprocessSuffix) TestArithmeticExpressionsSimple.cpp

$(IntermediateDirectory)/up_src_MathFun.cpp$(ObjectSuffix): ../src/MathFun.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_src_MathFun.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_src_MathFun.cpp$(DependSuffix) -MM ../src/MathFun.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/wasp/Projects/MiniInterpreter/src/MathFun.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_src_MathFun.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_src_MathFun.cpp$(PreprocessSuffix): ../src/MathFun.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_src_MathFun.cpp$(PreprocessSuffix) ../src/MathFun.cpp

$(IntermediateDirectory)/TestIfFlowControl.cpp$(ObjectSuffix): TestIfFlowControl.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestIfFlowControl.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestIfFlowControl.cpp$(DependSuffix) -MM TestIfFlowControl.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/wasp/Projects/MiniInterpreter/mipTest/TestIfFlowControl.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestIfFlowControl.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestIfFlowControl.cpp$(PreprocessSuffix): TestIfFlowControl.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestIfFlowControl.cpp$(PreprocessSuffix) TestIfFlowControl.cpp

$(IntermediateDirectory)/TestFunctionCalls.cpp$(ObjectSuffix): TestFunctionCalls.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestFunctionCalls.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestFunctionCalls.cpp$(DependSuffix) -MM TestFunctionCalls.cpp
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/wasp/Projects/MiniInterpreter/mipTest/TestFunctionCalls.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestFunctionCalls.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestFunctionCalls.cpp$(PreprocessSuffix): TestFunctionCalls.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestFunctionCalls.cpp$(PreprocessSuffix) TestFunctionCalls.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


