#ifndef CCANVAS_H
#define CCANVAS_H
#include <wx/utils.h>
#include "CPainter.h"

class CCanvas: public CPainter
{
public:
    CCanvas(wxWindow *lpParent);
    void m_fnShowResignResult();
    void m_fnShowCountResult(char *lpstrMessage);
private:
    void OnPaint(wxPaintEvent &event);
    void OnLeftButtonUp(wxMouseEvent &event);
    void OnRightButtonUp(wxMouseEvent &event);
    void OnKeyUp(wxKeyEvent &event);
    DECLARE_EVENT_TABLE()
};

#endif // CCANVAS_H
