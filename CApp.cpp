#include "CApp.h"
IMPLEMENT_APP(CApp);
bool CApp::OnInit()
{
    m_lpFrame = new CMainFrame(_("LZRobe"), wxSize(950, 650));
    m_lpFrame->SetIcon(wxICON(MAIN_ICON));
	if (argc > 1)
	{
		if (argv[1].length() > 0 && strcmp(strrchr(argv[1], '.') , ".sgf") == 0)
		{
			m_lpFrame->m_fnOpenSGF(argv[1].char_str());
		}
	}
    m_lpFrame->Show();
    return true;
}
