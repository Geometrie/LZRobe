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
	}
	m_esCurrentEngine = ES_WAITING_OPEN;
}

void CGameStatusManager::m_fnEngineConfirmed()
{
	if (m_esCurrentEngine == ES_WAITING_OPEN)
	{
		m_lpEditMenu->SetLabel(ID_LEELA_ZERO, _("Stop Engine"));
		m_lpToolBar->SetToolNormalBitmap(ID_LEELA_ZERO, wxBITMAP(STOP_BMP));
		m_lpToolBar->SetToolDisabledBitmap(ID_LEELA_ZERO, wxBITMAP(STOP_DISABLE_BMP));
		m_lpToolBar->SetToolShortHelp(ID_LEELA_ZERO, _("Stop Leela Zero Engine"));
		m_lpEditMenu->Enable(ID_LEELA_ZERO, true);
		m_lpToolBar->EnableTool(ID_LEELA_ZERO, true);
		m_lpToolBar->EnableTool(wxID_SAVE, true);
		m_lpToolBar->EnableTool(ID_BLACK_DOG, true);
		m_lpToolBar->EnableTool(ID_WHITE_DOG, true);
		m_lpToolBar->EnableTool(ID_ANALYZE, true);
		m_lpToolBar->EnableTool(ID_FINAL_SCORE, true);
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
		m_lpToolBar->EnableTool(wxID_SAVE, false);
		m_lpToolBar->EnableTool(ID_BLACK_DOG, false);
		m_lpToolBar->EnableTool(ID_WHITE_DOG, false);
		m_lpToolBar->EnableTool(ID_ANALYZE, false);
		m_lpToolBar->EnableTool(ID_FINAL_SCORE, false);
		m_esCurrentEngine = ES_WAITING_CLOSE;
	}
}

void CGameStatusManager::m_fnEngineClosed()
{
	if (m_esCurrentEngine == ES_WAITING_CLOSE)
	{
		m_lpEditMenu->SetLabel(ID_LEELA_ZERO, _("Run Engine"));
		m_lpToolBar->SetToolNormalBitmap(ID_LEELA_ZERO, wxBITMAP(RUN_BMP));
		m_lpToolBar->SetToolDisabledBitmap(ID_LEELA_ZERO, wxBITMAP(RUN_DISABLE_BMP));
		m_lpToolBar->SetToolShortHelp(ID_LEELA_ZERO, _("Run Leela Zero Engine"));
		m_lpEditMenu->Enable(ID_LEELA_ZERO, true);
		m_lpToolBar->EnableTool(ID_LEELA_ZERO, true);
		m_esCurrentEngine = ES_CLOSED;
	}
}

void CGameStatusManager::m_fnSetBlackDog()
{
	if (m_esCurrentEngine == ES_OPENED)
	{
		if (!m_lpToolBar->GetToolState(ID_WHITE_DOG))
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
			}
			else
			{
				m_lpEditMenu->Enable(wxID_UNDO, true);
				m_lpEditMenu->Enable(wxID_REDO, true);
				m_lpToolBar->EnableTool(wxID_UNDO, true);
				m_lpToolBar->EnableTool(wxID_REDO, true);
			}
		}
	}
}

void CGameStatusManager::m_fnSetWhiteDog()
{
	if (m_esCurrentEngine == ES_OPENED)
	{
		if (!m_lpToolBar->GetToolState(ID_BLACK_DOG))
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
			}
			else
			{
				m_lpEditMenu->Enable(wxID_UNDO, true);
				m_lpEditMenu->Enable(wxID_REDO, true);
				m_lpToolBar->EnableTool(wxID_UNDO, true);
				m_lpToolBar->EnableTool(wxID_REDO, true);
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
		}
	}
}