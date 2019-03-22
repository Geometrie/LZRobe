#include "CLZProcess.h"
CLZProcess::CLZProcess(wxEvtHandler *lpParent, int nId): wxProcess(lpParent, nId)
{
    m_bAlive = false;
}
