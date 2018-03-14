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
      eVT_string,
      eVT_stringArray
    };
    CVariable(eVarType p_VarType, bool p_StackVarFlag = false) :m_VarType(p_VarType),m_stackVarFlag(p_StackVarFlag){}

    bool GetStackVarFlag() {return m_stackVarFlag;}

    bool Is_Array() { return (m_VarType == eVT_floatArray); }
    eVarType GetType() { return m_VarType; }
    const char * GetTypeAsString();


    std::string& GetString();
    float GetFloatValue();
    float GetFloatValue(uint32_t p_index);
    void SetType(eVarType p_VarType) { m_VarType = p_VarType; }


    void SetArrayIndex(uint32_t p_index) { m_index = p_index; }
    void SetArrayWriteIndex(uint32_t p_index) { m_WriteIndex = p_index; }
    void SetFloatValue(float p_val);
    void SetFloatValue(float p_val, uint32_t p_index) {  m_WriteIndex = p_index;SetFloatValue(p_val); }

    void SetStringValue(std::string p_str) {m_val = p_str; }


    std::vector<float>& GetRawFloatArray() { return m_FloatArrayValues; }

    /// set variable name
    /// @param[in] p_name
    void SetName(std::string p_name) { m_name = p_name;}

    /// get name
    /// @return variable name
    std::string& GetName() { return m_name; }

    /// @return the write index
    uint32_t GetLIndex() { return m_WriteIndex; }


  private:
    eVarType           m_VarType {eVT_undef};
    std::string        m_name;
    std::string        m_val;
    std::vector<float> m_FloatArrayValues;
    uint32_t           m_index {0};
    uint32_t           m_WriteIndex {0};
    bool               m_stackVarFlag {false};
    float              m_valnum {0};
};
#endif // CVARIABLE_H
