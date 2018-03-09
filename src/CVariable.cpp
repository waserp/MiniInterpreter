#include "include/CVariable.h"
#include <iostream>





std::string& CVariable::GetString()
{
  if (m_VarType==eVT_float) {
    return m_val = std::to_string(m_valnum);
  }
  if (m_VarType==eVT_floatArray) {
    //std::cout << "float Array print" << m_WriteIndex << "\n";
    if (m_WriteIndex >  m_FloatArrayValues.size()) {
      m_val = "[";
      for (auto& v : m_FloatArrayValues){  m_val+=std::to_string(v); if (&v!=&m_FloatArrayValues.back()) {m_val+=",";} }
      m_val+="]";
      return m_val;
    }
    m_val = std::to_string(m_FloatArrayValues[m_index]);
  }
  return m_val;
}

float CVariable::GetFloatValue()
{
  if (m_VarType == eVT_string) {
    m_valnum = atof(m_val.c_str());
  }
  if (m_VarType != eVT_floatArray) { return m_valnum;}
  return m_FloatArrayValues[m_index];
}

void CVariable::SetFloatValue(float p_val)
{
  //std::cout << "CVariable::SetFloatValue " << m_name << " val " << p_val << " ix " << m_WriteIndex << "\n\n";
  if (m_VarType != eVT_floatArray) {  m_valnum = p_val; return;}
  if (m_FloatArrayValues.size() <= m_WriteIndex) {
    m_FloatArrayValues.resize(m_WriteIndex + 1);
  }
  m_FloatArrayValues[m_WriteIndex] = p_val;
}

const char * CVariable::GetTypeAsString()
{
  static const char * t[]={"undef","float","float[]","string","string[]","illegal type value"};
  return t[std::min(static_cast<size_t>(m_VarType),sizeof(t)/sizeof(const char *))];
}
