#ifndef CCANVAS_H
#define CCANVAS_H
#include <time.h>
#include "CPainter.h"
class CCanvas: public CPainter
{
public:
    CCanvas(wxWindow *lpParent);
    void m_fnShowResignResult();
    void m_fnShowCountResult(char *lpstrMessage);
	bool m_fnChangePosition(int x, int y);
	void m_fnDrawBuffer(wxDC &dc);
	wxMutex m_AnalyzeMutex;
private:
	void OnSize(wxSizeEvent &event);
    void OnPaint(wxPaintEvent &event);
    void OnLeftButtonUp(wxMouseEvent &event);
    void OnRightButtonUp(wxMouseEvent &event);
    DECLARE_EVENT_TABLE()
};

#endif // CCANVAS_H
