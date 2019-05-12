#include "CMainFrame.h"
void CMainFrame::m_fnSetupMenu()
{
    wxMenuBar *lpMenuBar;
    m_lpFileMenu = new wxMenu(_(""));
    m_lpFileMenu->Append(wxID_NEW, _(STR_NEW), _(""), wxITEM_NORMAL);
	m_lpFileMenu->Append(ID_HANDICAP, _(STR_HANDICAP), _(""), wxITEM_NORMAL);
    m_lpFileMenu->Append(wxID_OPEN, _(STR_OPEN), _(""), wxITEM_NORMAL);
    m_lpFileMenu->Append(wxID_SAVE, _(STR_SAVE), _(""), wxITEM_NORMAL);
    m_lpFileMenu->Append(wxID_EXIT, _(STR_EXIT), _(""), wxITEM_NORMAL);
    m_lpEditMenu = new wxMenu(_(""));
    m_lpEditMenu->Append(wxID_UNDO, _(STR_BACKWARD), _(""), wxITEM_NORMAL);
    m_lpEditMenu->Append(wxID_REDO, _(STR_FORWARD), _(""), wxITEM_NORMAL);
    m_lpEditMenu->Append(ID_SELECT_ENGINE, _(STR_SELECT_ENGINE), _(""), wxITEM_NORMAL);
    m_lpEditMenu->Append(ID_SELECT_WEIGHT, _(STR_SELECT_WEIGHT), _(""), wxITEM_NORMAL);
    m_lpEditMenu->Append(ID_LEELA_ZERO, _(STR_RUN_ENGINE), _(""), wxITEM_NORMAL);
    m_lpEditMenu->Append(ID_FINAL_SCORE, _(STR_RESULT), _(""), wxITEM_NORMAL);
	m_lpEditMenu->Append(ID_EXTRA_PARA, _(STR_EXTRA_PARA), _(""), wxITEM_NORMAL);
	m_lpEditMenu->Append(ID_BOARD_SIZE, _(STR_BOARD_SIZE), _(""), wxITEM_NORMAL);
	m_lpCoordMenu = new wxMenu(_(""));
	m_lpCoordMenu->Append(ID_COORD_NULL, _(STR_COORD_NULL), _(""), wxITEM_RADIO);
	m_lpCoordMenu->Append(ID_COORD_NET, _(STR_COORD_NET), _(""), wxITEM_RADIO);
	m_lpCoordMenu->Append(ID_COORD_NUM, _(STR_COORD_NUM), _(""), wxITEM_RADIO);
	m_lpCoordMenu->Append(ID_COORD_SGF, _(STR_COORD_SGF), _(""), wxITEM_RADIO);
	m_lpCoordMenu->Append(ID_COORD_GTP, _(STR_COORD_GTP), _(""), wxITEM_RADIO);
	m_lpCoordMenu->Check(ID_COORD_NULL, true);
    m_lpViewMenu = new wxMenu(_(""));
    m_lpViewMenu->Append(ID_SHOW_STEP, _(STR_STEP), _(""), wxITEM_CHECK);
	m_lpViewMenu->Append(wxID_SELECT_COLOR, _(STR_SET_GAMEBOARD_COLOR), _(""), wxITEM_NORMAL);
	m_lpViewMenu->Append(ID_COORDINATE, _(STR_COORDINATE), m_lpCoordMenu);
	m_lpHelpMenu = new wxMenu(_(""));
	m_lpHelpMenu->Append(wxID_HELP_CONTEXT, _(STR_MANUAL), _(""), wxITEM_NORMAL);
	m_lpHelpMenu->Append(wxID_ABOUT, _(STR_ABOUT), _(""), wxITEM_NORMAL);
    lpMenuBar = new wxMenuBar();
    lpMenuBar->Append(m_lpFileMenu, STR_FILE);
    lpMenuBar->Append(m_lpEditMenu, STR_EDIT);
    lpMenuBar->Append(m_lpViewMenu, STR_VIEW);
	lpMenuBar->Append(m_lpHelpMenu, STR_HELP);
    SetMenuBar(lpMenuBar);
}

void CMainFrame::m_fnSetupToolBar()
{
    wxStaticText *lpStaticText;
    m_lpToolBar = new wxToolBar(this, wxID_ANY);
    m_lpToolBar->AddTool(wxID_NEW, _(""), wxBITMAP(NEW_BMP), _(STR_NEW));
    m_lpToolBar->AddTool(wxID_OPEN, _(""), wxBITMAP(OPEN_BMP), _(STR_OPEN));
    m_lpToolBar->AddTool(wxID_SAVE, _(""), wxBITMAP(SAVE_BMP), wxBITMAP(SAVE_DISABLE_BMP), wxITEM_NORMAL, _(STR_SAVE));
    m_lpToolBar->AddTool(wxID_UNDO, _(""), wxBITMAP(BACKWARD_BMP), wxBITMAP(BACKWARD_DISABLE_BMP), wxITEM_NORMAL, _(STR_BACKWARD));
    m_lpToolBar->AddTool(wxID_REDO, _(""), wxBITMAP(FORWARD_BMP), wxBITMAP(FORWARD_DISABLE_BMP), wxITEM_NORMAL, _(STR_FORWARD));
    m_lpToolBar->AddTool(ID_LEELA_ZERO, _(""), wxBITMAP(RUN_BMP), wxBITMAP(RUN_DISABLE_BMP), wxITEM_NORMAL, _(STR_RUN_ENGINE));
	m_lpToolBar->AddSeparator();
    m_lpToolBar->AddTool(ID_BLACK_DOG, _(""), wxBITMAP(BLACK_DOG_BMP), wxBITMAP(BLACK_DOG_DISABLE_BMP), wxITEM_CHECK, _(STR_BLACK_DOG));
    m_lpToolBar->EnableTool(ID_BLACK_DOG, false);
    m_lpToolBar->AddTool(ID_WHITE_DOG, _(""), wxBITMAP(WHITE_DOG_BMP), wxBITMAP(WHITE_DOG_DISABLE_BMP), wxITEM_CHECK, _(STR_WHITE_DOG));
    m_lpToolBar->EnableTool(ID_WHITE_DOG, false);
    lpStaticText = new wxStaticText(m_lpToolBar, wxID_ANY, _(STR_TIME));
    m_lpToolBar->AddControl(lpStaticText, _(""));
    m_lpTimeSpinCtrl = new wxSpinCtrl(m_lpToolBar, wxID_ANY, _(""), wxDefaultPosition, wxSize(40, 25), wxSP_ARROW_KEYS, 1, 60, 5);
    m_lpToolBar->AddControl(m_lpTimeSpinCtrl);
	m_lpToolBar->AddSeparator();
    m_lpToolBar->AddTool(ID_ANALYZE, _(""), wxBITMAP(ANALYZE_BMP), wxBITMAP(ANALYZE_DISABLE_BMP), wxITEM_CHECK, _(STR_SHOW_ANALYZE));
    m_lpToolBar->EnableTool(ID_ANALYZE, false);
	m_lpToolBar->AddSeparator();
    lpStaticText = new wxStaticText(m_lpToolBar, wxID_ANY, _(STR_INTERVAL));
    m_lpToolBar->AddControl(lpStaticText, _(""));
    m_lpIntervalSpinCtrl = new wxSpinCtrl(m_lpToolBar, wxID_ANY, _(""), wxDefaultPosition, wxSize(50, 25), wxSP_ARROW_KEYS, 10, 250, 50);
    m_lpToolBar->AddControl(m_lpIntervalSpinCtrl, _(""));
	m_lpToolBar->AddSeparator();
	lpStaticText = new wxStaticText(m_lpToolBar, wxID_ANY, _(STR_ROUTE_LENGTH));
	m_lpToolBar->AddControl(lpStaticText, _(""));
	m_lpAnalyzeSpinControl = new wxSpinCtrl(m_lpToolBar, wxID_ANY, _(""), wxDefaultPosition, wxSize(50, 25), wxSP_ARROW_KEYS, 2, 50, 16);//m_lpAnalyzeSlider = new wxSlider(m_lpToolBar, wxID_ANY, 16, 2, 50, wxDefaultPosition, wxSize(150, 25), wxSL_VALUE_LABEL);
	m_lpToolBar->AddControl(m_lpAnalyzeSpinControl, _(""));//m_lpToolBar->AddControl(m_lpAnalyzeSlider, _(""));
	m_lpToolBar->AddSeparator();
    m_lpToolBar->AddTool(ID_FINAL_SCORE, _(""), wxBITMAP(SCORE_BMP), wxBITMAP(SCORE_DISABLE_BMP), wxITEM_NORMAL, _(STR_RESULT));
    m_lpToolBar->EnableTool(ID_FINAL_SCORE, false);
    m_lpToolBar->Realize();
    SetToolBar(m_lpToolBar);
}

void CMainFrame::m_fnSetupStatusBar()
{
	m_lpStatusBar = new wxStatusBar(this);
	SetStatusBar(m_lpStatusBar);
	m_lpStatusBar->SetStatusText(_(STR_NO_ENGINE));
}

void CMainFrame::m_fnCreateCanvas()
{
    m_lpCanvas = new CCanvas(this);
    m_lpCanvas->m_GameStatusManager.m_lpToolBar = m_lpToolBar;
    m_lpCanvas->m_GameStatusManager.m_lpEditMenu = m_lpEditMenu;
    m_lpCanvas->m_iAnalyzeInterval = m_lpIntervalSpinCtrl->GetValue();
	m_lpCanvas->m_lpAnalyzeSpinCtrl = m_lpAnalyzeSpinControl;//m_lpCanvas->m_lpAnalyzeSlider = m_lpAnalyzeSlider;
	m_lpCanvas->m_GameStatusManager.m_lpStatusBar = m_lpStatusBar;
	m_lpCanvas->m_bmpOriginalBlackStone = wxBITMAP(BLACK_STONE_BMP);
	m_lpCanvas->m_bmpOriginalWhiteStone = wxBITMAP(WHITE_STONE_BMP);
	m_lpCanvas->m_bmpOriginalPass = wxBITMAP(PASS_BMP);
	m_lpCanvas->m_bmpOriginalResign = wxBITMAP(RESIGN_BMP);
	DragAcceptFiles(true);
}

void CMainFrame::m_fnPrepareEngine()
{
    std::ifstream ifs;
    char buffer[2048] = {'\0'};
    ifs.open("config.txt");
	ifs.getline(buffer, 2048);
    m_wxstrEnginePath = wxString(buffer);
	ifs.getline(buffer, 2048);
    m_wxstrWeightPath = wxString(buffer);
	ifs.getline(buffer, 2048);
	m_wxstrExtraPara = wxString(buffer);
    ifs.close();
    m_bPathChanged = false;
	m_bExtraParaChanged = false;
    m_ProcessExitType = PET_COLLAPSE;
    m_lpLZProcess = new CLZProcess(this, wxID_ANY);
}

CMainFrame::CMainFrame(const wxString &title, wxSize init_size = wxDefaultSize): wxFrame(0, wxID_ANY, title, wxDefaultPosition, init_size)//, m_Timer(this, wxID_ANY)
{
	m_fnSetupMenu();
	m_fnSetupToolBar();
	m_fnSetupStatusBar();
	m_fnCreateCanvas();
	m_fnPrepareEngine();
}

void CMainFrame::OnNew(wxCommandEvent &event)
{
    wxMessageDialog MD(this, _(STR_DISCARD_RECORD_INQUIRY), _(STR_TIP), wxOK|wxCANCEL);
    if ((m_lpCanvas->m_GameBoardManager.m_emBlankMove.depth == 0 && m_lpCanvas->m_GameBoardManager.m_iHandicapPutting == 0) || MD.ShowModal() == wxID_OK)
    {
        if (!(m_lpCanvas->m_GameBoardManager.m_emBlankMove.depth == 0 && m_lpCanvas->m_GameBoardManager.m_iHandicapPutting == 0))
        {
            m_lpCanvas->m_GameBoardManager.OnClearGameRecord();
			if (m_lpCanvas->m_GameStatusManager.m_esCurrentEngine == ES_OPENED)
			{
				m_lpCanvas->m_fnLZClearBoard();
				if (m_lpCanvas->m_GameStatusManager.m_fnAnalyzing())
				{
					m_lpCanvas->m_GameBoardManager.OnClearAnalyze();
					m_lpCanvas->m_fnLZInquireAnalyze();
				}
				m_lpCanvas->m_fnLZExecuteFirstInquire();
			}
        }
        Refresh();
    }
}


void CMainFrame::OnHandicap(wxCommandEvent &event)
{
	wxMessageDialog MD(this, _(STR_DISCARD_RECORD_INQUIRY), _(STR_TIP), wxOK | wxCANCEL);
	wxTextEntryDialog TED(this, _(STR_HANDICAP_NUM), _(STR_TIP), wxString::Format(wxString("%d"), m_lpCanvas->m_GameBoardManager.m_nHandicap));
	long nHandicap;
	if (m_lpCanvas->m_GameBoardManager.m_emBlankMove.depth == 0 && m_lpCanvas->m_GameBoardManager.m_iHandicapPutting == 0 || MD.ShowModal() == wxID_OK)
	{
		if (TED.ShowModal() == wxID_OK)
		{
			TED.GetValue().ToLong(&nHandicap);
			if (nHandicap > 1 && nHandicap <= 9)
			{
				if (!(m_lpCanvas->m_GameBoardManager.m_emBlankMove.depth == 0 && m_lpCanvas->m_GameBoardManager.m_iHandicapPutting == 0))
				{
					m_lpCanvas->m_GameBoardManager.OnClearGameRecord();
					if (m_lpCanvas->m_GameStatusManager.m_esCurrentEngine == ES_OPENED)
					{
						m_lpCanvas->m_fnLZClearBoard();
					}
				}
				if (nBoardSize != 19)
				{
					nBoardSize = 19;
					m_lpCanvas->m_GameBoardManager.m_fnChangeSize();
					m_lpCanvas->m_fnSetSize();
				}
				m_lpCanvas->m_GameBoardManager.m_nHandicap = int(nHandicap);
				m_lpCanvas->m_GameBoardManager.m_iHandicapPutting = 0;
				if (m_lpCanvas->m_GameStatusManager.m_esCurrentEngine == ES_OPENED)
				{
					m_lpCanvas->m_GameBoardManager.m_scTurnColor = SC_WHITE;
					m_lpCanvas->m_fnLZSetHandicap();
					if (m_lpCanvas->m_GameStatusManager.m_fnAnalyzing())
					{
						m_lpCanvas->m_GameBoardManager.OnClearAnalyze();
						m_lpCanvas->m_fnLZInquireAnalyze();
					}
					m_lpCanvas->m_fnLZExecuteFirstInquire();
				}
				else
				{
					m_lpCanvas->m_GameBoardManager.OnSetHandicap();
				}
				Refresh();
			}
		}
	}
}

void CMainFrame::m_fnOpenSGF(char *lpstrFile)
{
	std::ifstream ifs;
	ifs.open(lpstrFile);
    m_lpCanvas->m_GameBoardManager.OnReadSGF(ifs);
    ifs.close();
}

void CMainFrame::OnOpen(wxCommandEvent &event)
{
    wxFileDialog OpenFileDialog(this, _(""), _(""), _(""), _("Smart Game File (*.sgf)|*.sgf"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    wxMessageDialog MD(this, _(STR_DISCARD_RECORD_INQUIRY), _(STR_TIP), wxOK|wxCANCEL);
    std::ifstream ifs;
    if (OpenFileDialog.ShowModal() == wxID_OK)
    {
        if ((m_lpCanvas->m_GameBoardManager.m_emBlankMove.depth == 0 && m_lpCanvas->m_GameBoardManager.m_iHandicapPutting == 0) || MD.ShowModal() == wxID_OK)
        {
            if (!(m_lpCanvas->m_GameBoardManager.m_emBlankMove.depth == 0 && m_lpCanvas->m_GameBoardManager.m_iHandicapPutting == 0))
            {
				m_lpCanvas->m_GameBoardManager.OnClearGameRecord();
                if (m_lpCanvas->m_GameStatusManager.m_esCurrentEngine == ES_OPENED)
                {
					m_lpCanvas->m_fnLZClearBoard();
                }
            }
			m_fnOpenSGF(OpenFileDialog.GetPath().char_str());
            Refresh();
            if (m_lpCanvas->m_GameStatusManager.m_esCurrentEngine == ES_OPENED)
            {
				if (m_lpCanvas->m_GameBoardManager.m_nHandicap != 0)
				{
					m_lpCanvas->m_GameBoardManager.m_iHandicapPutting = 0;
					m_lpCanvas->m_fnLZSetHandicap();
				}
				if (m_lpCanvas->m_GameStatusManager.m_fnAnalyzing())
				{
					m_lpCanvas->m_GameBoardManager.OnClearAnalyze();
					m_lpCanvas->m_fnLZInquireAnalyze();
				}
				m_lpCanvas->m_fnLZExecuteFirstInquire();
            }
        }
    }
}

void CMainFrame::OnDropFile(wxDropFilesEvent &event)
{
    wxMessageDialog MD(this, _(STR_DISCARD_RECORD_INQUIRY), _(STR_TIP), wxOK|wxCANCEL);
    std::ifstream ifs;
	wxString wxstrFile;
	wxstrFile = *(event.GetFiles());
	if (wxstrFile.length() > 4 && strcmp(strrchr((char*)(wxstrFile.char_str()), '.'), ".sgf") == 0)
	{
		if ((m_lpCanvas->m_GameBoardManager.m_emBlankMove.depth == 0 && m_lpCanvas->m_GameBoardManager.m_iHandicapPutting == 0) || MD.ShowModal() == wxID_OK)
		{
			if (!(m_lpCanvas->m_GameBoardManager.m_emBlankMove.depth == 0 && m_lpCanvas->m_GameBoardManager.m_iHandicapPutting == 0))
			{
				m_lpCanvas->m_GameBoardManager.OnClearGameRecord();
				if (m_lpCanvas->m_GameStatusManager.m_esCurrentEngine == ES_OPENED)
				{
					m_lpCanvas->m_fnLZClearBoard();
				}
			}
			m_fnOpenSGF(wxstrFile.char_str());
			Refresh();
			if (m_lpCanvas->m_GameStatusManager.m_esCurrentEngine == ES_OPENED)
			{
				if (m_lpCanvas->m_GameBoardManager.m_nHandicap != 0)
				{
					m_lpCanvas->m_GameBoardManager.m_iHandicapPutting = 0;
					m_lpCanvas->m_fnLZSetHandicap();
				}
				if (m_lpCanvas->m_GameStatusManager.m_fnAnalyzing())
				{
					m_lpCanvas->m_GameBoardManager.OnClearAnalyze();
					m_lpCanvas->m_fnLZInquireAnalyze();
				}
				m_lpCanvas->m_fnLZExecuteFirstInquire();
			}
		}
	}
}

void CMainFrame::OnSave(wxCommandEvent &event)
{
    wxFileDialog SaveFileDialog(this, _(""), _(""), _(""), _("Smart Game File (*.sgf)|*.sgf"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
	std::ofstream ofs;
    if (SaveFileDialog.ShowModal() == wxID_OK)
    {
		ofs.open(SaveFileDialog.GetPath().char_str());
		m_lpCanvas->m_GameBoardManager.OnWriteSGF(ofs);
		ofs.close();
    }
}

void CMainFrame::OnShowStep(wxCommandEvent &event)
{
    m_lpCanvas->m_bShowStep = !m_lpCanvas->m_bShowStep;
    Refresh();
}

void CMainFrame::OnSetGameboardColor(wxCommandEvent &event)
{
	wxColourData wxclrdata;
	wxclrdata.SetColour(m_lpCanvas->m_brGameBoard.GetColour());
	wxColourDialog CD(this, &wxclrdata);
	if (CD.ShowModal() == wxID_OK)
	{
		wxclrdata = CD.GetColourData();
		m_lpCanvas->m_brGameBoard.SetColour(wxclrdata.GetColour());
		Refresh();
	}
}


void CMainFrame::OnHideCoord(wxCommandEvent &event)
{
	m_lpCanvas->m_ctBoardTick = CT_NULL;
	Refresh();
}
void CMainFrame::OnSetNetCoord(wxCommandEvent &event)
{
	m_lpCanvas->m_ctBoardTick = CT_NET;
	Refresh();
}
void CMainFrame::OnSetNumCoord(wxCommandEvent &event)
{
	m_lpCanvas->m_ctBoardTick = CT_NUM;
	Refresh();
}
void CMainFrame::OnSetSGFCoord(wxCommandEvent &event)
{
	m_lpCanvas->m_ctBoardTick = CT_SGF;
	Refresh();
}
void CMainFrame::OnSetGTPCoord(wxCommandEvent &event)
{
	m_lpCanvas->m_ctBoardTick = CT_GTP;
	Refresh();
}

void CMainFrame::OnBackward(wxCommandEvent &event)
{
	if (m_lpCanvas->m_GameStatusManager.m_fnBothAuthorized() && m_lpCanvas->m_GameBoardManager.m_lpemCurrentMove->parent != NULL)
	{
		if (m_lpCanvas->m_GameStatusManager.m_esCurrentEngine == ES_OPENED)
		{
			if (m_lpCanvas->m_GameStatusManager.m_fnAnalyzing())
			{
				m_lpCanvas->m_GameBoardManager.OnClearAnalyze();
				m_lpCanvas->m_fnLZBackward();
				m_lpCanvas->m_fnLZInquireAnalyze();
			}
			else
			{
				m_lpCanvas->m_fnLZBackward();
			}
			m_lpCanvas->m_GameBoardManager.OnBackMove();
			Refresh();
			m_lpCanvas->m_fnLZExecuteFirstInquire();
		}
		else
		{
			m_lpCanvas->m_GameBoardManager.OnBackMove();
			Refresh();
		}
	}
}

void CMainFrame::OnForward(wxCommandEvent &event)
{
	if (m_lpCanvas->m_GameStatusManager.m_fnBothAuthorized() && m_lpCanvas->m_GameBoardManager.m_lpemCurrentMove->child != NULL)
	{
		if (m_lpCanvas->m_GameStatusManager.m_esCurrentEngine == ES_OPENED)
		{
			if (m_lpCanvas->m_GameStatusManager.m_fnAnalyzing())
			{
				m_lpCanvas->m_GameBoardManager.OnClearAnalyze();
				m_lpCanvas->m_fnLZForward();
				m_lpCanvas->m_fnLZInquireAnalyze();
			}
			else
			{
				m_lpCanvas->m_fnLZForward();
			}
			m_lpCanvas->m_GameBoardManager.OnRedoMove();
			Refresh();
			m_lpCanvas->m_fnLZExecuteFirstInquire();
		}
		else
		{
			m_lpCanvas->m_GameBoardManager.OnRedoMove();
			Refresh();
		}
	}
}

void CMainFrame::OnSelectEngine(wxCommandEvent &event)
{
    wxFileDialog OpenFileDialog(this, _(""), _(""), m_wxstrEnginePath, _("Leela Zero Engine (*.exe)|*.exe"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (OpenFileDialog.ShowModal() == wxID_OK)
    {
        wxString wxstrOldPath = m_wxstrEnginePath;
        m_wxstrEnginePath = OpenFileDialog.GetPath();
        if (m_wxstrEnginePath.compare(wxstrOldPath) != 0)
        {
            m_bPathChanged = true;
        }
    }
}

void CMainFrame::OnSelectWeight(wxCommandEvent &event)
{
    wxFileDialog OpenFileDialog(this, _(""), _(""), m_wxstrWeightPath, _("Weight File(*.gz)|*.gz|Network File(*.txt)|*.txt"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    if (OpenFileDialog.ShowModal() == wxID_OK)
    {
        wxString wxstrOldPath = m_wxstrWeightPath;
        m_wxstrWeightPath = OpenFileDialog.GetPath();
        if (m_wxstrWeightPath.compare(wxstrOldPath) != 0)
        {
            m_bPathChanged = true;
        }
    }
}

void CMainFrame::OnLeelaZero(wxCommandEvent &event)
{
    wxMessageDialog MD(this, _(STR_CLOSE_ENGINE_INQUIRY), _(STR_TIP), wxOK | wxCANCEL);
    wxFileDialog OpenEigineDialog(this, _(""), _(""), m_wxstrEnginePath, _("Leela Zero Engine (*.exe)|*.exe"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    wxFileDialog OpenWeightDialog(this, _(""), _(""), m_wxstrWeightPath, _("Weight File(*.gz)|*.gz|Network File(*.txt)|*.txt"), wxFD_OPEN | wxFD_FILE_MUST_EXIST);
    bool bApplicable;
	InquireInfo iiInquire;
    if (m_lpCanvas->m_GameStatusManager.m_esCurrentEngine == ES_OPENED)
    {
        if (MD.ShowModal() == wxID_OK)
        {
			m_lpCanvas->m_GameStatusManager.m_fnTryToCloseEngine();
			m_lpCanvas->m_GameBoardManager.OnClearAnalyze();
            m_ProcessExitType = PET_STOP;
			iiInquire.itInquireType = IT_QUIT;
			if (m_lpCanvas->m_quiiLZInquireQueue.empty())
			{
				m_lpCanvas->m_quiiLZInquireQueue.push(iiInquire);
			}
			else
			{
				m_lpCanvas->m_quiiLZInquireQueue.front() = iiInquire;
			}
			m_lpCanvas->m_fnLZApplyInquire(&iiInquire);
        }
    }
    else if (nBoardSize == STANDARD_BOARD_SIZE)
    {
        bApplicable = true;
        if (m_wxstrEnginePath.length() == 0)
        {
            if (OpenEigineDialog.ShowModal() == wxID_OK)
            {
                wxString wxstrOldPath = m_wxstrEnginePath;
                m_wxstrEnginePath = OpenEigineDialog.GetPath();
                if (m_wxstrEnginePath.compare(wxstrOldPath) != 0)
                {
                    m_bPathChanged = true;
                }
                bApplicable = true;
            }
            else
            {
                bApplicable = false;
            }
        }
        if (bApplicable)
        {
            if (m_wxstrWeightPath.length() == 0)
            {
                if (OpenWeightDialog.ShowModal() == wxID_OK)
                {
                    wxString wxstrOldPath = m_wxstrWeightPath;
                    m_wxstrWeightPath = OpenWeightDialog.GetPath();
                    if (m_wxstrWeightPath.compare(wxstrOldPath) != 0)
                    {
                        m_bPathChanged = true;
                    }
                    bApplicable = true;
                }
                else
                {
                    bApplicable = false;
                }
            }
            if(bApplicable)
            {
				m_lpCanvas->m_GameStatusManager.m_fnTryToOpenEngine();
                if(m_fnOpenLZProcess() == 0)
                {
					m_lpCanvas->m_GameStatusManager.m_fnEngineConfirmed();
					m_lpCanvas->m_GameStatusManager.m_fnTryToCloseEngine();
					m_lpCanvas->m_GameStatusManager.m_fnEngineClosed();
                }
            }
        }
    }
}


void CMainFrame::OnScore(wxCommandEvent &event)
{
    m_lpCanvas->m_fnLZInquireResult();
	m_lpCanvas->m_fnLZExecuteFirstInquire();
}

void CMainFrame::OnExtraPara(wxCommandEvent &event)
{
	wxString wxstrOldExtraPara;
	wxTextEntryDialog TED(this, _(STR_EXTRA_PARAMETERS), _(STR_TIP), m_wxstrExtraPara, wxOK | wxCANCEL);
    if (TED.ShowModal() == wxID_OK)
    {
		wxstrOldExtraPara = m_wxstrExtraPara;
		m_wxstrExtraPara = TED.GetValue();
		if (m_wxstrExtraPara.compare(wxstrOldExtraPara) != 0)
		{
			m_bExtraParaChanged = true;
		}
    }
}

void CMainFrame::OnBoardSize(wxCommandEvent &event)
{
	wxTextEntryDialog TED(this, _(STR_BOARD_SIZE), _(STR_TIP), wxString::Format(wxString("%d"), nBoardSize), wxOK | wxCANCEL);
	wxMessageDialog MD(this, _(STR_DISCARD_RECORD_INQUIRY), _(STR_TIP), wxOK | wxCANCEL);
	long nNewSize;
	if ((m_lpCanvas->m_GameStatusManager.m_esCurrentEngine == ES_CLOSED) && TED.ShowModal() == wxID_OK)
	{
		TED.GetValue().ToLong(&nNewSize);
		if (nNewSize > 8 && nNewSize < 26 && (int(nNewSize) != nBoardSize) && (m_lpCanvas->m_GameBoardManager.m_emBlankMove.depth == 0 || MD.ShowModal() == wxID_OK))
		{
			if (m_lpCanvas->m_GameBoardManager.m_emBlankMove.depth != 0)
			{
				m_lpCanvas->m_GameBoardManager.OnClearGameRecord();
			}
			if (m_lpCanvas->m_GameStatusManager.m_esCurrentEngine == ES_OPENED)
			{
				m_lpCanvas->m_fnLZChangeBoardSize(nBoardSize);
				m_lpCanvas->m_fnLZExecuteFirstInquire();
			}
			else
			{
				nBoardSize = int(nNewSize);
				m_lpCanvas->m_GameBoardManager.m_fnChangeSize();
				m_lpCanvas->m_fnSetSize();
				m_lpCanvas->Refresh();
			}
		}
	}
}

void CMainFrame::OnBlackDog(wxCommandEvent &event)
{
    bool bBlackDog;
    wxMessageDialog MD(this, _(STR_ADD_BRANCH_INQUIRY), _(STR_TIP), wxOK | wxCANCEL);
    bBlackDog = m_lpToolBar->GetToolState(ID_BLACK_DOG);
    if (bBlackDog)
    {
		if (m_lpCanvas->m_GameBoardManager.m_lpemCurrentMove->child == NULL || MD.ShowModal() == wxID_OK)
        {
			m_lpCanvas->m_GameStatusManager.m_fnSetBlackDog();
			if (m_lpCanvas->m_iThinkingTime != m_lpTimeSpinCtrl->GetValue())
			{
				m_lpCanvas->m_iThinkingTime = m_lpTimeSpinCtrl->GetValue();
				m_lpCanvas->m_fnLZSetThinkingTime();
			}
            if (m_lpCanvas->m_GameStatusManager.m_fnInquireAI(m_lpCanvas->m_GameBoardManager.m_scTurnColor))
            {
                m_lpCanvas->m_fnLZInquireMove(m_lpCanvas->m_GameBoardManager.m_scTurnColor);
            }
			m_lpCanvas->m_fnLZExecuteFirstInquire();
        }
        else
        {
            m_lpToolBar->ToggleTool(ID_BLACK_DOG, false);
        }
    }
	else
	{
		m_lpCanvas->m_GameStatusManager.m_fnSetBlackDog();
	}
}

void CMainFrame::OnWhiteDog(wxCommandEvent &event)
{
	bool bWhiteDog;
	wxMessageDialog MD(this, _(STR_ADD_BRANCH_INQUIRY), _(STR_TIP), wxOK | wxCANCEL);
	bWhiteDog = m_lpToolBar->GetToolState(ID_WHITE_DOG);
	if (bWhiteDog)
	{
		if (m_lpCanvas->m_GameBoardManager.m_lpemCurrentMove->child == NULL || MD.ShowModal() == wxID_OK)
		{
			m_lpCanvas->m_GameStatusManager.m_fnSetWhiteDog();
			if (m_lpCanvas->m_iThinkingTime != m_lpTimeSpinCtrl->GetValue())
			{
				m_lpCanvas->m_iThinkingTime = m_lpTimeSpinCtrl->GetValue();
				m_lpCanvas->m_fnLZSetThinkingTime();
			}
			if (m_lpCanvas->m_GameStatusManager.m_fnInquireAI(m_lpCanvas->m_GameBoardManager.m_scTurnColor))
			{
				m_lpCanvas->m_fnLZInquireMove(m_lpCanvas->m_GameBoardManager.m_scTurnColor);
			}
				m_lpCanvas->m_fnLZExecuteFirstInquire();
		}
		else
		{
			m_lpToolBar->ToggleTool(ID_WHITE_DOG, false);
		}
	}
	else
	{
		m_lpCanvas->m_GameStatusManager.m_fnSetWhiteDog();
	}
}

void CMainFrame::OnAnalyze(wxCommandEvent &event)
{
	InquireInfo iiInquire;
	iiInquire.itInquireType = IT_INTERRUPT;
	m_lpCanvas->m_GameStatusManager.m_fnSetAnalyze();
    if (m_lpToolBar->GetToolState(ID_ANALYZE))
    {
		m_lpCanvas->m_iAnalyzeInterval = m_lpIntervalSpinCtrl->GetValue();
		m_lpCanvas->m_GameStatusManager.m_fnSetAnalyze();
		m_lpCanvas->m_fnLZInquireAnalyze();
		m_lpCanvas->m_fnLZExecuteFirstInquire();
    }
    else
    {
        m_lpCanvas->m_fnLZApplyInquire(&iiInquire);
		m_lpCanvas->m_GameBoardManager.OnClearAnalyze();
		m_lpCanvas->Refresh();
    }
}

void CMainFrame::OnManual(wxCommandEvent &event)
{
	CManualDialog MD(this, _(STR_MANUAL), _(STR_DIRECTION), _(STR_CLOSE));
	MD.ShowModal();
}

void CMainFrame::OnAbout(wxCommandEvent &event)
{
	wxMessageDialog MD(this, _(STR_VERSION), _(STR_ABOUT));
	MD.ShowModal();
}

long CMainFrame::m_fnOpenLZProcess()
{
    long lProcessId;
    wxString wxstrCommand;
    if (m_wxstrExtraPara.length() > 0)
    {
        wxstrCommand = m_wxstrEnginePath + wxString(" -g -q -w ") + m_wxstrWeightPath + wxString(" ") + m_wxstrExtraPara;
    }
    else
    {
        wxstrCommand = m_wxstrEnginePath + wxString(" -g -q -w ") + m_wxstrWeightPath;
    }
    m_lpLZProcess->Redirect();
    lProcessId = wxExecute(wxstrCommand, wxEXEC_ASYNC, m_lpLZProcess);
    if (lProcessId > 0)
    {
        m_lpLZReceiver = new CLZReceiver();
        m_lpLZReceiver->m_lpCanvas = m_lpCanvas;
        m_lpLZReceiver->m_lpInputStream = m_lpLZProcess->GetInputStream();
        m_lpLZReceiver->Run();
        m_lpCanvas->m_lpOutputStream = m_lpLZProcess->GetOutputStream();
		m_lpCanvas->m_fnLZInquireName();
		m_lpCanvas->m_fnLZExecuteFirstInquire();
        m_lpCanvas->m_iThinkingTime = 0;
    }
    return lProcessId;
}

void CMainFrame::OnLZProcessExit(wxProcessEvent &event)
{
    m_lpCanvas->m_lpOutputStream = 0;
	m_lpCanvas->m_GameStatusManager.m_fnEngineClosed();
	while (!m_lpCanvas->m_quiiLZInquireQueue.empty())
	{
		m_lpCanvas->m_quiiLZInquireQueue.pop();
	}
	if (m_lpCanvas->m_GameStatusManager.m_esCurrentEngine == ES_WAITING_OPEN)
	{
		m_ProcessExitType = PET_FAILURE;
	}
    switch (m_ProcessExitType)
    {
	case PET_FAILURE:
		m_lpCanvas->m_GameStatusManager.m_fnEngineConfirmed();
		m_lpCanvas->m_GameStatusManager.m_fnTryToCloseEngine();
		m_lpCanvas->m_GameStatusManager.m_fnEngineClosed();
        delete m_lpLZProcess;
        m_lpLZProcess = new CLZProcess(this, wxID_ANY);
        m_ProcessExitType = PET_COLLAPSE;
		break;
    case PET_STOP:
        m_lpLZReceiver->m_bKeepLoop = false;
        delete m_lpLZProcess;
        m_lpLZProcess = new CLZProcess(this, wxID_ANY);
        m_ProcessExitType = PET_COLLAPSE;
		m_lpCanvas->m_GameStatusManager.m_fnEngineClosed();
        break;
    case PET_COLLAPSE:
        m_lpLZReceiver->m_bKeepLoop = false;
		m_lpCanvas->m_GameStatusManager.m_fnTryToCloseEngine();
		m_lpCanvas->m_GameStatusManager.m_fnEngineClosed();
		m_lpCanvas->m_GameStatusManager.m_fnTryToOpenEngine();
		m_lpStatusBar->SetStatusText(_(STR_RESTART_ENGINE));
        delete m_lpLZProcess;
        m_lpLZProcess = new CLZProcess(this, wxID_ANY);
        m_fnOpenLZProcess();
        break;
    case PET_QUIT:
        delete m_lpLZProcess;
        Destroy();
        break;
    }
}

void CMainFrame::OnExit(wxCommandEvent &event)
{
	std::ifstream ifs;
    std::ofstream ofs;
	char buffer[1024];
	InquireInfo iiInquire;
    if (m_bPathChanged)
    {
        wxMessageDialog MD(this, _(STR_CHANGE_PATH), _(STR_TIP), wxOK|wxCANCEL);
        if (MD.ShowModal()== wxID_OK)
        {
            ofs.open("config.txt");
            ofs << m_wxstrEnginePath.char_str() << '\n' << m_wxstrWeightPath.char_str() << '\n';
            ofs.close();
        }
    }
	if (m_bExtraParaChanged)
	{
		wxMessageDialog MD(this, _(STR_CHANGE_EXTRA_PARA), _(STR_TIP), wxOK | wxCANCEL);
		if (MD.ShowModal() == wxID_OK)
		{
			ifs.open("config.txt");
			ifs >> buffer;
			m_wxstrEnginePath = wxString(buffer);
			ifs >> buffer;
			m_wxstrWeightPath = wxString(buffer);
			ifs.close();
			ofs.open("config.txt");
            ofs << m_wxstrEnginePath.char_str() << '\n' << m_wxstrWeightPath.char_str() << '\n';
			ofs << m_wxstrExtraPara.char_str() << '\n';
			ofs.close();
		}
	}
    if (m_lpCanvas->m_GameStatusManager.m_esCurrentEngine == ES_OPENED)
    {
        m_lpCanvas->m_GameStatusManager.m_fnTryToCloseEngine();
        m_ProcessExitType = PET_QUIT;
		iiInquire.itInquireType = IT_QUIT;
		if (m_lpCanvas->m_quiiLZInquireQueue.empty())
		{
			m_lpCanvas->m_quiiLZInquireQueue.push(iiInquire);
		}
		else
		{
			m_lpCanvas->m_quiiLZInquireQueue.front() = iiInquire;
		}
		m_lpCanvas->m_fnLZApplyInquire(&iiInquire);
    }
    else
    {
        delete m_lpLZProcess;
        Destroy();
    }
}

void CMainFrame::OnClose(wxCloseEvent &event)
{
	std::ifstream ifs;
	std::ofstream ofs;
	char buffer[1024];
	InquireInfo iiInquire;
    if (m_bPathChanged)
    {
        wxMessageDialog MD(this, _(STR_CHANGE_PATH), _(STR_TIP), wxOK|wxCANCEL);
        if (MD.ShowModal()== wxID_OK)
        {
            ofs.open("config.txt");
            ofs << m_wxstrEnginePath.char_str() << '\n' << m_wxstrWeightPath.char_str() << '\n';
            ofs.close();
        }
    }
	if (m_bExtraParaChanged)
	{
		wxMessageDialog MD(this, _(STR_CHANGE_EXTRA_PARA), _(STR_TIP), wxOK | wxCANCEL);
		if (MD.ShowModal() == wxID_OK)
		{
			ifs.open("config.txt");
			ifs >> buffer;
			m_wxstrEnginePath = wxString(buffer);
			ifs >> buffer;
			m_wxstrWeightPath = wxString(buffer);
			ifs.close();
			ofs.open("config.txt");
			ofs << m_wxstrEnginePath.char_str() << '\n' << m_wxstrWeightPath.char_str() << '\n';
			ofs << m_wxstrExtraPara.char_str() << '\n';
			ofs.close();
		}
	}
    if (m_lpCanvas->m_GameStatusManager.m_esCurrentEngine == ES_OPENED)
    {
		m_lpCanvas->m_GameStatusManager.m_fnTryToCloseEngine();
        m_ProcessExitType = PET_QUIT;
		iiInquire.itInquireType = IT_QUIT;
		if (m_lpCanvas->m_quiiLZInquireQueue.empty())
		{
			m_lpCanvas->m_quiiLZInquireQueue.push(iiInquire);
		}
		else
		{
			m_lpCanvas->m_quiiLZInquireQueue.front() = iiInquire;
		}
		m_lpCanvas->m_fnLZApplyInquire(&iiInquire);
    }
    else
    {
        delete m_lpLZProcess;
        Destroy();
    }
}


BEGIN_EVENT_TABLE(CMainFrame, wxFrame)
EVT_MENU(wxID_NEW, CMainFrame::OnNew)
EVT_TOOL(wxID_NEW, CMainFrame::OnNew)
EVT_MENU(ID_HANDICAP, CMainFrame::OnHandicap)
EVT_MENU(wxID_OPEN, CMainFrame::OnOpen)
EVT_TOOL(wxID_OPEN, CMainFrame::OnOpen)
EVT_DROP_FILES(CMainFrame::OnDropFile)
EVT_MENU(wxID_SAVE, CMainFrame::OnSave)
EVT_TOOL(wxID_SAVE, CMainFrame::OnSave)
EVT_TOOL(ID_SHOW_STEP, CMainFrame::OnShowStep)
EVT_MENU(ID_COORD_NULL, CMainFrame::OnHideCoord)
EVT_MENU(ID_COORD_NET, CMainFrame::OnSetNetCoord)
EVT_MENU(ID_COORD_NUM, CMainFrame::OnSetNumCoord)
EVT_MENU(ID_COORD_SGF, CMainFrame::OnSetSGFCoord)
EVT_MENU(ID_COORD_GTP, CMainFrame::OnSetGTPCoord)
EVT_TOOL(wxID_SELECT_COLOR, CMainFrame::OnSetGameboardColor)
EVT_MENU(ID_SELECT_ENGINE, CMainFrame::OnSelectEngine)
EVT_MENU(ID_SELECT_WEIGHT, CMainFrame::OnSelectWeight)
EVT_MENU(ID_LEELA_ZERO, CMainFrame::OnLeelaZero)
EVT_MENU(ID_EXTRA_PARA, CMainFrame::OnExtraPara)
EVT_MENU(ID_BOARD_SIZE, CMainFrame::OnBoardSize)
EVT_MENU(wxID_UNDO, CMainFrame::OnBackward)
EVT_TOOL(wxID_UNDO, CMainFrame::OnBackward)
EVT_MENU(wxID_REDO, CMainFrame::OnForward)
EVT_TOOL(wxID_REDO, CMainFrame::OnForward)
EVT_MENU(ID_FINAL_SCORE, CMainFrame::OnScore)
EVT_TOOL(ID_FINAL_SCORE, CMainFrame::OnScore)
EVT_TOOL(ID_BLACK_DOG, CMainFrame::OnBlackDog)
EVT_TOOL(ID_WHITE_DOG, CMainFrame::OnWhiteDog)
EVT_TOOL(ID_ANALYZE, CMainFrame::OnAnalyze)
EVT_MENU(wxID_HELP_CONTEXT, CMainFrame::OnManual)
EVT_MENU(wxID_ABOUT, CMainFrame::OnAbout)
EVT_END_PROCESS(wxID_ANY, CMainFrame::OnLZProcessExit)
EVT_MENU(wxID_EXIT, CMainFrame::OnExit)
EVT_CLOSE(CMainFrame::OnClose)
END_EVENT_TABLE()
