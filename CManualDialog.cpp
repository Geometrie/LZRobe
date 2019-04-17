#include "CManualDialog.h"

CManualDialog::CManualDialog(wxWindow* lpParent, wxString wxstrTitle, wxString wxstrHelp, wxString wxstrButtonLabel) : wxDialog(lpParent, wxID_ANY, wxstrTitle)
{
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer(2, 1, 0, 0);
	fgSizer1->SetFlexibleDirection(wxBOTH);
	fgSizer1->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_lpTextCtrl = new wxTextCtrl(this, wxID_ANY, wxstrHelp, wxDefaultPosition, wxSize(380, 350), wxTE_MULTILINE | wxTE_READONLY);
	fgSizer1->Add(m_lpTextCtrl, 0, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);

	m_lpButtonClose = new wxButton(this, wxID_CLOSE, wxstrButtonLabel, wxDefaultPosition, wxDefaultSize, 0);
	fgSizer1->Add(m_lpButtonClose, 0, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);


	this->SetSizer(fgSizer1);
	this->Layout();
	fgSizer1->Fit(this);

	this->Centre(wxBOTH);
}

void CManualDialog::OnClose(wxCommandEvent &event)
{
	EndModal(wxID_CLOSE);
}

BEGIN_EVENT_TABLE(CManualDialog, wxDialog)
EVT_BUTTON(wxID_CLOSE, CManualDialog::OnClose)
END_EVENT_TABLE()