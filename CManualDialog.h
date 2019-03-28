#ifndef CMANUALDIALOG_H
#define CMANUALDIALOG_H
#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/textctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/dialog.h>
class CManualDialog : public wxDialog
{

public:
	CManualDialog(wxWindow* lpParent, wxString wxstrTitle, wxString wxstrHelp, wxString wxstrButtonLabel);
protected:
	wxTextCtrl* m_lpTextCtrl;
	wxButton* m_lpButtonClose;
	void OnClose(wxCommandEvent &event);
	DECLARE_EVENT_TABLE()
};
#endif
