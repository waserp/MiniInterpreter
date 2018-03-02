#ifndef CVARIABLE_H
#define CVARIABLE_H


#include <string>
#include <vector>


class CVariable {

  public:
    enum eVarType {
      eVT_undef,
      eVT_float,
      eVT_floatArray,
      eVT_string
    };
    CVariable(eVarType p_VarType, bool p_StackVarFlag = false) :m_VarType(p_VarType),m_stackVarFlag(p_StackVarFlag){}

    bool GetStackVarFlag() {return m_stackVarFlag;}

  // todo GetString(); GetFloat(); GetArray();
    std::string& GetString();
    float GetFloatValue() {return m_valnum;}
    void SetType(eVarType p_VarType) { m_VarType = p_VarType; }
    void SetFloatValue(float p_val) { m_valnum = p_val; }
    void SetStringValue(std::string& p_str) {m_val = p_str; }

    eVarType           m_VarType {eVT_undef};
    std::string        m_name;
    std::string        m_val;
    float              m_valnum {0};
    std::vector<float> m_arrayValues;
    bool               m_stackVarFlag {false};
};
#endif // CVARIABLE_H
