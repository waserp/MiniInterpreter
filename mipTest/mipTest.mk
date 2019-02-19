##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=mipTest
ConfigurationName      :=Debug
WorkspacePath          :=/home/waserp/Projects/Projects
ProjectPath            :=/home/waserp/Projects/MiniInterpreter/mipTest
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=waserp
Date                   :=19/02/19
CodeLitePath           :=/home/waserp/.codelite
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
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_src_CVariable.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_src_CColors.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_src_MiniInterpreterEnums.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_src_MathFun.cpp$(ObjectSuffix) $(IntermediateDirectory)/up_src_CMiniInterpreter.cpp$(ObjectSuffix) $(IntermediateDirectory)/TestArithmeticExpressionsSimple.cpp$(ObjectSuffix) $(IntermediateDirectory)/TestNumericBooleanEvaluator.cpp$(ObjectSuffix) $(IntermediateDirectory)/TestWhileFlowControl.cpp$(ObjectSuffix) $(IntermediateDirectory)/TestFunctionCalls.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/TestIfFlowControl.cpp$(ObjectSuffix) $(IntermediateDirectory)/TestFloatArrays.cpp$(ObjectSuffix) $(IntermediateDirectory)/TestStrings.cpp$(ObjectSuffix) $(IntermediateDirectory)/TestRegisterCustomBuildInFun.cpp$(ObjectSuffix) $(IntermediateDirectory)/TestPreloadVariable.cpp$(ObjectSuffix) $(IntermediateDirectory)/TestDebugCallBack.cpp$(ObjectSuffix) $(IntermediateDirectory)/TestMathFunctions.cpp$(ObjectSuffix) $(IntermediateDirectory)/TestLocalVariablescpp.cpp$(ObjectSuffix) $(IntermediateDirectory)/TestFunctionCallFromCode.cpp$(ObjectSuffix) $(IntermediateDirectory)/TestMultilevelFun.cpp$(ObjectSuffix) \
	$(IntermediateDirectory)/TestSyntaxErrors.cpp$(ObjectSuffix) $(IntermediateDirectory)/TestMultilevelFunError.cpp$(ObjectSuffix) 



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
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/waserp/Projects/MiniInterpreter/mipTest/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM main.cpp

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) main.cpp

$(IntermediateDirectory)/up_src_CVariable.cpp$(ObjectSuffix): ../src/CVariable.cpp $(IntermediateDirectory)/up_src_CVariable.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/waserp/Projects/MiniInterpreter/src/CVariable.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_src_CVariable.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_src_CVariable.cpp$(DependSuffix): ../src/CVariable.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_src_CVariable.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_src_CVariable.cpp$(DependSuffix) -MM ../src/CVariable.cpp

$(IntermediateDirectory)/up_src_CVariable.cpp$(PreprocessSuffix): ../src/CVariable.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_src_CVariable.cpp$(PreprocessSuffix) ../src/CVariable.cpp

$(IntermediateDirectory)/up_src_CColors.cpp$(ObjectSuffix): ../src/CColors.cpp $(IntermediateDirectory)/up_src_CColors.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/waserp/Projects/MiniInterpreter/src/CColors.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_src_CColors.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_src_CColors.cpp$(DependSuffix): ../src/CColors.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_src_CColors.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_src_CColors.cpp$(DependSuffix) -MM ../src/CColors.cpp

$(IntermediateDirectory)/up_src_CColors.cpp$(PreprocessSuffix): ../src/CColors.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_src_CColors.cpp$(PreprocessSuffix) ../src/CColors.cpp

$(IntermediateDirectory)/up_src_MiniInterpreterEnums.cpp$(ObjectSuffix): ../src/MiniInterpreterEnums.cpp $(IntermediateDirectory)/up_src_MiniInterpreterEnums.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/waserp/Projects/MiniInterpreter/src/MiniInterpreterEnums.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_src_MiniInterpreterEnums.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_src_MiniInterpreterEnums.cpp$(DependSuffix): ../src/MiniInterpreterEnums.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_src_MiniInterpreterEnums.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_src_MiniInterpreterEnums.cpp$(DependSuffix) -MM ../src/MiniInterpreterEnums.cpp

$(IntermediateDirectory)/up_src_MiniInterpreterEnums.cpp$(PreprocessSuffix): ../src/MiniInterpreterEnums.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_src_MiniInterpreterEnums.cpp$(PreprocessSuffix) ../src/MiniInterpreterEnums.cpp

$(IntermediateDirectory)/up_src_MathFun.cpp$(ObjectSuffix): ../src/MathFun.cpp $(IntermediateDirectory)/up_src_MathFun.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/waserp/Projects/MiniInterpreter/src/MathFun.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_src_MathFun.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_src_MathFun.cpp$(DependSuffix): ../src/MathFun.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_src_MathFun.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_src_MathFun.cpp$(DependSuffix) -MM ../src/MathFun.cpp

$(IntermediateDirectory)/up_src_MathFun.cpp$(PreprocessSuffix): ../src/MathFun.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_src_MathFun.cpp$(PreprocessSuffix) ../src/MathFun.cpp

$(IntermediateDirectory)/up_src_CMiniInterpreter.cpp$(ObjectSuffix): ../src/CMiniInterpreter.cpp $(IntermediateDirectory)/up_src_CMiniInterpreter.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/waserp/Projects/MiniInterpreter/src/CMiniInterpreter.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/up_src_CMiniInterpreter.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/up_src_CMiniInterpreter.cpp$(DependSuffix): ../src/CMiniInterpreter.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/up_src_CMiniInterpreter.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/up_src_CMiniInterpreter.cpp$(DependSuffix) -MM ../src/CMiniInterpreter.cpp

$(IntermediateDirectory)/up_src_CMiniInterpreter.cpp$(PreprocessSuffix): ../src/CMiniInterpreter.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/up_src_CMiniInterpreter.cpp$(PreprocessSuffix) ../src/CMiniInterpreter.cpp

$(IntermediateDirectory)/TestArithmeticExpressionsSimple.cpp$(ObjectSuffix): TestArithmeticExpressionsSimple.cpp $(IntermediateDirectory)/TestArithmeticExpressionsSimple.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/waserp/Projects/MiniInterpreter/mipTest/TestArithmeticExpressionsSimple.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestArithmeticExpressionsSimple.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestArithmeticExpressionsSimple.cpp$(DependSuffix): TestArithmeticExpressionsSimple.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestArithmeticExpressionsSimple.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestArithmeticExpressionsSimple.cpp$(DependSuffix) -MM TestArithmeticExpressionsSimple.cpp

$(IntermediateDirectory)/TestArithmeticExpressionsSimple.cpp$(PreprocessSuffix): TestArithmeticExpressionsSimple.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestArithmeticExpressionsSimple.cpp$(PreprocessSuffix) TestArithmeticExpressionsSimple.cpp

$(IntermediateDirectory)/TestNumericBooleanEvaluator.cpp$(ObjectSuffix): TestNumericBooleanEvaluator.cpp $(IntermediateDirectory)/TestNumericBooleanEvaluator.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/waserp/Projects/MiniInterpreter/mipTest/TestNumericBooleanEvaluator.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestNumericBooleanEvaluator.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestNumericBooleanEvaluator.cpp$(DependSuffix): TestNumericBooleanEvaluator.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestNumericBooleanEvaluator.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestNumericBooleanEvaluator.cpp$(DependSuffix) -MM TestNumericBooleanEvaluator.cpp

$(IntermediateDirectory)/TestNumericBooleanEvaluator.cpp$(PreprocessSuffix): TestNumericBooleanEvaluator.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestNumericBooleanEvaluator.cpp$(PreprocessSuffix) TestNumericBooleanEvaluator.cpp

$(IntermediateDirectory)/TestWhileFlowControl.cpp$(ObjectSuffix): TestWhileFlowControl.cpp $(IntermediateDirectory)/TestWhileFlowControl.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/waserp/Projects/MiniInterpreter/mipTest/TestWhileFlowControl.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestWhileFlowControl.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestWhileFlowControl.cpp$(DependSuffix): TestWhileFlowControl.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestWhileFlowControl.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestWhileFlowControl.cpp$(DependSuffix) -MM TestWhileFlowControl.cpp

$(IntermediateDirectory)/TestWhileFlowControl.cpp$(PreprocessSuffix): TestWhileFlowControl.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestWhileFlowControl.cpp$(PreprocessSuffix) TestWhileFlowControl.cpp

$(IntermediateDirectory)/TestFunctionCalls.cpp$(ObjectSuffix): TestFunctionCalls.cpp $(IntermediateDirectory)/TestFunctionCalls.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/waserp/Projects/MiniInterpreter/mipTest/TestFunctionCalls.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestFunctionCalls.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestFunctionCalls.cpp$(DependSuffix): TestFunctionCalls.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestFunctionCalls.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestFunctionCalls.cpp$(DependSuffix) -MM TestFunctionCalls.cpp

$(IntermediateDirectory)/TestFunctionCalls.cpp$(PreprocessSuffix): TestFunctionCalls.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestFunctionCalls.cpp$(PreprocessSuffix) TestFunctionCalls.cpp

$(IntermediateDirectory)/TestIfFlowControl.cpp$(ObjectSuffix): TestIfFlowControl.cpp $(IntermediateDirectory)/TestIfFlowControl.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/waserp/Projects/MiniInterpreter/mipTest/TestIfFlowControl.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestIfFlowControl.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestIfFlowControl.cpp$(DependSuffix): TestIfFlowControl.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestIfFlowControl.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestIfFlowControl.cpp$(DependSuffix) -MM TestIfFlowControl.cpp

$(IntermediateDirectory)/TestIfFlowControl.cpp$(PreprocessSuffix): TestIfFlowControl.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestIfFlowControl.cpp$(PreprocessSuffix) TestIfFlowControl.cpp

$(IntermediateDirectory)/TestFloatArrays.cpp$(ObjectSuffix): TestFloatArrays.cpp $(IntermediateDirectory)/TestFloatArrays.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/waserp/Projects/MiniInterpreter/mipTest/TestFloatArrays.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestFloatArrays.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestFloatArrays.cpp$(DependSuffix): TestFloatArrays.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestFloatArrays.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestFloatArrays.cpp$(DependSuffix) -MM TestFloatArrays.cpp

$(IntermediateDirectory)/TestFloatArrays.cpp$(PreprocessSuffix): TestFloatArrays.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestFloatArrays.cpp$(PreprocessSuffix) TestFloatArrays.cpp

$(IntermediateDirectory)/TestStrings.cpp$(ObjectSuffix): TestStrings.cpp $(IntermediateDirectory)/TestStrings.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/waserp/Projects/MiniInterpreter/mipTest/TestStrings.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestStrings.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestStrings.cpp$(DependSuffix): TestStrings.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestStrings.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestStrings.cpp$(DependSuffix) -MM TestStrings.cpp

$(IntermediateDirectory)/TestStrings.cpp$(PreprocessSuffix): TestStrings.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestStrings.cpp$(PreprocessSuffix) TestStrings.cpp

$(IntermediateDirectory)/TestRegisterCustomBuildInFun.cpp$(ObjectSuffix): TestRegisterCustomBuildInFun.cpp $(IntermediateDirectory)/TestRegisterCustomBuildInFun.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/waserp/Projects/MiniInterpreter/mipTest/TestRegisterCustomBuildInFun.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestRegisterCustomBuildInFun.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestRegisterCustomBuildInFun.cpp$(DependSuffix): TestRegisterCustomBuildInFun.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestRegisterCustomBuildInFun.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestRegisterCustomBuildInFun.cpp$(DependSuffix) -MM TestRegisterCustomBuildInFun.cpp

$(IntermediateDirectory)/TestRegisterCustomBuildInFun.cpp$(PreprocessSuffix): TestRegisterCustomBuildInFun.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestRegisterCustomBuildInFun.cpp$(PreprocessSuffix) TestRegisterCustomBuildInFun.cpp

$(IntermediateDirectory)/TestPreloadVariable.cpp$(ObjectSuffix): TestPreloadVariable.cpp $(IntermediateDirectory)/TestPreloadVariable.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/waserp/Projects/MiniInterpreter/mipTest/TestPreloadVariable.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestPreloadVariable.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestPreloadVariable.cpp$(DependSuffix): TestPreloadVariable.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestPreloadVariable.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestPreloadVariable.cpp$(DependSuffix) -MM TestPreloadVariable.cpp

$(IntermediateDirectory)/TestPreloadVariable.cpp$(PreprocessSuffix): TestPreloadVariable.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestPreloadVariable.cpp$(PreprocessSuffix) TestPreloadVariable.cpp

$(IntermediateDirectory)/TestDebugCallBack.cpp$(ObjectSuffix): TestDebugCallBack.cpp $(IntermediateDirectory)/TestDebugCallBack.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/waserp/Projects/MiniInterpreter/mipTest/TestDebugCallBack.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestDebugCallBack.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestDebugCallBack.cpp$(DependSuffix): TestDebugCallBack.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestDebugCallBack.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestDebugCallBack.cpp$(DependSuffix) -MM TestDebugCallBack.cpp

$(IntermediateDirectory)/TestDebugCallBack.cpp$(PreprocessSuffix): TestDebugCallBack.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestDebugCallBack.cpp$(PreprocessSuffix) TestDebugCallBack.cpp

$(IntermediateDirectory)/TestMathFunctions.cpp$(ObjectSuffix): TestMathFunctions.cpp $(IntermediateDirectory)/TestMathFunctions.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/waserp/Projects/MiniInterpreter/mipTest/TestMathFunctions.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestMathFunctions.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestMathFunctions.cpp$(DependSuffix): TestMathFunctions.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestMathFunctions.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestMathFunctions.cpp$(DependSuffix) -MM TestMathFunctions.cpp

$(IntermediateDirectory)/TestMathFunctions.cpp$(PreprocessSuffix): TestMathFunctions.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestMathFunctions.cpp$(PreprocessSuffix) TestMathFunctions.cpp

$(IntermediateDirectory)/TestLocalVariablescpp.cpp$(ObjectSuffix): TestLocalVariablescpp.cpp $(IntermediateDirectory)/TestLocalVariablescpp.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/waserp/Projects/MiniInterpreter/mipTest/TestLocalVariablescpp.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestLocalVariablescpp.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestLocalVariablescpp.cpp$(DependSuffix): TestLocalVariablescpp.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestLocalVariablescpp.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestLocalVariablescpp.cpp$(DependSuffix) -MM TestLocalVariablescpp.cpp

$(IntermediateDirectory)/TestLocalVariablescpp.cpp$(PreprocessSuffix): TestLocalVariablescpp.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestLocalVariablescpp.cpp$(PreprocessSuffix) TestLocalVariablescpp.cpp

$(IntermediateDirectory)/TestFunctionCallFromCode.cpp$(ObjectSuffix): TestFunctionCallFromCode.cpp $(IntermediateDirectory)/TestFunctionCallFromCode.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/waserp/Projects/MiniInterpreter/mipTest/TestFunctionCallFromCode.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestFunctionCallFromCode.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestFunctionCallFromCode.cpp$(DependSuffix): TestFunctionCallFromCode.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestFunctionCallFromCode.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestFunctionCallFromCode.cpp$(DependSuffix) -MM TestFunctionCallFromCode.cpp

$(IntermediateDirectory)/TestFunctionCallFromCode.cpp$(PreprocessSuffix): TestFunctionCallFromCode.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestFunctionCallFromCode.cpp$(PreprocessSuffix) TestFunctionCallFromCode.cpp

$(IntermediateDirectory)/TestMultilevelFun.cpp$(ObjectSuffix): TestMultilevelFun.cpp $(IntermediateDirectory)/TestMultilevelFun.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/waserp/Projects/MiniInterpreter/mipTest/TestMultilevelFun.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestMultilevelFun.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestMultilevelFun.cpp$(DependSuffix): TestMultilevelFun.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestMultilevelFun.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestMultilevelFun.cpp$(DependSuffix) -MM TestMultilevelFun.cpp

$(IntermediateDirectory)/TestMultilevelFun.cpp$(PreprocessSuffix): TestMultilevelFun.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestMultilevelFun.cpp$(PreprocessSuffix) TestMultilevelFun.cpp

$(IntermediateDirectory)/TestSyntaxErrors.cpp$(ObjectSuffix): TestSyntaxErrors.cpp $(IntermediateDirectory)/TestSyntaxErrors.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/waserp/Projects/MiniInterpreter/mipTest/TestSyntaxErrors.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestSyntaxErrors.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestSyntaxErrors.cpp$(DependSuffix): TestSyntaxErrors.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestSyntaxErrors.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestSyntaxErrors.cpp$(DependSuffix) -MM TestSyntaxErrors.cpp

$(IntermediateDirectory)/TestSyntaxErrors.cpp$(PreprocessSuffix): TestSyntaxErrors.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestSyntaxErrors.cpp$(PreprocessSuffix) TestSyntaxErrors.cpp

$(IntermediateDirectory)/TestMultilevelFunError.cpp$(ObjectSuffix): TestMultilevelFunError.cpp $(IntermediateDirectory)/TestMultilevelFunError.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/waserp/Projects/MiniInterpreter/mipTest/TestMultilevelFunError.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestMultilevelFunError.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/TestMultilevelFunError.cpp$(DependSuffix): TestMultilevelFunError.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/TestMultilevelFunError.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/TestMultilevelFunError.cpp$(DependSuffix) -MM TestMultilevelFunError.cpp

$(IntermediateDirectory)/TestMultilevelFunError.cpp$(PreprocessSuffix): TestMultilevelFunError.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/TestMultilevelFunError.cpp$(PreprocessSuffix) TestMultilevelFunError.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


