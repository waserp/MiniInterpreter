





#include "include/CWppInterpreter.h"
#include "include/CColors.h"
#include <cstdio>
#include <cstdint>
#include <cstring>
#include <ctype.h>
#include <iostream>



struct KeyWordList_t {
    ETokenType   token;
    const char * name;
};

KeyWordList_t KeyWords[] = {
  {eTT_KW_float,"float"},
  {eTT_SN_Plus,"+"},
  {eTT_SN_Minus,"-"},
  {eTT_SN_Equal,"="},
  {eTT_SN_Mul,"*"},
  {eTT_SN_Div,"/"},
  {eTT_SN_Semicolon,";"},
  {eTT_KW_Comma,","},
  {eTT_SN_Zero, "ThisIsTheEndMyFriend" },
  {eTT_KW_RoundParOpen,"("},
  {eTT_KW_RoundParClose,")"},
  {eTT_KW_Function,"function"},
  {eTT_KW_DoubleQuotes,"\""},
  {eTT_SN_LISTEND,""} // mark the end of the list, let this allways at bottom
};

const char * helperTo2Str(ETokenType to){KeyWordList_t* kp= &KeyWords[0]; while (kp->token!= eTT_SN_LISTEND) { if (kp->token == to) return kp->name; kp++;} return "unknown :( !"; }


CMiniInterpreter::CMiniInterpreter()
{
  PushBuiltIns();
}

CMiniInterpreter::~CMiniInterpreter()
{
}

void ParChecker(const uint32_t p_count, const char * p_name, std::vector<CVariable*>& parVec)
{
  if (parVec.size() != p_count) { throw std::runtime_error(("Error, wrong number of parameters, expected [" + std::to_string(p_count) + "] detected [" + std::to_string(parVec.size()) + "]").c_str()); }
}

void CMiniInterpreter::PushBuiltIns()
{
  m_BuiltInFunMap["print"] = [](std::vector<CVariable*>& parVec){ std::cout << Colors::yellow; for (auto pPar : parVec) { std::cout << pPar->GetString(); }  std::cout << Colors::white; return 0.0F;};
  m_BuiltInFunMap["sin"] = [](std::vector<CVariable*>& parVec){ std::cout << Colors::green << "fun sinus:" << sin(parVec[0]->GetFloatValue()) << Colors::white; return sin(parVec[0]->GetFloatValue());};
  //m_BuiltInFunMap["max"] = [](std::vector<CVariable*>& parVec){ float val; for (auto pPar : parVec) {  }  return 0.0F;};
}



uint32_t CMiniInterpreter::GetCurrentLine()
{
  uint32_t linecounter = 1;
  const char * sp = m_StartPos;
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
    //system("read a");
  }
  m_tokenName = p_keyword;
  if (!isalnum(p_keyword[0])) { m_CurPos = pt; return true; } // keywords like "+" "-" etc can be followed by letters i.e. a=b+c
  if (!isalnum(*pt)) { m_CurPos = pt; return true; }           // keywords like "float" can not be followed by letters i.e. floatFoo is not keyword float
  printf(" pt = %c isalnum = %i",*pt,isalnum(*pt));
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
  m_tokenValue = atof(m_CurPos);
  m_CurPos = pt;
  printf("try read number success [%f] \n",m_tokenValue);
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
    if (*m_CurPos==0) { throw std::runtime_error(("Error, Reading string constant no terminating '\"' detected"));   }
    m_StringConstant += *m_CurPos;
    m_CurPos++;
  }
  m_CurPos++;
  return true;
}

ETokenType CMiniInterpreter::GetToken(const char type)
{
    while (isspace(*m_CurPos)) { //(*m_CurPos==' ') || (*m_CurPos=='\t') || (*m_CurPos=='\n') || (*m_CurPos=='\r')) {
        m_CurPos++; // remove whitespace
    }

    if (*m_CurPos == 0) return eTT_SN_Zero;

    if (type == 'n') {  // expect a number, so first try read number
      //printf("\n  type = 'n' rm whitespace>%s<\n",m_CurPos);
      //system("read a");
      if (TryReadNumber()) { return eTT_ST_NumericValue; }
    }
    if (TryReadStringConstant()) { return eTT_SN_StringConstant;}

//    printf("\nrm whitespace>%s<\n",m_CurPos);
    // now search keywords
    KeyWordList_t* pkwl = KeyWords;
    while (pkwl->token != eTT_SN_LISTEND) { //printf(" compare to -->%s\n",pkwl->name);
      if (keyComp(pkwl->name)) {
        printf("found token -->%s %i\n",pkwl->name,pkwl->token);
        return pkwl->token;
      }
      pkwl++;
    }
    //printf("search in varspace\n");
    for (auto var : m_VarSpace) { // check if it is a variable
      if ( keyComp(var->m_name.c_str())) {
        if (type == 'l') { m_lValueVar = var; printf("det Lvar %s\n",var->m_name.c_str()); return eTT_ST_Variable; }
        else {  m_tokenValue = var->m_valnum; printf("det var %s\n",var->m_name.c_str()); return eTT_ST_NumericValue; } // directly resolve to num value if we are r
      }
    }
    std::string name;
    if (TryReadName(name)) {  // we got some sort of name
      std::cout << " TryReadName succcess  found" << name << std::endl;
      auto it = m_BuiltInFunMap.find(name);
      if (it != m_BuiltInFunMap.end()) { std::cout << " Build In found found" << name << std::endl;
        m_LastBuiltInFunction = it->second;
        return eTT_NM_BuiltIn;
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
     printf("fatal expect new variable name after float, instead got [%s]\n",m_tokenName);
     throw std::runtime_error(("fatal expect new variable name instead got [" + p_name + "]").c_str());
  }

  while (isalnum(*m_CurPos)) {
    p_name += *m_CurPos;
    m_CurPos++;
  }
}


float CMiniInterpreter::EvaluateNumExpression(const char * p_expression)
{
  m_CurPos = p_expression;
  m_StartPos = p_expression;
  std::cout << "--------------------------------------------\n" << p_expression << "\n";
  return EvaluateNumExpression(eTT_SN_Semicolon);
}



/*
Example with negative numbers:  5      +     -3      ;
                                <num>  <op>  <num>


*/

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
    } else {
      std::string errorCode = std::string("Error: unexpected token EvaluateNumExpression Line: ")+  std::to_string(GetCurrentLine()) + " totype " + std::to_string(totype);
      throw std::runtime_error(errorCode.c_str());
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
        case eTT_SN_Plus: result = opa + opb; std::cout << opa << " + " << opb <<  " = " << result << "\n";
        break;
        case eTT_SN_Minus: result = opb - opa ; std::cout << opb << " - " << opa <<  " = " << result << "\n";
        break;
        case eTT_SN_Mul: result = opa * opb; std::cout << opa << " * " << opb <<  " = " << result << "\n";
        break;
        case eTT_SN_Div: result = opb / opa; std::cout << opa << " / " << opb <<  " = " << result << "\n";
        default :
        break;
      }
      rpnstack.push_back(result);
      //std::cout << "result : " << result << "\n";
    }
  }
  return result;
}

void CMiniInterpreter::CreateVariable(CVariable::eVarType p_VarType)
{

  CVariable* pVar = new CVariable(p_VarType);
  GetNewName(pVar->m_name);
  printf("Variable with name :[%s] created\n",pVar->m_name.c_str());
  m_VarSpace.push_back(pVar);
  ETokenType totype = GetToken();
  if (totype == eTT_SN_Semicolon) { return; } // were done, ok
  if (totype == eTT_SN_Equal) { pVar->m_valnum = EvaluateNumExpression(eTT_SN_Semicolon); return;}
  printf("fatal expect Semicolon after Variable definition name[%s] [%i]\n",m_tokenName, totype);
  throw std::runtime_error(("Error fatal expect Semicolon after Variable definition. Variable Name[" + pVar->m_name + "] totype[" + std::to_string(totype) + "] Line["+ std::to_string(GetCurrentLine()) +"]\n").c_str());
}
void CMiniInterpreter::PreParseFunction()
{
   std::string funname;
   GetNewName(funname);
   InsertFunPointer(funname,m_CurPos);
   // advance m_CurPos first behind function parameter and then behind function body.
   //FindNext("(");
   //FindNext(")");
   throw std::runtime_error("not yet implemented!");
}

float CMiniInterpreter::ExecuteBuiltIn()
{
    // and now parse the arguments
    std::vector<CVariable*> paramList;
    ETokenType totype = GetToken('l');
    ETokenType NextExpected = eTT_KW_RoundParOpen;
    while (totype != eTT_KW_RoundParClose) {
      std::cout << " ExecBuilt in : " << totype << std::endl;
      if ((totype != NextExpected) && (NextExpected != eTT_KW_DontCare)) {  throw std::runtime_error("Unexpected token while parsing parameter list");}

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
            std::cout << " StringConstant Found :" << m_StringConstant << std::endl;
            pVar->SetStringValue(m_StringConstant);
            paramList.push_back(pVar);
            NextExpected = eTT_KW_Comma;
          }
        break;
        // todo numeric or string
        default :
          if (totype != NextExpected) {
            throw std::runtime_error("Unexpected token while parsing parameter list 2");
          } else {
             NextExpected = eTT_KW_DontCare;
          }
        break;
      }
      totype = GetToken('l');
    }
    std::cout << "execute the function " << std::endl;
    m_tokenValue = m_LastBuiltInFunction(paramList);
    // now delete specialy created vars
    for (auto par: paramList) {
      if (par->GetStackVarFlag()){delete par;}
    }
    return m_tokenValue;
}

void CMiniInterpreter::InterpretCode(const char * p_code)
{
    printf("%s",p_code);
    m_CurPos = p_code;
    m_StartPos = p_code;
    bool statementDone = false;
    while (!statementDone) {
      ETokenType totype = GetToken('l');
      switch (totype) {
        case eTT_KW_float:
          CreateVariable(CVariable::eVT_float);
        break;
        case eTT_ST_Variable:
          m_lValueVar->m_valnum = EvaluateNumExpression(eTT_SN_Semicolon);
        break;
        case eTT_SN_Zero:
          std::cout << "script exit, processed:" << m_CurPos - m_StartPos << " of " << strlen(p_code) << std::endl;
          return;
        break;
        case eTT_SN_Semicolon: // stray semicolon
          std::cout << "unused semicolon" << std::endl;
        break;
        case eTT_KW_Function: // a function definition
        break;
        case eTT_NM_BuiltIn: // a built in function call
          ExecuteBuiltIn();
        break;
        default :
          throw std::runtime_error(("Error Unexpected token totype[" + std::to_string(totype) + "] Line["+ std::to_string(GetCurrentLine()) +"]\n").c_str());
          return;
        break;
      }
      printf("Gettoken result %i  %s \n",totype, m_tokenName);
      //if (totype == eTT_SN_Semicolon) {statementDone = true;}
    }
}
