#ifndef CWPPWINDOWSDEBUGGER_H
#define CWPPWINDOWSDEBUGGER_H

#include <windows.h>
#include <map>
#include <string>
#include <vector>
#include <thread>
#include <mutex>


#define MSGID_SINGLESTEP 101
#define MSGID_RUN        102
#define MSGID_ABORT      103
#define MSGID_BREAK      104

class CVariable;
void EndDebugger();
void OpenDebugger(const char * p_code);
bool StepCallBack(uint32_t p_line, std::map<std::string,CVariable*>& p_VarMap);

class CwppWindowsDebugger
{
  public:
    CwppWindowsDebugger();
    int OpenWindow();
    void Destroy();
    void Command(uint32_t id);
    bool StepCallBack(uint32_t p_line, std::map<std::string,CVariable*>& p_VarMap);
    void Paint();
    void SetCode(const char * p_code);
    void PaintPointer(HDC hdc, uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2);
    void Timer();
  protected:

  private:
    bool m_AdvanceASingleStepFlag {false};
    bool m_StoppedFlag {true};
    bool m_AbortFlag {false};
    std::vector<std::string>    m_VarDescr;
    char * m_code {nullptr};
    HWND      m_hwnd{0};
    HINSTANCE m_hInstance {0};
    std::vector<const char *> m_linevec;
    uint32_t  m_CurrentLine {3};
    uint32_t  m_PreviousLine {2};
    bool m_update{true};
    HPEN m_hFramePen;
    HPEN m_hDonePen;
    std::mutex m_mut;
};

#endif // CWPPWINDOWSDEBUGGER_H
