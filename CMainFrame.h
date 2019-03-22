#ifndef CMAINFRAME_H
#define CMAINFRAME_H
#include <wx/frame.h>
#include <wx/spinctrl.h>
#include <wx/stattext.h>
#include <wx/filedlg.h>
#include <wx/textdlg.h>
#include <fstream>
#include "CLZReceiver.h"
class CMainFrame: public wxFrame
{
public:
    CMainFrame(const wxString &title, wxSize init_size);
    wxMenu *m_lpFileMenu, *m_lpEditMenu, *m_lpViewMenu;
    wxToolBar *m_lpToolBar;
    wxSpinCtrl *m_lpTimeSpinCtrl, *m_lpIntervalSpinCtrl;
    CCanvas *m_lpCanvas;
    CLZReceiver *m_lpLZReceiver;
    CLZProcess *m_lpLZProcess;
    wxString m_wxstrEnginePath, m_wxstrWeightPath, m_wxstrExtraPara;
    PROCESS_EXIT_TYPE m_ProcessExitType;
    bool m_bPathChanged;
    //wxTimer m_Timer;
private:
    void OnNew(wxCommandEvent &event);
    void OnOpen(wxCommandEvent &event);
    void OnSave(wxCommandEvent &event);
    void OnShowStep(wxCommandEvent &event);
    void OnScore(wxCommandEvent &event);
    void OnSelectEngine(wxCommandEvent &event);
    void OnSelectWeight(wxCommandEvent &event);
    void OnLeelaZero(wxCommandEvent &event);
    void OnBackward(wxCommandEvent &event);
    void OnForward(wxCommandEvent &event);
    void OnBlackDog(wxCommandEvent &event);
    void OnWhiteDog(wxCommandEvent &event);
    void OnAnalyze(wxCommandEvent &event);
    void OnLZProcessExit(wxProcessEvent &event);
    long m_fnOpenLZProcess();
    void OnExit(wxCommandEvent &event);
    void OnClose(wxCloseEvent &event);
    //void OnTimer(wxTimerEvent &event);
    DECLARE_EVENT_TABLE()
};
#endif // CMAINFRAME_H
