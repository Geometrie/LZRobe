#ifndef CAPP_H
#define CAPP_H
#include <wx/app.h>
#include "CMainFrame.h"
class CApp: public wxApp
{
public:
    virtual bool OnInit();
    CMainFrame *m_lpFrame;
};
#endif // CAPP_H
