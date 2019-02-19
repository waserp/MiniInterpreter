
#include "include/MiniInterpreterEnums.h"

const char * EtokenTypeToString(ETokenType p_token)
{

  switch (p_token) {
    case eTT_SN_LISTEND : return "ListEnd"; break;
    case eTT_KW_float : return "float"; break;
    case eTT_KW_StringDesignator : return "StringDesignator"; break;
    case eTT_SN_Plus : return "+"; break;
    case eTT_SN_Minus : return "-"; break;
    case eTT_SN_Equal : return "="; break;
    case eTT_SN_Mul : return "*"; break;
    case eTT_SN_Div : return "/"; break;
    case eTT_SN_Semicolon : return ";"; break;
    case eTT_KW_Comma : return ","; break;
    case eTT_SN_LessThan : return "<"; break;
    case eTT_SN_GreaterThan : return ">"; break;
    case eTT_SN_EqualCompare : return "=="; break;
    case eTT_SN_NotEqualCompare : return "!="; break;
    case eTT_SN_Zero : return "Zero"; break;
    case eTT_KW_RoundParOpen : return ")"; break;
    case eTT_KW_RoundParClose : return "("; break;
    case eTT_KW_BraceOpen : return "{"; break;
    case eTT_KW_BraceClose : return "}"; break;
    case eTT_ST_NumericValue : return "Numeric Value"; break;
    case eTT_ST_Variable : return "Variable"; break;
    case eTT_KW_Function : return "KW Function"; break;
    case eTT_SN_FunctionName : return "Function Name"; break;
    case eTT_NM_Function : return "Function"; break;
    case eTT_NM_BuiltIn : return "Build In"; break;
    case eTT_KW_DontCare : return "DontCare"; break;
    case eTT_NM_UnknownIdentifier : return "Unknown Identifier"; break;
    case eTT_KW_DoubleQuotes : return "\""; break;
    case eTT_SN_StringConstant : return "StringConstant"; break;
    case eTT_KW_While  : return "KW While"; break;
    case eTT_KW_If : return "KW if"; break;
    case eTT_KW_Else : return "KW else"; break;
    case eTT_SN_OpeningBracket : return "["; break;
    case eTT_SN_ClosingBracket : return "]"; break;
    case eTT_SN_ArrayIdentifier : return "Array Id"; break;
    default :
    return "unknown Token";
  }
}
