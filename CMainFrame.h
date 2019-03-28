#ifndef CMAINFRAME_H
#define CMAINFRAME_H
#include <wx/frame.h>
#include <wx/spinctrl.h>
#include <wx/stattext.h>
#include <wx/filedlg.h>
#include <wx/textdlg.h>
#include <fstream>
#include <wx/colordlg.h>
#include "CLZReceiver.h"
#include "CLZProcess.h"
#include "CManualDialog.h"
class CMainFrame: public wxFrame
{
public:
    CMainFrame(const wxString &title, wxSize init_size);
    wxMenu *m_lpFileMenu, *m_lpViewMenu, *m_lpEditMenu, *m_lpHelpMenu;
    wxToolBar *m_lpToolBar;
    wxSpinCtrl *m_lpTimeSpinCtrl, *m_lpIntervalSpinCtrl;
	wxSlider *m_lpAnalyzeSlider;
	wxStatusBar *m_lpStatusBar;
    CCanvas *m_lpCanvas;
    CLZReceiver *m_lpLZReceiver;
    CLZProcess *m_lpLZProcess;
    wxString m_wxstrEnginePath, m_wxstrWeightPath, m_wxstrExtraPara;
    PROCESS_EXIT_TYPE m_ProcessExitType;
    bool m_bPathChanged;
protected:
    void OnNew(wxCommandEvent &event);
    void OnOpen(wxCommandEvent &event);
    void OnSave(wxCommandEvent &event);
    void OnShowStep(wxCommandEvent &event);
	void OnSetGameboardColor(wxCommandEvent &event);
    void OnScore(wxCommandEvent &event);
    void OnSelectEngine(wxCommandEvent &event);
    void OnSelectWeight(wxCommandEvent &event);
    void OnLeelaZero(wxCommandEvent &event);
    void OnBackward(wxCommandEvent &event);
    void OnForward(wxCommandEvent &event);
    void OnBlackDog(wxCommandEvent &event);
    void OnWhiteDog(wxCommandEvent &event);
	void OnManual(wxCommandEvent &event);
	void OnAbout(wxCommandEvent &event);
    void OnAnalyze(wxCommandEvent &event);
    long m_fnOpenLZProcess();
    void OnLZProcessExit(wxProcessEvent &event);
    void OnExit(wxCommandEvent &event);
    void OnClose(wxCloseEvent &event);
private:
	void m_fnSetupMenu();
	void m_fnSetupToolBar();
	void m_fnSetupStatusBar();
	void m_fnCreateCanvas();
	void m_fnPrepareEngine();
    DECLARE_EVENT_TABLE()
};
#endif // CMAINFRAME_H
