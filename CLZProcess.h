#ifndef CLZPROCESS_H
#define CLZPROCESS_H
#include <wx/process.h>
enum PROCESS_EXIT_TYPE
{
	PET_FAILURE,
    PET_COLLAPSE,
    PET_STOP,
    PET_QUIT
};
class CLZProcess: public wxProcess
{
public:
    CLZProcess(wxEvtHandler *lpParent, int nId);
    bool m_bAlive;
};
#endif // CLZPROCESS_H
