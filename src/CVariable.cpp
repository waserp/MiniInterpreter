#include "include/CVariable.h"


std::string& CVariable::GetString()
{
  if (m_VarType==eVT_float) {
    return m_val = std::to_string(m_valnum);
  }
  return m_val;
}
