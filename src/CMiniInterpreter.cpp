





#include "include/CMiniInterpreter.h"
#include "include/CColors.h"
#include "MathFun.h"

#include <cstdio>
#include <cstdint>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <stdarg.h>

//#define Debug


struct KeyWordList_t {
    ETokenType   token;
    const char * name;
};

KeyWordList_t KeyWords[] = {
  {eTT_KW_float,"float"},
  {eTT_KW_StringDesignator,"string"},
  {eTT_SN_Plus,"+"},
  {eTT_SN_Minus,"-"},
  {eTT_SN_NotEqualCompare,"!="},
  {eTT_SN_EqualCompare,"=="},  // this must be before the '=' entry otherwise bad things happen !!!
  {eTT_SN_Equal,"="},
  {eTT_SN_Mul,"*"},
  {eTT_SN_Div,"/"},
  {eTT_SN_Semicolon,";"},
  {eTT_KW_Comma,","},
  {eTT_SN_LessThan,"<"},
  {eTT_SN_GreaterThan,">"},
  {eTT_SN_Zero, "ThisIsTheEndMyFriend" },
  {eTT_KW_RoundParOpen,"("},
  {eTT_KW_RoundParClose,")"},
  {eTT_KW_BraceOpen,"{"},
  {eTT_KW_BraceClose,"}"},
  {eTT_KW_Function,"function"},
  {eTT_KW_While,"while"},
  {eTT_KW_If,"if"},
  {eTT_KW_Else,"else"},
  {eTT_KW_DoubleQuotes,"\""},
  {eTT_SN_ArrayIdentifier,"[]"},
  {eTT_SN_OpeningBracket,"["},
  {eTT_SN_ClosingBracket,"]"},
  {eTT_SN_LISTEND,""} // mark the end of the list, let this allways at bottom
};

const char * helperTo2Str(ETokenType to){KeyWordList_t* kp= &KeyWords[0]; while (kp->token!= eTT_SN_LISTEND) { if (kp->token == to) return kp->name; kp++;} return "unknown :( !"; }


void CMiniInterpreter::ThrowFatalError(const char *format, ...)
{
  va_list arglist;
  char msg[512];
  int32_t pcnt = snprintf(msg,50,"Script-Error Line %04d:",GetCurrentLine());
  //std::cout << pcnt << " " << msg << std::endl;
  if ((pcnt < 0) || ( pcnt > 100)){
    pcnt = 0;
  }
  va_start(arglist, format);
  vsnprintf(&msg[pcnt], sizeof(msg) -pcnt, format, arglist);
  throw std::runtime_error(msg);
}



CMiniInterpreter::CMiniInterpreter()
{
  PushBuiltIns();
}

CMiniInterpreter::~CMiniInterpreter()
{
  Clean();
}

void ParChecker(const uint32_t p_count, const char * p_name, std::vector<CVariable*>& parVec)
{
  if (parVec.size() != p_count) { throw std::runtime_error(("Error, wrong number of parameters, expected [" + std::to_string(p_count) + "] detected [" + std::to_string(parVec.size()) + "]").c_str()); }
}

void CMiniInterpreter::PushBuiltIns()
{
  m_BuiltInFunMap["print"] = [](std::vector<CVariable*>& parVec){ std::cout << Colors::yellow; for (auto pPar : parVec) { std::cout << pPar->GetString(); }  std::cout << Colors::white << "\n"; return 0.0F;};
  m_BuiltInFunMap["sin"] = [](std::vector<CVariable*>& parVec){ return sin(parVec[0]->GetFloatValue());};
  m_BuiltInFunMap["cos"] = [](std::vector<CVariable*>& parVec){ return cos(parVec[0]->GetFloatValue());};
  m_BuiltInFunMap["log"] = [](std::vector<CVariable*>& parVec){ return logf(parVec[0]->GetFloatValue());};
  m_BuiltInFunMap["log10"] = [](std::vector<CVariable*>& parVec){ return log10f(parVec[0]->GetFloatValue());};
  m_BuiltInFunMap["sqrt"] = [](std::vector<CVariable*>& parVec){ return sqrtf(parVec[0]->GetFloatValue());};
  m_BuiltInFunMap["mean"] = [](std::vector<CVariable*>& parVec){
     return mean(parVec);
  };
  m_BuiltInFunMap["stddev"] = [](std::vector<CVariable*>& parVec){
     return stddev(parVec);
  };
  m_BuiltInFunMap["min"] = [](std::vector<CVariable*>& parVec){
     return minfun(parVec);
  };
  m_BuiltInFunMap["max"] = [](std::vector<CVariable*>& parVec){
     return maxfun(parVec);
  };
  //m_BuiltInFunMap["max"] = [](std::vector<CVariable*>& parVec){ float val; for (auto pPar : parVec) {  }  return 0.0F;};
}


/*    #    ##    #####      #      ##    #####   #       ######   ####
 #    #   #  #   #    #     #     #  #   #    #  #       #       #
 #    #  #    #  #    #     #    #    #  #####   #       #####    ####
 #    #  ######  #####      #    ######  #    #  #       #            #
  #  #   #    #  #   #      #    #    #  #    #  #       #       #    #
   ##    #    #  #    #     #    #    #  #####   ######  ######   ####*/


void CMiniInterpreter::CreateVariable(CVariable::eVarType p_VarType)
{
  CVariable* pVar = new CVariable(p_VarType);
  ETokenType totype = GetToken();
  if ( totype == eTT_SN_ArrayIdentifier) {
    if (p_VarType == CVariable::eVT_float) {
      pVar->SetType(CVariable::eVT_floatArray);
    } else {
      pVar->SetType(CVariable::eVT_stringArray);
    }
    totype = GetToken();
  }
  if ( totype != eTT_NM_UnknownIdentifier) {  ThrowFatalError("Expected a new variable name, redeclaration or reserved word "); }
  pVar->SetName(m_Unknownidentifier);
  #ifdef Debug
  std::cout << Colors::Iblue << "Variable with name :[" << pVar->m_name.c_str() << "] created of type [" << pVar->GetTypeAsString() << "]" << Colors::white << std::endl;
  #endif // Debug
  m_VarMap[m_Unknownidentifier] = pVar;
  if (m_pListofLocalVariables != nullptr) {
    m_pListofLocalVariables->push_back(m_Unknownidentifier);
  }
  totype = GetToken();
  if (totype == eTT_SN_Semicolon) { return; } // were done, ok
  if (totype == eTT_SN_Equal) {
    switch (pVar->GetType()) {
      case CVariable::eVT_float: pVar->SetFloatValue(EvaluateNumExpression(eTT_SN_Semicolon));
      break;
      case CVariable::eVT_floatArray:
      {
        if ( GetToken() != eTT_SN_OpeningBracket) { ThrowFatalError("Error expected array initializer i.e. [1,2,3] after float[] = statment!"); }
        uint32_t index = 0;
        do {
          totype = GetNextOf(eTT_SN_ClosingBracket,eTT_KW_Comma);
          pVar->SetArrayWriteIndex(index);
          pVar->SetFloatValue(EvaluateNumExpression(totype));
          index++;
        }
        while (totype != eTT_SN_ClosingBracket);
      }
      break;
      case CVariable::eVT_string: pVar->SetStringValue(EvaluateStringExpression(eTT_SN_Semicolon));
      break;
      case CVariable::eVT_stringArray:
      break;
      default :
      break;
    }
    return;
  }
  ThrowFatalError("Error fatal expect Semicolon after Variable definition. Variable Name[%s] totype[%d]",pVar->GetName().c_str(),totype);
}

void CMiniInterpreter::Clean()
{
  m_Abort = false;
  m_RecursionLevel = -1;
  for (auto it :  m_VarMap) {
    delete it.second;
  }
  m_VarMap.clear();
  for (auto fundesc : m_FunSpace) {
    delete fundesc.second;
  }
  m_FunSpace.clear();
}

bool CMiniInterpreter::PreloadVariable(const char * p_varname, float p_val)
{
  CVariable* pv =FindExistingVariable(p_varname);
  if (pv==nullptr) {
    pv = new CVariable(CVariable::eVT_float);
    pv->SetName(p_varname);
    pv->SetFloatValue(p_val);
    m_VarMap[p_varname] = pv;
    return true;
  }
  pv->SetFloatValue(p_val);
  return false;
}

bool CMiniInterpreter::DeleteVariable(const char * p_varname)
{
  auto it = m_VarMap.find(p_varname);
  if (it == m_VarMap.end()) {
    return false;
  }
  m_VarMap.erase(it);
  delete it->second;
  return true;
}

bool CMiniInterpreter::PreloadVariable(const char * p_varname, std::string p_val)
{
  CVariable* pv =FindExistingVariable(p_varname);
  if (pv==nullptr) {
    pv = new CVariable(CVariable::eVT_string);
    pv->SetName(p_varname);
    pv->SetStringValue(p_val);
    m_VarMap[p_varname] = pv;
    return true;
  }
  pv->SetStringValue(p_val);
  return false;
}

float CMiniInterpreter::GetFloatValue(const char * p_varname)
{
 CVariable* pv =FindExistingVariable(p_varname);
 if (pv==nullptr) {
   return nanf("0");
 }
 return pv->GetFloatValue();
}

CVariable* CMiniInterpreter::FindExistingVariable(const char * p_name)
{
  auto it = m_VarMap.find(p_name);
  if (it == m_VarMap.end()) {
    return nullptr;
  }
  return it->second;
}

std::string CMiniInterpreter::GetStringValue(const char * p_varname)
{
  CVariable* pv =FindExistingVariable(p_varname);
  return pv->GetString();
  return std::string("string not found");
}


uint32_t CMiniInterpreter::GetCurrentLine()
{
  uint32_t linecounter = 1;
  const char * sp = m_StartPosAtReclevel0;
  while (sp < m_CurPos) {
    if (*sp == '\n') {linecounter++;}
    sp++;
  }
  return linecounter;
}

bool CMiniInterpreter::keyComp(const char * p_keyword)
{
  const char * pt = m_CurPos;
  const char * kwp = p_keyword;
  while (*kwp != 0) {
    if (*kwp != *pt) { return false; }
    if (*pt == 0) { return false; }
    kwp++;
    pt++;
  }
  m_tokenName = p_keyword;
  if (!isalnum(p_keyword[0])) { m_CurPos = pt; return true; } // keywords like "+" "-" etc can be followed by letters i.e. a=b+c
  if (!isalnum(*pt)) { m_CurPos = pt; return true; }           // keywords like "float" can not be followed by letters i.e. floatFoo is not keyword float
  //printf(" pt = %c isalnum = %i",*pt,isalnum(*pt));
  return false;
}

bool CMiniInterpreter::TryReadNumber()
{
  bool DigitFlag = false;
  const char * pt = m_CurPos;
  if ((*pt == '-') || (*pt == '+')) { // accept these as sign on first pos
    pt++;
  }
  while ( isdigit(*pt) || (*pt == '.') ) {
    if (isdigit(*pt)) { DigitFlag = true; }
    pt++;
  }
  if (isalpha(*pt)) {return false;}  // this covers cases like "453hello", which is not a number
  if (!DigitFlag) {return false;}  // we need at least a single digit, if there is none this is not a number
  m_tokenValue = static_cast<float>(atof(m_CurPos));
  m_CurPos = pt;
  //printf("try read number success [%f] \n",m_tokenValue);
  return true;
}

bool CMiniInterpreter::TryReadName(std::string& p_name)
{
  p_name = "";
  const char * pt = m_CurPos;
  if (!isalpha(*pt)) return false; // name must start with a letter
  while (isalnum(*pt)) {  // letters and digit
    p_name += *pt;
    pt++;
  }
  if (p_name.size() == 0) return false; // name must at least be 1 letter
  m_CurPos = pt;
  return true;
}

bool CMiniInterpreter::TryReadStringConstant()
{
  if (*m_CurPos!='"') return false;
  m_StringConstant = "";
  m_CurPos++;
  while (*m_CurPos!='"') {
    if (*m_CurPos==0) { ThrowFatalError("Reading string constant no terminating '\"' detected");  }
    m_StringConstant += *m_CurPos;
    m_CurPos++;
  }
  m_CurPos++;
  return true;
}

uint32_t CMiniInterpreter::ReadArrayIndex(CVariable* p_var, char p_mode)
{
  if (!p_var->Is_Array()) { return 0; }
  while (isspace(*m_CurPos)) { m_CurPos++; }
  if (*m_CurPos != '[') { ThrowFatalError("Error, expected array index after variable [%s]",p_var->GetName().c_str()); }
  m_CurPos++;
  uint32_t index = -1;
  if (*m_CurPos != ']') {
    index = lrintf(EvaluateNumExpression(eTT_SN_ClosingBracket));
  } else {
    m_CurPos++;
    index = -1;
  }
  if (p_mode == 'L') {
    p_var->SetArrayWriteIndex(index);
  } else {
    p_var->SetArrayIndex(index);
  }
  return index;
}


/*####   ######   #####   #####   ####   #    #  ######  #    #
 #    #  #          #       #    #    #  #   #   #       ##   #
 #       #####      #       #    #    #  ####    #####   # #  #
 #  ###  #          #       #    #    #  #  #    #       #  # #
 #    #  #          #       #    #    #  #   #   #       #   ##
  ####   ######     #       #     ####   #    #  ######  #    # */


ETokenType CMiniInterpreter::RemoveWhitespace()
{
  do {
    while (isspace(*m_CurPos)) {
        m_CurPos++; // remove whitespace
    }
    if (*m_CurPos == 0) return eTT_SN_Zero;
    if ((*m_CurPos == '/') && (*(m_CurPos+1) == '/')) { // dump comment
      while (*m_CurPos != '\n') {
        if (*m_CurPos == 0) return eTT_SN_Zero;
        m_CurPos++;
      }
    }
  } while (isspace(*m_CurPos));
  if (*m_CurPos == 0) return eTT_SN_Zero;
  return eTT_KW_DontCare;
}

ETokenType CMiniInterpreter::GetToken(const char type)
{
    if ( RemoveWhitespace()== eTT_SN_Zero ) { return eTT_SN_Zero; }


    if ((type == 'n') || (type == 'p')) {  // expect a number, so first try read number
      //printf("\n  type = 'n' rm whitespace>%s<\n",m_CurPos);
      if (TryReadNumber()) { return eTT_ST_NumericValue; }
    }
    if (TryReadStringConstant()) { return eTT_SN_StringConstant;}

//    printf("\nrm whitespace>%s<\n",m_CurPos);
    // now search keywords
    KeyWordList_t* pkwl = KeyWords;
    while (pkwl->token != eTT_SN_LISTEND) { //printf(" compare to -->%s\n",pkwl->name);
      if (keyComp(pkwl->name)) {
        //printf("found token -->%s %i\n",pkwl->name,pkwl->token);
        return pkwl->token;
      }
      pkwl++;
    }
    std::string name;
    if (TryReadName(name)) {  // we got some sort of name
      //std::cout << "Redname succ >" << name << "<\n";
      auto itv = m_VarMap.find(name);
      if (itv != m_VarMap.end()) {
        CVariable* var = itv->second;
        //std::cout << " in var map " << var->GetName()  <<  " " << var->GetTypeAsString() << " type " << type << std::endl;
        if (type == 'p') {   // p like parameter in function call
          int32_t index = ReadArrayIndex(var,'L');
          //std::cout << "first time p th"  << index << std::endl;
          if ((!var->Is_Array()) || (index == -1))  { // if the complete array is the param or if the var is not an array
            m_lValueVar = var;
            return eTT_ST_Variable;
          }
          // if the var is an array we extract the value and return it as numerical

          m_tokenValue = var->GetFloatValue(index);
          //std::cout << "first time th"  << m_tokenValue << " ix " << index  << std::endl;
          return eTT_ST_NumericValue;
        } else if (type == 'l') {
          ReadArrayIndex(var,'L');
          m_lValueVar = var;
          //printf("det Lvar %s\n",var->GetName().c_str());
          return eTT_ST_Variable;
        } else {
          ReadArrayIndex(var);
          m_tokenValue = var->GetFloatValue();
          //printf("det var %s\n",var->GetName().c_str());
          return eTT_ST_NumericValue;
        } // directly resolve to num value if we are r
      }
      //std::cout << " TryReadName succcess  found [" << name << "]" << std::endl;
      auto it = m_BuiltInFunMap.find(name);
      if (it != m_BuiltInFunMap.end()) { //std::cout << " Build In found found " << name << std::endl;
        m_LastBuiltInFunction = it->second;
        return eTT_NM_BuiltIn;
      }
      auto itf = m_FunSpace.find(name);
      if (itf != m_FunSpace.end()) {  //std::cout << " function name found " << name << std::endl;
        m_LastFunctionDescriptor = itf->second;
        return eTT_SN_FunctionName;
      }
      m_Unknownidentifier = name;
      return eTT_NM_UnknownIdentifier;
    }

    // check if it is a number
    if (TryReadNumber()) { return eTT_ST_NumericValue; }
    //printf("list end%s\n",m_CurPos);
    //system("read a");
    return eTT_SN_LISTEND;
}

void CMiniInterpreter::GetNewName(std::string& p_name)
{
  while (isspace(*m_CurPos)) { //(*m_CurPos==' ') || (*m_CurPos=='\t') || (*m_CurPos=='\n') || (*m_CurPos=='\r')) {
    m_CurPos++; // remove whitespace
  }
  ETokenType totype = GetToken();
  if ( totype == eTT_NM_UnknownIdentifier) { p_name = m_Unknownidentifier; return; }
  if ( totype != eTT_SN_LISTEND ) {
     ThrowFatalError("Expeced new identifier instead got [%s]",p_name.c_str());
  }

  while (isalnum(*m_CurPos)) {
    p_name += *m_CurPos;
    m_CurPos++;
  }
}


/*#####  #    #    ##    #       #    #    ##     #####  ######          #    #
 #       #    #   #  #   #       #    #   #  #      #    #               ##   #
 #####   #    #  #    #  #       #    #  #    #     #    #####   #####   # #  #
 #       #    #  ######  #       #    #  ######     #    #               #  # #
 #        #  #   #    #  #       #    #  #    #     #    #               #   ##
 ######    ##    #    #  ######   ####   #    #     #    ######          #    #*/



float CMiniInterpreter::EvaluateNumExpression(const char * p_expression)
{
  m_CurPos = p_expression;
  m_StartPos = p_expression;
  #ifdef Debug
  std::cout << "--------------------------------------------\n" << p_expression << "\n";
  #endif // Debug
  return EvaluateNumExpression(eTT_SN_Semicolon);
}


// https://github.com/cparse/cparse
// read this --> https://en.wikipedia.org/wiki/Shunting-yard_algorithm
float CMiniInterpreter::EvaluateNumExpression(ETokenType p_Endtoken)
{
  //std::cout << "enter" << std::endl;
  class oQType {public:oQType(float p_val,ETokenType p_tok):val(p_val),tok(p_tok){}float val;ETokenType tok;};
  std::vector<oQType> outputQueue;
  std::vector<ETokenType> tokenStack;
  int16_t LastPrecedence = -1; // +- have 0, */ have 1, ^ has 2
  char nextTtype = 'n';
  ETokenType totype = GetToken(nextTtype);  // expect number
  while (totype != p_Endtoken) {
    //std::cout << "start of while >" << m_CurPos << "< analyzing" << helperTo2Str(totype) << std::endl;
    if (totype == eTT_KW_RoundParOpen) {
      nextTtype = 'l';
      //std::cout << " -------------> recursion enter\n";
      outputQueue.push_back(oQType(EvaluateNumExpression(eTT_KW_RoundParClose),eTT_ST_NumericValue));
      //std::cout << " -------------> recursion done\n";
    } else if (totype == eTT_ST_NumericValue) {
      nextTtype = 'r';
      outputQueue.push_back(oQType(m_tokenValue,eTT_ST_NumericValue));
    } else if (( totype == eTT_SN_Plus ) || ( totype == eTT_SN_Minus )) {
      nextTtype = 'n';
      if (LastPrecedence < 0) {
        tokenStack.push_back(totype);
      } else {
        outputQueue.push_back(oQType(nanf("0"),tokenStack.back()));
        tokenStack.pop_back();
        tokenStack.push_back(totype);
      }
      LastPrecedence = 0;
    } else if (( totype == eTT_SN_Mul ) || ( totype == eTT_SN_Div )) {
      nextTtype = 'n';
      if (LastPrecedence < 1) {
        tokenStack.push_back(totype);
      } else {
        outputQueue.push_back(oQType(nanf("0"),tokenStack.back()));
        tokenStack.pop_back();
        tokenStack.push_back(totype);
      }
      LastPrecedence = 1;
    } else if (totype == eTT_NM_BuiltIn) {
      nextTtype = 'r';
      outputQueue.push_back(oQType(ExecuteBuiltIn(),eTT_ST_NumericValue));
    } else if ((totype == eTT_SN_LessThan) || (totype == eTT_SN_GreaterThan) || (totype == eTT_SN_EqualCompare) || (totype == eTT_SN_NotEqualCompare) )  {
      nextTtype = 'n';
      if (LastPrecedence < 0) {
        tokenStack.push_back(totype);
      } else {
        outputQueue.push_back(oQType(nanf("0"),tokenStack.back()));
        tokenStack.pop_back();
        tokenStack.push_back(totype);
      }
      LastPrecedence = -1;
    } else {
      ThrowFatalError("unexpected token in EvaluateNumExpression [%d]",totype);
    }


    // dump queues for debug
    //std::cout << "tokenstack: ";
    //for (auto to : tokenStack) {       std::cout << helperTo2Str(to) << ",";    } std::cout << std::endl;
    //std::cout << "outqueue  : ";
    //for (auto oQ : outputQueue) {      if (oQ.tok == eTT_ST_NumericValue) std::cout << oQ.val << " ";       else std::cout << helperTo2Str(oQ.tok);     } std::cout << std::endl;
    //std::cout << "after dump:" << m_CurPos << std::endl;
    //system("read a");

    totype = GetToken(nextTtype);

  }
  // all operators to output q
  while (tokenStack.size() > 0) {
    outputQueue.push_back(oQType(nanf("0"),tokenStack.back()));
    tokenStack.pop_back();
  }

  // dump queues for debug
  //std::cout << "tokenstack:" << std::endl;
  //for (auto to : tokenStack) {       std::cout << helperTo2Str(to) << " ";    } std::cout << std::endl;    std::cout << "outqueue:" << std::endl;
  //for (auto oQ : outputQueue) {      if (oQ.tok == eTT_ST_NumericValue) std::cout << oQ.val << " ";       else std::cout << helperTo2Str(oQ.tok);     } std::cout << std::endl;

  std::vector<float> rpnstack;
  float result = 0.0F;
  // evaluate rpn
  for (oQType oQ : outputQueue) {
    if (oQ.tok == eTT_ST_NumericValue) {
      //std::cout << "push to rpn " << oQ.val << "\n";
      result = oQ.val;
      rpnstack.push_back(oQ.val);
    } else {
      float opa = rpnstack.back();rpnstack.pop_back();
      float opb = rpnstack.back();rpnstack.pop_back();
      switch (oQ.tok){
        case eTT_SN_Plus: result = opa + opb; //std::cout << opb << " + " << opa <<  " = " << result << "\n";
           break;
        case eTT_SN_Minus: result = opb - opa ; //std::cout << opb << " - " << opa <<  " = " << result << "\n";
           break;
        case eTT_SN_Mul: result = opa * opb; //std::cout << opa << " * " << opb <<  " = " << result << "\n";
           break;
        case eTT_SN_Div: result = opb / opa; //std::cout << opb << " / " << opa <<  " = " << result << "\n";
           break;
        case eTT_SN_LessThan: result = (opb < opa); //std::cout << opb << " < " << opa <<  " = " << result << "\n";
           break;
        case eTT_SN_GreaterThan: result = (opb > opa); //std::cout << opa << " < " << opb <<  " = " << result << "\n";
           break;
        case eTT_SN_EqualCompare: result = (opb == opa); //std::cout << opa << " == " << opb <<  " = " << result << "\n";
           break;
        case eTT_SN_NotEqualCompare: result = (opb != opa); //std::cout << opa << " != " << opb <<  " = " << result << "\n";
           break;
        default :
        break;
      }
      rpnstack.push_back(result);
      //std::cout << "result : " << result << "\n";
    }
  }
  return result;
}
std::string CMiniInterpreter::EvaluateStringExpression(ETokenType p_Endtoken)
{
  std::string a;
  ETokenType totype = GetToken();
  while (totype!=p_Endtoken) {
    if (totype == eTT_SN_StringConstant) {
      a += m_StringConstant;
    } else if (totype == eTT_ST_Variable) {
      a += m_lValueVar->GetString();
    }
    totype = GetToken();
  }
  return a;
}

ETokenType CMiniInterpreter::GetNextOf(ETokenType a, ETokenType b)
{
  const char * p = m_CurPos;
  ETokenType to;
  do {
    to = GetToken();
    if (to == eTT_SN_Zero) {
      ThrowFatalError("Error unexpected end of file!");
    }
  } while ((to != a) && (to != b));
  m_CurPos = p;
  return to;
}


/*#####  #    #  #    #   ####    #####     #     ####   #    #
 #       #    #  ##   #  #    #     #       #    #    #  ##   #
 #####   #    #  # #  #  #          #       #    #    #  # #  #
 #       #    #  #  # #  #          #       #    #    #  #  # #
 #       #    #  #   ##  #    #     #       #    #    #  #   ##
 #        ####   #    #   ####      #       #     ####   #    #*/

void CMiniInterpreter::ExecuteFunction(functionDescriptor_t* p_fun)
{
    auto oldList = m_pListofLocalVariables;  // backup for multiple levels
    m_pListofLocalVariables = new std::vector<std::string>;
    InterpretCode(p_fun->StartOfFuncode, eTT_KW_BraceClose);
    for (auto& name: *m_pListofLocalVariables) {
      DeleteVariable(name.c_str());
    }
    delete m_pListofLocalVariables;
    m_pListofLocalVariables = oldList;
}


bool CMiniInterpreter::ExecuteFunction(const char* p_name)
{
  auto itf = m_FunSpace.find(p_name);
  if (itf != m_FunSpace.end()) {  //std::cout << " function name found " << name << std::endl;
    m_LastFunctionDescriptor = itf->second;
    ExecuteFunction(m_LastFunctionDescriptor);
    return true;
  }
  return false;
}

void CMiniInterpreter::ExecuteFunction()
{
  #ifdef Debug
  std::cout << Colors::violet << "execute this-->" <<  Colors::white << std::endl;
  #endif // Debug
  // parse given parameters
  std::map<std::string,CVariable*>* backup = m_ParameterVariableMap;
  std::map<std::string,CVariable*> parmap;
  m_ParameterVariableMap = &parmap;
  // parse given parameters
  if (GetToken('l') != eTT_KW_RoundParOpen) { ThrowFatalError("Expected '(' "); }
  ETokenType totype;
  do {
    totype = GetToken('l');

  } while(totype != eTT_KW_RoundParClose);
  #ifdef Debug
  std::cout << Colors::violet << "execute this-->" << m_LastFunctionDescriptor->StartOfFuncode  <<  Colors::white << std::endl;
  #endif // Debug
  const char * backupPosition = m_CurPos;
  //InterpretCode(m_LastFunctionDescriptor->StartOfFuncode, eTT_KW_BraceClose);
  ExecuteFunction(m_LastFunctionDescriptor);
  // restore old parameters
  m_ParameterVariableMap = backup;
  m_CurPos = backupPosition; // continiue at old position
}

void CMiniInterpreter::InsertFunPointer(std::string p_funname, functionDescriptor_t* fundes)
{
  if (m_FunSpace.end() != m_FunSpace.find(p_funname)) {
    ThrowFatalError("duplicate function name [%s]",p_funname.c_str());
  };
  m_FunSpace[p_funname] = fundes;
}

void CMiniInterpreter::PreParseFunction()
{
   std::string funname;
   std::string varname;
   std::cout << Colors::blue <<  m_CurPos << Colors::white << std::endl;
   GetNewName(funname);
   functionDescriptor_t* fundes = new functionDescriptor_t;
   if (eTT_KW_RoundParOpen != GetToken()) { ThrowFatalError("expect '(' after function <name> [%s]",funname.c_str()); }
   ETokenType totype;
   do {
     totype = GetToken('l');
     if ((totype == eTT_KW_float) || (totype == eTT_KW_StringDesignator)) {
       GetNewName(varname);
       fundes->LocalVarNames.push_back(std::pair<std::string,ETokenType>(varname,totype));
     } else if ((totype != eTT_KW_Comma) && (totype != eTT_KW_RoundParClose)) { ThrowFatalError("unexpect token in function definition");  }
     std::cout << Colors::blue <<  m_CurPos << Colors::white << std::endl;
   } while (totype != eTT_KW_RoundParClose );
   if (GetToken('l') != eTT_KW_BraceOpen) { ThrowFatalError("unexpect token in function definition");  }
   fundes->StartOfFuncode = m_CurPos;
   SkipPair(eTT_KW_BraceOpen,eTT_KW_BraceClose,false);
   InsertFunPointer(funname,fundes);
   // parse parameters
   #ifdef Debug
   std::cout << " done:" << Colors::blue <<  m_CurPos << Colors::white << std::endl;
   #endif // Debug
   // advance m_CurPos first behind function parameter and then behind function body.
}

float CMiniInterpreter::ExecuteBuiltIn()
{
    // and now parse the arguments
    std::vector<CVariable*> paramList;
    ETokenType totype = GetToken('p');
    ETokenType NextExpected = eTT_KW_RoundParOpen;
    while (totype != eTT_KW_RoundParClose) {
      //std::cout << " ExecBuilt in : " << totype << std::endl;
      if ((totype != NextExpected) && (NextExpected != eTT_KW_DontCare)) { ThrowFatalError("Unexpected token while parsing parameter list to call");}

      switch (totype) {
        case eTT_ST_Variable :
          paramList.push_back(m_lValueVar);
          NextExpected = eTT_KW_Comma;
        break;
        case eTT_KW_Comma:
          NextExpected = eTT_KW_DontCare;
        break;
        case eTT_ST_NumericValue:
          {
            CVariable* pVar = new CVariable(CVariable::eVT_float,true);
            pVar->SetFloatValue(m_tokenValue);
            paramList.push_back(pVar);
            NextExpected = eTT_KW_Comma;
          }
        break;
        case eTT_SN_StringConstant:
          {
            CVariable* pVar = new CVariable(CVariable::eVT_string,true);
            //std::cout << " StringConstant Found :" << m_StringConstant << std::endl;
            pVar->SetStringValue(m_StringConstant);
            paramList.push_back(pVar);
            NextExpected = eTT_KW_Comma;
          }
        break;
        // todo numeric or string
        default :
          if (totype != NextExpected) {
            ThrowFatalError("Unexpected token while parsing parameter list 2");
          } else {
             NextExpected = eTT_KW_DontCare;
          }
        break;
      }
      totype = GetToken('p');
    }
    //std::cout << "execute the function " << std::endl;
    m_tokenValue = m_LastBuiltInFunction(paramList);
    // now delete specialy created vars
    for (auto par: paramList) {
      if (par->GetStackVarFlag()){delete par;}
    }
    return m_tokenValue;
}
/*    #  #    #     #    #       ######
 #    #  #    #     #    #       #
 #    #  ######     #    #       #####
 # ## #  #    #     #    #       #
 ##  ##  #    #     #    #       #
 #    #  #    #     #    ######  ######*/

void CMiniInterpreter::ExecuteWhile()
{
  ETokenType totype = GetToken('l');
  if (totype != eTT_KW_RoundParOpen) { ThrowFatalError("Error no '(' after 'while'"); }
  const char * BeginOfExpression = m_CurPos;
  //std::cout << "\n     dump before entry >" << m_CurPos;
  while (0 != lrintf(EvaluateNumExpression(eTT_KW_RoundParClose))) {
    if (m_Abort) {return;}
    if (GetToken('l') != eTT_KW_BraceOpen) { ThrowFatalError("Error no '{' after 'while (..)'"); }
    InterpretCode(m_CurPos, eTT_KW_BraceClose);
    m_CurPos = BeginOfExpression; // back to begin if expression
    //std::cout << "\n     dump end of loop >" << m_CurPos;
  }
  //std::cout << "\n     dump after while loop >" << m_CurPos;
  SkipPair(eTT_KW_BraceOpen,eTT_KW_BraceClose);
}

void CMiniInterpreter::ExecuteIf()
{
  bool elseFlag = false;
  ETokenType totype = GetToken('l');
  if (totype != eTT_KW_RoundParOpen) { ThrowFatalError("Error no '(' after 'if'"); }
  if ( 0 != lrintf(EvaluateNumExpression(eTT_KW_RoundParClose))){
    //std::cout << Colors::violet << m_CurPos << std::endl;
    if (GetToken('l') != eTT_KW_BraceOpen) { ThrowFatalError("Error no '{' after 'if()'"); }
    InterpretCode(m_CurPos, eTT_KW_BraceClose);
  } else {
    SkipPair(eTT_KW_BraceOpen,eTT_KW_BraceClose);
    elseFlag = true;
  }
  const char * PosBeforeSearchElse = m_CurPos; // in case we don't find an else we go back to this position
  totype = GetToken('l');
  if (totype != eTT_KW_Else) {m_CurPos =PosBeforeSearchElse; return;  }  // // thereis no else after the if
  if (elseFlag) {
     if (GetToken('l') != eTT_KW_BraceOpen) { ThrowFatalError("Error no '{' after 'if()'"); }
     InterpretCode(m_CurPos, eTT_KW_BraceClose);
  } else {
    SkipPair(eTT_KW_BraceOpen,eTT_KW_BraceClose);
  }
}

void CMiniInterpreter::SkipPair(ETokenType p_Starttoken,ETokenType p_Endtoken, bool p_first)
{
  if (p_first) {
    if (GetToken('l') != p_Starttoken) { ThrowFatalError("Error SkipPair no '{' "); }
  }
  ETokenType totype;
  do {
    totype = GetToken('l');
    if (totype == p_Starttoken) {SkipPair(p_Starttoken,p_Endtoken,false);}
    if (totype == eTT_SN_Zero) { ThrowFatalError("Error SkipPair no '}' before end of file");}
  } while(totype != p_Endtoken);
}





void CMiniInterpreter::InterpretCode(const char * p_code, ETokenType p_Endtoken)
{
  m_Abort = false;
  m_RecursionLevel++;
  if (m_RecursionLevel==0){
    m_StartPosAtReclevel0  = p_code;
  }
    //printf("%s",p_code);
    m_CurPos = p_code;
    m_StartPos = p_code;
    while (!m_Abort) {
      ETokenType totype = GetToken('l');
      //std::cout << "while after get token " << std::endl;
      if (nullptr != m_CallBack) {
        m_Abort = m_CallBack(GetCurrentLine(),m_VarMap);
      }

      if (totype == p_Endtoken) {
       //std::cout << "endtoken found \n";
       m_RecursionLevel--;
       return;
      }
      switch (totype) {
        case eTT_KW_float:
          CreateVariable(CVariable::eVT_float);
        break;
        case eTT_KW_StringDesignator:
          CreateVariable(CVariable::eVT_string);
        break;
        case eTT_ST_Variable:
          {
            CVariable* Lvar = m_lValueVar; // back up because BuiltIn Function calls will overwrite this
            uint32_t LvarIndex = m_lValueVar->GetLIndex();
            if (GetToken('l') != eTT_SN_Equal) { ThrowFatalError("no '=' after variable name"); }
            if ((Lvar->GetType() == CVariable::eVT_float) || (Lvar->GetType() == CVariable::eVT_floatArray)) {
              Lvar->SetFloatValue(EvaluateNumExpression(eTT_SN_Semicolon),LvarIndex);
            } else {
              Lvar->SetStringValue(EvaluateStringExpression(eTT_SN_Semicolon));
            }
          }
        break;
        case eTT_SN_Zero:
          //std::cout << "script exit, processed:" << m_CurPos - m_StartPos << " of " << strlen(p_code) << std::endl;
          m_RecursionLevel--;
          return;
        break;
        case eTT_SN_Semicolon: // stray semicolon
          //std::cout << "unused semicolon" << std::endl;
        break;
        case eTT_KW_Function: // a function definition
          PreParseFunction();
        break;
        case eTT_SN_FunctionName: // a function call
          ExecuteFunction();
        break;
        case eTT_KW_While:  // while detected
          ExecuteWhile();
        break;
        case eTT_NM_BuiltIn: // a built in function call
          ExecuteBuiltIn();
        break;
        case eTT_KW_If:
          ExecuteIf();
        break;
        default :
          ThrowFatalError("Unexpected token totype[%d]",totype);
          m_RecursionLevel--;
          return;
        break;
      }

      //printf("Gettoken result %i  %s \n",totype, m_tokenName);
      //if (totype == eTT_SN_Semicolon) {statementDone = true;}
    }
    m_RecursionLevel--;
    std::cout << m_RecursionLevel << " abort\n";
}
