


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
    CMiniInterpreter();
    ~CMiniInterpreter();

    typedef std::function<float(std::vector<CVariable*>&)> BuiltInfunction_t;

    void RegisterCustomBuiltIn(std::string p_name, BuiltInfunction_t p_fun)    {      m_BuiltInFunMap[p_name] = p_fun;    }

    void InterpretCode(const char * p_code, ETokenType p_Endtoken = eTT_SN_Zero);

    float EvaluateNumExpression(const char * p_expression);

    /// Deletes all variables, and function pointers, BUT not the built in Functions
    void Clean();

    /// Create or if it already exists update the value of a variable
    /// @param[in] p_varname name of the variable to create
    /// @param[in] p_val float value
    bool PreloadVariable(const char * p_varname, float p_val);

    /// Create or if it already exists update the value of a variable
    /// @param[in] p_varname name of the variable to create
    /// @param[in] p_val string value
    bool PreloadVariable(const char * p_varname, std::string p_val);

    /// Read the Value of a float Variable from the varspace
    /// @param[in] p_varname name of the variable
    float GetFloatValue(const char * p_varname);
    std::string GetStringValue(const char * p_varname) { for(auto&var:m_VarSpace){ if(0==var->m_name.compare(p_varname)) {return var->GetString();} } return std::string("string not found");}
    void InsertFunPointer(std::string p_funname, functionDescriptor_t* fundes) {
        if (m_FunSpace.end() != m_FunSpace.find(p_funname)) { throw std::runtime_error(("duplicate function name [" + p_funname + "]").c_str()); };
          m_FunSpace[p_funname] = fundes;
        }


private:
  bool TryReadName(std::string& name);
  bool TryReadStringConstant();
  void ParChecker(const uint32_t p_count, const char * p_name,std::vector<CVariable*>& parVec);
  void PushBuiltIns();
  float ExecuteBuiltIn();
  void ExecuteWhile();
  void ExecuteIf();
  void ExecuteFunction();
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
  void ReadArrayIndex(CVariable* p_var, char p_mode = 'R');
  ETokenType GetToken(const char type = 'l');
  bool keyComp(const char * p_keyword);
  CVariable* FindExistingVariable(const char * p_name);


  std::vector<CVariable*>   m_VarSpace;
  std::map<std::string,functionDescriptor_t*>  m_FunSpace;  // function name to point in code after function name i.e. "function foo(float a, float b)" the const char* points to '('.
  std::map<std::string,BuiltInfunction_t>      m_BuiltInFunMap;

  const char *              m_CurPos {nullptr};
  const char *              m_StartPos {nullptr};
  const char *              m_tokenName {nullptr};
  std::string               m_Unknownidentifier;
  std::string               m_StringConstant;
  BuiltInfunction_t         m_LastBuiltInFunction {nullptr};
  functionDescriptor_t*     m_LastFunctionDescriptor {nullptr};
  float                     m_tokenValue { nanf("0") };
  CVariable*                m_lValueVar {nullptr};
  std::map<std::string,CVariable*>*
                            m_ParameterVariableMap {nullptr};
};


#endif

