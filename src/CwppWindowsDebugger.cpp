#include "CwppWindowsDebugger.h"
#include "../include/CVariable.h"
#include <tchar.h>
#include <windows.h>
#include <iostream>
#include <functional>
#include <thread>


CwppWindowsDebugger ThisDebugger;


bool StepCallBack(uint32_t p_line, std::map<std::string,CVariable*>& p_VarMap)
{
  return ThisDebugger.StepCallBack(p_line,p_VarMap);
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

      switch (message) {
        case WM_DESTROY:
          ThisDebugger.Destroy();
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        case WM_TIMER:
          ThisDebugger.Timer();
            break;

        case WM_COMMAND:
          ThisDebugger.Command(LOWORD(wParam));
            break;
        case WM_PAINT:
          ThisDebugger.Paint();
        break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}

void CwppWindowsDebugger::Destroy()
{
  m_AbortFlag = true;
}

void CwppWindowsDebugger::Command(uint32_t id)
{
  if (id == MSGID_SINGLESTEP) {
    m_AdvanceASingleStepFlag = true;
  } else if (id == MSGID_BREAK) {
    m_StoppedFlag = true;
    m_AdvanceASingleStepFlag = false;
    m_AbortFlag = false;
  } else if (id == MSGID_RUN) {
    m_StoppedFlag = false;
  } else if (id == MSGID_ABORT) {
     m_AbortFlag = true;
     m_StoppedFlag = false;
  }

}

CwppWindowsDebugger::CwppWindowsDebugger(){
    m_hFramePen = CreatePen(PS_SOLID, 3, RGB(200, 0, 0));
    m_hDonePen = CreatePen(PS_SOLID, 3, RGB(220, 180, 180));
}

void CwppWindowsDebugger::Timer()
{
  if (m_update) {
     m_update = false;
     InvalidateRect (m_hwnd, NULL, FALSE);
     //RedrawWindow(m_hwnd,NULL,NULL,0);
     UpdateWindow( m_hwnd);
  }
}


bool CwppWindowsDebugger::StepCallBack(uint32_t p_line, std::map<std::string,CVariable*>& p_VarMap)
{
  if (p_line == m_CurrentLine) return m_AbortFlag;
  size_t varmapSize = p_VarMap.size();

  if ( m_VarDescr.size() < varmapSize) {
      m_VarDescr.resize(varmapSize);
  }
  uint32_t index = 0;
  m_mut.lock();
  for (auto it : p_VarMap) {
    //it.second->SetArrayWriteIndex(-1);
    m_VarDescr[index] = it.second->GetName() + " = " + it.second->GetString() +  "              ";
  //  snprintf(&m_VarDesc[index],50,"%s",it->second->GetName().c_str());
    index++;
  }
  m_mut.unlock();
  m_PreviousLine = m_CurrentLine;
  m_CurrentLine = p_line;
  m_update = true;
  bool wait = true;
  while (wait ) {
    if (m_AdvanceASingleStepFlag) { wait = false;}
    if (m_StoppedFlag == false) { wait = false;}
    //Sleep(180);
  }
  m_AdvanceASingleStepFlag = false;
  return m_AbortFlag;
}

void CwppWindowsDebugger::SetCode(const char * p_code)
{
  if (m_code != nullptr ) delete m_code;
  m_code = nullptr;
  size_t len = strlen(p_code);
  m_code = new char[len+2];
  m_linevec.push_back(&m_code[0]);
  for (uint32_t i = 0; i < len; i++) {
    if (p_code[i] == 10) {
      m_linevec.push_back(&m_code[i+1]);
      m_code[i]=0;
    } else {
      m_code[i]=p_code[i];
    }
  }
}

std::thread DebuggerThread;

void OpenDebuggerThread()
{
  ThisDebugger.OpenWindow();
}

void EndDebugger()
{
  DebuggerThread.join();
}

void OpenDebugger(const char * p_code)
{
  ThisDebugger.SetCode(p_code);
  DebuggerThread = std::thread{  OpenDebuggerThread };

 // ThisDebugger.OpenWindow();
}

void CwppWindowsDebugger::PaintPointer(HDC hdc, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2)
{
  MoveToEx(hdc, x1, y1,(LPPOINT) NULL);
  LineTo(hdc,  x2 - 10, y2);LineTo(hdc, x2 - 10, y2-7);LineTo(hdc, x2, y2);LineTo(hdc, x2 - 10, y2+7);LineTo(hdc, x2 - 10, y2);
}

void CwppWindowsDebugger::Paint()
{
    PAINTSTRUCT ps;
    HDC hdc;
    hdc = BeginPaint(m_hwnd, &ps);
    tagRECT Rect;
    GetClientRect(m_hwnd,&Rect);
    uint32_t posx = 10;
    uint32_t posy = 40;
    uint32_t linecnt  = 1;

    for (auto ln : m_linevec){
      char line[6];
      snprintf(line,sizeof(line),"% 4d",linecnt);
      TextOut(hdc, posx, posy ,line, strlen(line));
      TextOut(hdc, posx+50, posy ,ln, strlen(ln));
      if (m_PreviousLine == linecnt) {
        HPEN defPen = (HPEN) SelectObject(hdc,m_hDonePen);
        PaintPointer(hdc,posx+30, posy+5,posx+50, posy+5);
        SelectObject(hdc,defPen);
      }
      if (m_CurrentLine == linecnt) {
        HPEN defPen = (HPEN) SelectObject(hdc,m_hFramePen);
        PaintPointer(hdc,posx+30, posy+5,posx+50, posy+5);
        SelectObject(hdc,defPen);
      }
      posy = posy + 18;
      linecnt++;
    }
    posx = 420;
    posy = 40;
    //std::cout << "map size " << m_VarDescr.size() << "\n";
    m_mut.lock();
    for (auto str : m_VarDescr){
      TextOut(hdc, posx, posy ,str.c_str(), str.size());
      posy = posy + 18;
    }
    m_mut.unlock();
    EndPaint(m_hwnd, &ps);
}


int CwppWindowsDebugger::OpenWindow()
{
  m_hInstance = GetModuleHandle(0);
  static const char* classname = "wppdebugger";
  MSG messages;            /* Here messages to the application are saved */
  WNDCLASSEX wincl;        /* Data structure for the windowclass */
  /* The Window structure */
  wincl.hInstance = GetModuleHandle(0);
  wincl.lpszClassName = classname;
  wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
  //wincl.lpfnWndProc = [](HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)->LRESULT{ return 0;}
  wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
  wincl.cbSize = sizeof (WNDCLASSEX);

  /* Use default icon and mouse-pointer */
  wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
  wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
  wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
  wincl.lpszMenuName = NULL;                 /* No menu */
  wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
  wincl.cbWndExtra = 0;                      /* structure or the window instance */
  /* Use Windows's default colour as the background of the window */
  wincl.hbrBackground = (HBRUSH) CreateSolidBrush(RGB(255, 255, 255)); // COLOR_BACKGROUND;

  /* Register the window class, and if it fails quit the program */
  if (!RegisterClassEx (&wincl)) { return 0; }

    m_hwnd = CreateWindowEx ( 0, classname,_T("Debugger"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,CW_USEDEFAULT,644,575,HWND_DESKTOP, NULL, m_hInstance, NULL );
   CreateWindow("BUTTON","Single Step", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 10,10,80,24,m_hwnd,(HMENU)MSGID_SINGLESTEP,(HINSTANCE) m_hInstance,NULL);
   CreateWindow("BUTTON","Run", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 100,10,80,24,m_hwnd,(HMENU)MSGID_RUN,(HINSTANCE) m_hInstance,NULL);
   CreateWindow("BUTTON","Break", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 190,10,80,24,m_hwnd,(HMENU)MSGID_BREAK,(HINSTANCE) m_hInstance,NULL);
   CreateWindow("BUTTON","Abort", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 280,10,80,24,m_hwnd,(HMENU)MSGID_ABORT,(HINSTANCE) m_hInstance,NULL);
    SetTimer(m_hwnd,1,50,(TIMERPROC) NULL);

    ShowWindow (m_hwnd, 1);
    while (GetMessage (&messages, NULL, 0, 0))    {
        TranslateMessage(&messages);
        DispatchMessage(&messages);
    }
    return messages.wParam;
}
