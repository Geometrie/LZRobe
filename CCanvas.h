#ifndef CCANVAS_H
#define CCANVAS_H
#include <time.h>
#include <wx/timer.h>
#include "CPainter.h"
class CCanvas: public CPainter
{
public:
    CCanvas(wxWindow *lpParent);
	~CCanvas();
    void m_fnShowResignResult();
    void m_fnShowCountResult(char *lpstrMessage);
	bool m_fnChangePosition(int x, int y);
	void m_fnDrawBuffer();
	wxMutex m_AnalyzeMutex, m_lpBufferMutex[2];
	int m_iDraw;
private:
	void OnSize(wxSizeEvent &event);
    void OnPaint(wxPaintEvent &event);
    void OnLeftButtonUp(wxMouseEvent &event);
    void OnRightButtonUp(wxMouseEvent &event);
	wxBitmap *m_lplpbmpBuffer[2];
    DECLARE_EVENT_TABLE()
};

#endif // CCANVAS_H
