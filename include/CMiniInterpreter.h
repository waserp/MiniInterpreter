


#ifndef CMINIINTERPRETER_H_
#define CMINIINTERPRETER_H_


#include <string>
#include <vector>
#include <cmath>
#include <map>
#include <stdexcept>
#include <functional>

#include "CVariable.h"

enum ETokenType {
  eTT_SN_LISTEND = 0,
  eTT_KW_float,
  eTT_KW_StringDesignator,
  eTT_SN_Plus,
  eTT_SN_Minus,
  eTT_SN_Equal,
  eTT_SN_Mul,
  eTT_SN_Div,
  eTT_SN_Semicolon,
  eTT_KW_Comma,
  eTT_SN_LessThan = 20,
  eTT_SN_GreaterThan,
  eTT_SN_EqualCompare,
  eTT_SN_NotEqualCompare,
  eTT_SN_Zero,
  eTT_KW_RoundParOpen = 30,
  eTT_KW_RoundParClose,
  eTT_KW_BraceOpen,
  eTT_KW_BraceClose,
  eTT_ST_NumericValue,
  eTT_ST_Variable = 40,
  eTT_KW_Function,
  eTT_SN_FunctionName,
  eTT_NM_Function,
  eTT_NM_BuiltIn,
  eTT_KW_DontCare,

  eTT_NM_UnknownIdentifier,
  eTT_KW_DoubleQuotes,
  eTT_SN_StringConstant,
  eTT_KW_While  = 60,
  eTT_KW_If,
  eTT_KW_Else,
  eTT_SN_OpeningBracket,
  eTT_SN_ClosingBracket,
  eTT_SN_ArrayIdentifier
};

struct functionDescriptor_t {
  const char *                                        StartOfFuncode {nullptr};
  std::vector<std::pair<std::string,ETokenType>>      LocalVarNames;
};



class CMiniInterpreter {
  public:

    /// Built in Function definition
    typedef std::function<float(std::vector<CVariable*>&)> BuiltInfunction_t;

    /// Call Back Function
    typedef std::function<bool(uint32_t, std::map<std::string, CVariable*>&)>  CallBack_t;

    /// Constructor, registers the built in functions
    CMiniInterpreter();

    /// Destructor, deletes all allocated memory
    ~CMiniInterpreter();

    /// Executes Code
    /// @param[in] p_code code to execute
    void InterpretCode(const char * p_code);

    /// Execute the function with the given name. The function must have been in the previously
    /// with InterpretCode parsed code.
    /// @code
    /// interp.InterpretCode(" // other code \n function foo(){ print(\"hello from foo\"); }   // other code \n ");
    /// interp.ExecuteFunction("foo");
    /// @endcode
    /// @param[in] p_name
    /// @return true if the function was executed. false if it was not found
    bool ExecuteFunction(const char* p_name);

    /// Evaluate the numeric expression i.e. EvaluateNumExpression(" 1 + 3 * 2"); returns 7
    /// @param[in] p_expression the expression to be evaluated
    /// @return the value
    float EvaluateNumExpression(const char * p_expression);

    /// Deletes all variables, and function pointers, BUT not the built in Functions
    void Clean();

    /// Register built in functions into map
    /// @param[in] p_name function name
    /// @param[in] p_fun function pointer
    void RegisterCustomBuiltIn(std::string p_name, BuiltInfunction_t p_fun)    {      m_BuiltInFunMap[p_name] = p_fun;    }

    /// Create or if it already exists update the value of a variable
    /// @param[in] p_varname name of the variable to create
    /// @param[in] p_val float value
    bool PreloadVariable(const char * p_varname, float p_val);

    /// Create or if it already exists update the value of a variable
    /// @param[in] p_varname name of the variable to create
    /// @param[in] p_val string value
    bool PreloadVariable(const char * p_varname, std::string p_val);

    /// deletes a variable from the variable map
    /// @param[in] p_varname name of the variable to delete
    /// @return true if the variable was found and deleted else false is returned
    bool DeleteVariable(const char * p_varname);

    /// Read the Value of a float Variable from the varspace
    /// @param[in] p_varname name of the variable
    /// @return the value
    float GetFloatValue(const char * p_varname);

    /// Read the Value of a string Variable from the varspace
    /// @param[in] p_varname name of the variable
    /// @return the value
    std::string GetStringValue(const char * p_varname);

    /// Insert a function pointer into the map
    /// a function is an in-script defined function
    void InsertFunPointer(std::string p_funname, functionDescriptor_t* fundes);

    /// Register a Callback function which is called after each statement
    /// Allows single step or abort
    void RegisterStatementCallBack(CallBack_t p_CallBack) { m_CallBack = p_CallBack; }

private:
  /// Executes Code
  /// @param[in] p_code code to execute
  /// @param[in] p_Endtoken the endtoken
  void InterpretCode(const char * p_code, ETokenType p_Endtoken);

  void ThrowFatalError(const char *format, ...);
  bool TryReadName(std::string& name);
  bool TryReadStringConstant();
  void ParChecker(const uint32_t p_count, const char * p_name,std::vector<CVariable*>& parVec);
  void PushBuiltIns();
  float ExecuteBuiltIn();
  void ExecuteWhile();
  void ExecuteIf();
  void ExecuteFunction();
  void ExecuteFunction(functionDescriptor_t* p_fun);
  ETokenType GetNextOf(ETokenType a, ETokenType b);
  void SkipPair(ETokenType p_Starttoken,ETokenType p_Endtoken, bool p_first = true);
  void FindNext(const char * ch) {while (*m_CurPos!=0){ if (*m_CurPos==*ch) {m_CurPos++; return;} }throw std::runtime_error((" unexpected end of file while looking for [" + std::string(ch) + "]").c_str());}

  uint32_t GetCurrentLine();
  void CreateVariable(CVariable::eVarType p_VarType);
  void PreParseFunction();
  void GetNewName(std::string& p_name);
  float EvaluateNumExpression(ETokenType p_Endtoken);
  std::string EvaluateStringExpression(ETokenType p_Endtoken);
  bool TryReadNumber();
  uint32_t ReadArrayIndex(CVariable* p_var, char p_mode = 'R');

  ETokenType RemoveWhitespace();  // also remove comment
  ETokenType GetToken(const char type = 'l');
  bool keyComp(const char * p_keyword);
  CVariable* FindExistingVariable(const char * p_name);


  std::map<std::string,CVariable*>             m_VarMap;
  std::map<std::string,functionDescriptor_t*>  m_FunSpace;  // function name to point in code after function name i.e. "function foo(float a, float b)" the const char* points to '('.
  std::map<std::string,BuiltInfunction_t>      m_BuiltInFunMap;

  CallBack_t                m_CallBack {nullptr};
  bool                      m_Abort {false};
  // parser state variables
  int32_t                   m_RecursionLevel { -1 };
  const char *              m_StartPosAtReclevel0 {nullptr};
  const char *              m_CurPos {nullptr};
  const char *              m_StartPos {nullptr};
  const char *              m_tokenName {nullptr};
  const char *              m_StartOfCode {nullptr};
  std::string               m_Unknownidentifier;
  std::string               m_StringConstant;
  BuiltInfunction_t         m_LastBuiltInFunction {nullptr};
  functionDescriptor_t*     m_LastFunctionDescriptor {nullptr};
  float                     m_tokenValue { nanf("0") };
  CVariable*                m_lValueVar {nullptr};
  std::map<std::string,CVariable*>*
                            m_ParameterVariableMap {nullptr};

  /// if this pointer is not null, then every newly created variable name goes into this list.
  /// Except preload variables. On Exit of the function all variables on this list are deleted.
  std::vector<std::string>* m_pListofLocalVariables {nullptr};
};


#endif

