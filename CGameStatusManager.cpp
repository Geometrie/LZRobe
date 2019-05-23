#include "CGameStatusManager.h"

CGameStatusManager::CGameStatusManager()
{
	m_esCurrentEngine = ES_CLOSED;
}

void CGameStatusManager::m_fnTryToOpenEngine()
{
	if (m_esCurrentEngine == ES_CLOSED)
	{
		m_lpEditMenu->Enable(ID_LEELA_ZERO, false);
		m_lpToolBar->EnableTool(ID_LEELA_ZERO, false);
		m_lpStatusBar->SetStatusText(STR_ENGINE_OPENING);
		m_esCurrentEngine = ES_WAITING_OPEN;
	}
}

void CGameStatusManager::m_fnEngineConfirmed()
{
	if (m_esCurrentEngine == ES_WAITING_OPEN)
	{
		m_lpEditMenu->SetLabel(ID_LEELA_ZERO, _(STR_CLOSE_ENGINE));
		m_lpToolBar->SetToolNormalBitmap(ID_LEELA_ZERO, wxBITMAP(STOP_BMP));
		m_lpToolBar->SetToolDisabledBitmap(ID_LEELA_ZERO, wxBITMAP(STOP_DISABLE_BMP));
		m_lpToolBar->SetToolShortHelp(ID_LEELA_ZERO, _(STR_CLOSE_ENGINE));
		m_lpEditMenu->Enable(ID_LEELA_ZERO, true);
		m_lpToolBar->EnableTool(ID_LEELA_ZERO, true);
		m_lpToolBar->EnableTool(ID_BLACK_DOG, true);
		m_lpToolBar->EnableTool(ID_WHITE_DOG, true);
		m_lpToolBar->EnableTool(ID_ANALYZE, true);
		//m_lpToolBar->EnableTool(ID_FINAL_SCORE, true);
		m_lpStatusBar->SetStatusText(m_wxstrEngineName + wxString(STR_ENGINE_AVAILABLE));
		m_esCurrentEngine = ES_OPENED;
	}
}

void CGameStatusManager::m_fnTryToCloseEngine()
{
	if (m_esCurrentEngine == ES_OPENED)
	{
		if (m_lpToolBar->GetToolState(ID_BLACK_DOG) || m_lpToolBar->GetToolState(ID_WHITE_DOG))
		{
			m_lpEditMenu->Enable(wxID_UNDO, true);
			m_lpEditMenu->Enable(wxID_REDO, true);
			m_lpToolBar->EnableTool(wxID_UNDO, true);
			m_lpToolBar->EnableTool(wxID_REDO, true);
		}
		if (m_lpToolBar->GetToolState(ID_BLACK_DOG))
		{
			m_lpToolBar->ToggleTool(ID_BLACK_DOG, false);
		}
		if (m_lpToolBar->GetToolState(ID_WHITE_DOG))
		{
			m_lpToolBar->ToggleTool(ID_WHITE_DOG, false);
		}
		if (m_lpToolBar->GetToolState(ID_ANALYZE))
		{
			m_lpToolBar->ToggleTool(ID_ANALYZE, false);
		}
		m_lpToolBar->EnableTool(ID_BLACK_DOG, false);
		m_lpToolBar->EnableTool(ID_WHITE_DOG, false);
		m_lpToolBar->EnableTool(ID_ANALYZE, false);
		//m_lpToolBar->EnableTool(ID_FINAL_SCORE, false);
		m_lpStatusBar->SetStatusText(STR_ENGINE_CLOSING);
		m_esCurrentEngine = ES_WAITING_CLOSE;
	}
}

void CGameStatusManager::m_fnEngineClosed()
{
	if (m_esCurrentEngine == ES_WAITING_CLOSE)
	{
		m_lpEditMenu->SetLabel(ID_LEELA_ZERO, _(STR_RUN_ENGINE));
		m_lpToolBar->SetToolNormalBitmap(ID_LEELA_ZERO, wxBITMAP(RUN_BMP));
		m_lpToolBar->SetToolDisabledBitmap(ID_LEELA_ZERO, wxBITMAP(RUN_DISABLE_BMP));
		m_lpToolBar->SetToolShortHelp(ID_LEELA_ZERO, _(STR_RUN_ENGINE));
		m_lpEditMenu->Enable(ID_LEELA_ZERO, true);
		m_lpToolBar->EnableTool(ID_LEELA_ZERO, true);
		m_lpStatusBar->SetStatusText(_(STR_NO_ENGINE));
		m_esCurrentEngine = ES_CLOSED;
	}
}

void CGameStatusManager::m_fnSetBlackDog()
{
	if (m_esCurrentEngine == ES_OPENED)
	{
		if (m_lpToolBar->GetToolState(ID_WHITE_DOG))
		{
			if (m_lpToolBar->GetToolState(ID_BLACK_DOG))
			{
				m_lpStatusBar->SetStatusText(STR_SELFPLAY);
			}
			else
			{
				m_lpStatusBar->SetStatusText(STR_WHITE_DOG);
			}
		}
		else
		{
			if (m_lpToolBar->GetToolState(ID_BLACK_DOG))
			{
				m_lpEditMenu->Enable(wxID_UNDO, false);
				m_lpEditMenu->Enable(wxID_REDO, false);
				m_lpToolBar->EnableTool(wxID_UNDO, false);
				m_lpToolBar->EnableTool(wxID_REDO, false);
				if (m_lpToolBar->GetToolState(ID_ANALYZE))
				{
					m_lpToolBar->ToggleTool(ID_ANALYZE, false);
				}
				m_lpStatusBar->SetStatusText(STR_BLACK_DOG);
			}
			else
			{
				m_lpEditMenu->Enable(wxID_UNDO, true);
				m_lpEditMenu->Enable(wxID_REDO, true);
				m_lpToolBar->EnableTool(wxID_UNDO, true);
				m_lpToolBar->EnableTool(wxID_REDO, true);
				m_lpStatusBar->SetStatusText(STR_ENGINE_AVAILABLE);
			}
		}
	}
}

void CGameStatusManager::m_fnSetWhiteDog()
{
	if (m_esCurrentEngine == ES_OPENED)
	{
		if (m_lpToolBar->GetToolState(ID_BLACK_DOG))
		{
			if (m_lpToolBar->GetToolState(ID_WHITE_DOG))
			{
				m_lpStatusBar->SetStatusText(STR_SELFPLAY);
			}
			else
			{
				m_lpStatusBar->SetStatusText(STR_BLACK_DOG);
			}
		}
		else
		{
			if (m_lpToolBar->GetToolState(ID_WHITE_DOG))
			{
				m_lpEditMenu->Enable(wxID_UNDO, false);
				m_lpEditMenu->Enable(wxID_REDO, false);
				m_lpToolBar->EnableTool(wxID_UNDO, false);
				m_lpToolBar->EnableTool(wxID_REDO, false);
				if (m_lpToolBar->GetToolState(ID_ANALYZE))
				{
					m_lpToolBar->ToggleTool(ID_ANALYZE, false);
				}
				m_lpStatusBar->SetStatusText(STR_WHITE_DOG);
			}
			else
			{
				m_lpEditMenu->Enable(wxID_UNDO, true);
				m_lpEditMenu->Enable(wxID_REDO, true);
				m_lpToolBar->EnableTool(wxID_UNDO, true);
				m_lpToolBar->EnableTool(wxID_REDO, true);
				m_lpStatusBar->SetStatusText(STR_ENGINE_AVAILABLE);
			}
		}
	}
}


void CGameStatusManager::m_fnSetAnalyze()
{
	if (m_esCurrentEngine == ES_OPENED)
	{
		if (m_lpToolBar->GetToolState(ID_ANALYZE))
		{
			if (m_lpToolBar->GetToolState(ID_BLACK_DOG) || m_lpToolBar->GetToolState(ID_WHITE_DOG))
			{
				m_lpEditMenu->Enable(wxID_UNDO, true);
				m_lpEditMenu->Enable(wxID_REDO, true);
				m_lpToolBar->EnableTool(wxID_UNDO, true);
				m_lpToolBar->EnableTool(wxID_REDO, true);
			}
			if (m_lpToolBar->GetToolState(ID_BLACK_DOG))
			{
				m_lpToolBar->ToggleTool(ID_BLACK_DOG, false);
			}
			if (m_lpToolBar->GetToolState(ID_WHITE_DOG))
			{
				m_lpToolBar->ToggleTool(ID_WHITE_DOG, false);
			}
			m_lpStatusBar->SetStatusText(STR_ANALYZING);
		}
		else
		{
			m_lpStatusBar->SetStatusText(STR_ENGINE_AVAILABLE);
		}
	}
}
