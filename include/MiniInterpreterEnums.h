#ifndef MINIINTERPRETERENUMS_H_INCLUDED
#define MINIINTERPRETERENUMS_H_INCLUDED

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

const char * EtokenTypeToString(ETokenType p_token);
#endif // MINIINTERPRETERENUMS_H_INCLUDED
