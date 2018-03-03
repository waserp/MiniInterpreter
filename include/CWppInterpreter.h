


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
  eTT_SN_Plus,
  eTT_SN_Minus,
  eTT_SN_Equal,
  eTT_SN_Mul,
  eTT_SN_Div,
  eTT_SN_Semicolon,
  eTT_SN_LessThan,
  eTT_SN_GreaterThan,
  eTT_SN_EqualCompare,
  eTT_SN_NotEqualCompare,
  eTT_SN_Zero,
  eTT_KW_RoundParOpen,
  eTT_KW_RoundParClose,
  eTT_KW_BraceOpen,
  eTT_KW_BraceClose,
  eTT_ST_NumericValue,
  eTT_ST_Variable,
  eTT_KW_Function,
  eTT_NM_Function,
  eTT_NM_BuiltIn,
  eTT_KW_DontCare,
  eTT_KW_Comma,
  eTT_NM_UnknownIdentifier,
  eTT_KW_DoubleQuotes,
  eTT_SN_StringConstant,
  eTT_KW_While
};


class CMiniInterpreter {
  public:
    CMiniInterpreter();
    ~CMiniInterpreter();
    typedef std::function<float(std::vector<CVariable*>&)> BuiltInfunction_t;

    void InterpretCode(const char * p_code, ETokenType p_Endtoken = eTT_SN_Zero);

    float EvaluateNumExpression(const char * p_expression);
    void PreloadVariable(const char * p_varname, float p_val) { CVariable* pv = new CVariable(CVariable::eVT_float); pv->m_name = p_varname; pv->m_valnum = p_val;m_VarSpace.push_back(pv);  }
    float GetFloatValue(const char * p_varname) { for(auto&var:m_VarSpace){ if(0==var->m_name.compare(p_varname)) {return var->m_valnum;} } return nanf("");}

    void InsertFunPointer(std::string p_funname, const char * p_pointInCode) {
        if (m_FunSpace.end() != m_FunSpace.find(p_funname)) { throw std::runtime_error(("duplicate function name [" + p_funname + "]").c_str()); };
        m_FunSpace[p_funname] = m_CurPos;    }


private:
  bool TryReadName(std::string& name);
  bool TryReadStringConstant();
  void ParChecker(const uint32_t p_count, const char * p_name,std::vector<CVariable*>& parVec);
  void PushBuiltIns();
  float ExecuteBuiltIn();
  void ExecuteWhile();
  void SkipPair(ETokenType p_Starttoken,ETokenType p_Endtoken, bool p_first = true);
  void FindNext(const char * ch) {while (*m_CurPos!=0){ if (*m_CurPos==*ch) {m_CurPos++; return;} }throw std::runtime_error((" unexpected end of file while looking for [" + std::string(ch) + "]").c_str());}

  uint32_t GetCurrentLine();
  void CreateVariable(CVariable::eVarType p_VarType);
  void PreParseFunction();
  void GetNewName(std::string& p_name);
  float EvaluateNumExpression(ETokenType p_Endtoken);
  bool TryReadNumber();
  ETokenType GetToken(const char type = 'l');
  bool keyComp(const char * p_keyword);


  std::vector<CVariable*>   m_VarSpace;
  std::map<std::string,const char *>   m_FunSpace;  // function name to point in code after function name i.e. "function foo(float a, float b)" the const char* points to '('.
  std::map<std::string,BuiltInfunction_t> m_BuiltInFunMap;

  const char *              m_CurPos {nullptr};
  const char *              m_StartPos {nullptr};
  const char *              m_tokenName {nullptr};
  std::string               m_Unknownidentifier;
  std::string               m_StringConstant;
  BuiltInfunction_t         m_LastBuiltInFunction {nullptr};
  float                     m_tokenValue { nanf("0") };
  CVariable*                m_lValueVar {nullptr};
};


#endif

