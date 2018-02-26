


#ifndef CMINIINTERPRETER_H_
#define CMINIINTERPRETER_H_


#include <string>
#include <vector>
#include <cmath>

class CVariable {
  public:
    enum eVarType {
      eVT_float,
      eVT_string  
    };
    std::string m_name;
    std::string m_val;
    float m_valnum {0};
};

enum ETokenType {
  eTT_SN_LISTEND = 0,
  eTT_KW_float,
  eTT_SN_Plus,
  eTT_SN_Minus,
  eTT_SN_Equal,
  eTT_SN_Mul,
  eTT_SN_Div,
  eTT_SN_Semicolon,
  eTT_SN_Zero,
  eTT_KW_RoundParOpen,
  eTT_KW_RoundParClose,
  eTT_ST_NumericValue,
  eTT_ST_Variable
};


class CMiniInterpreter {
  public:
    void InterpretCode(const char * p_code);
    
    float EvaluateNumExpression(const char * p_expression);
    
private:

  void CreateVariable();
  void GetNewName(std::string& p_name);
  float EvaluateNumExpression(ETokenType p_Endtoken);
  bool TryReadNumber();
  ETokenType GetToken(const char type = 'l');
  bool keyComp(const char * p_keyword);
  std::vector<CVariable*> m_VarSpace;
  const char * m_CurPos {nullptr};
  const char * m_tokenName {nullptr};
  float m_tokenValue { nanf("0") };
  CVariable* m_lValueVar {nullptr};
};


#endif

