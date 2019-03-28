#include "CApp.h"
IMPLEMENT_APP(CApp);
bool CApp::OnInit()
{
    m_lpFrame = new CMainFrame(_("LZRobe"), wxSize(900, 600));
    m_lpFrame->SetIcon(wxICON(MAIN_ICON));
    m_lpFrame->Show();
    return true;
}
