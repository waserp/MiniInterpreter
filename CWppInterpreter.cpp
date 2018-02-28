





#include "CWppInterpreter.h"
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
  {eTT_SN_Zero, "dfdfd" },
  {eTT_KW_RoundParOpen,"("},
  {eTT_KW_RoundParClose,")"},
  {eTT_SN_LISTEND,""} // mark the end of the list, let this allways at bottom
};

const char * helperTo2Str(ETokenType to){KeyWordList_t* kp= &KeyWords[0]; while (kp->token!= eTT_SN_LISTEND) { if (kp->token == to) return kp->name; kp++;} return "unknown :( !"; }


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

ETokenType CMiniInterpreter::GetToken(const char type)
{
    while (isspace(*m_CurPos)) { //(*m_CurPos==' ') || (*m_CurPos=='\t') || (*m_CurPos=='\n') || (*m_CurPos=='\r')) {
        m_CurPos++; // remove whitespace
    }

    if (type == 'n') {  // expect a number, so first try read number
      printf("\n  type = 'n' rm whitespace>%s<\n",m_CurPos);
      //system("read a");
      if (TryReadNumber()) { return eTT_ST_NumericValue; }
    }

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
    printf("search in varspace\n");
    for (auto var : m_VarSpace) { // check if it is a variable
      if ( keyComp(var->m_name.c_str())) {
        if (type == 'l') { m_lValueVar = var; printf("det Lvar %s\n",var->m_name.c_str()); return eTT_ST_Variable; }
        else {  m_tokenValue = var->m_valnum; printf("det var %s\n",var->m_name.c_str()); return eTT_ST_NumericValue; } // directly resolve to num value if we are r
      }
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
  while (isalnum(*m_CurPos)) {
    p_name += *m_CurPos;
    m_CurPos++;
  }
}


float CMiniInterpreter::EvaluateNumExpression(const char * p_expression)
{
  m_CurPos = p_expression;
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
  std::cout << "enter" << std::endl;
  class oQType {public:oQType(float p_val,ETokenType p_tok):val(p_val),tok(p_tok){}float val;ETokenType tok;};
  std::vector<oQType> outputQueue;
  std::vector<ETokenType> tokenStack;
  int16_t LastPrecedence = -1; // +- have 0, */ have 1, ^ has 2
  char nextTtype = 'n';
  ETokenType totype = GetToken(nextTtype);  // expect number
  while (totype != p_Endtoken) {
    std::cout << "start of while >" << m_CurPos << "< analyzing" << helperTo2Str(totype) << std::endl;
    if (totype == eTT_KW_RoundParOpen) {
      nextTtype = 'l';
      std::cout << " -------------> recursion enter\n";
      outputQueue.push_back(oQType(EvaluateNumExpression(eTT_KW_RoundParClose),eTT_ST_NumericValue));
      std::cout << " -------------> recursion done\n";
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
    } else {
      std::cout << " Error ++++++++++> unexpecte token \n" << helperTo2Str(totype) << std::endl;
    }


    // dump queues for debug
    std::cout << "tokenstack: ";
    for (auto to : tokenStack) {       std::cout << helperTo2Str(to) << ",";    } std::cout << std::endl;
    std::cout << "outqueue  : ";
    for (auto oQ : outputQueue) {      if (oQ.tok == eTT_ST_NumericValue) std::cout << oQ.val << " ";       else std::cout << helperTo2Str(oQ.tok);     } std::cout << std::endl;
    std::cout << "after dump:" << m_CurPos << std::endl;
    //system("read a");

    totype = GetToken(nextTtype);

  }
  // all operators to output q
  while (tokenStack.size() > 0) {
    outputQueue.push_back(oQType(nanf("0"),tokenStack.back()));
    tokenStack.pop_back();
  }

  // dump queues for debug
  std::cout << "tokenstack:" << std::endl;
  for (auto to : tokenStack) {       std::cout << helperTo2Str(to) << " ";    } std::cout << std::endl;    std::cout << "outqueue:" << std::endl;
  for (auto oQ : outputQueue) {      if (oQ.tok == eTT_ST_NumericValue) std::cout << oQ.val << " ";       else std::cout << helperTo2Str(oQ.tok);     } std::cout << std::endl;

  std::vector<float> rpnstack;
  float result = 0.0F;
  // evaluate rpn
  for (oQType oQ : outputQueue) {
    if (oQ.tok == eTT_ST_NumericValue) {
      std::cout << "push to rpn" << oQ.val << "\n";
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
      std::cout << "result : " << result << "\n";
    }
  }
  return result;
}

void CMiniInterpreter::CreateVariable()
{
  if ( GetToken() != eTT_SN_LISTEND ) {printf("fatal expect new variable name after float, instead got [%s]\n",m_tokenName);}
  CVariable* pVar = new CVariable;
  GetNewName(pVar->m_name);
  printf("Variable with name :[%s] created\n",pVar->m_name.c_str());
  ETokenType totype = GetToken();
  if (totype == eTT_SN_Semicolon) { return; } // were done, ok
  if (totype == eTT_SN_Equal) { pVar->m_valnum = EvaluateNumExpression(eTT_SN_Semicolon); return;}
  printf("fatal expect Semicolon after Variable definition name[%s] [%i]\n",m_tokenName, totype);
}

void CMiniInterpreter::InterpretCode(const char * p_code)
{
    //printf("%s",p_code);
    m_CurPos = p_code;
    bool statementDone = false;
    while (!statementDone) {
      ETokenType totype = GetToken('l');
      switch (totype) {
        case eTT_KW_float:
          CreateVariable();
        break;
        case eTT_ST_Variable:
          m_lValueVar->m_valnum = EvaluateNumExpression(eTT_SN_Semicolon);
        break;
        default :
          return;
        break;
      }
      printf("Gettoken result %i  %s \n",totype, m_tokenName);
      if (totype == eTT_SN_Semicolon) {statementDone = true;}
    }
}
