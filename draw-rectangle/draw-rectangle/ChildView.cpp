
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "draw-rectangle.h"
#include "ChildView.h"
#include "MyRect.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_color = RGB(255, 0, 0);
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_COLOR_RED, &CChildView::OnColorRed)
	ON_COMMAND(ID_COLOR_GREEN, &CChildView::OnColorGreen)
	ON_COMMAND(ID_COLOR_BLUE, &CChildView::OnColorBlue)
END_MESSAGE_MAP()



// CChildView 메시지 처리기

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	int w = rect.Width();
	int h = rect.Height();
	CDC memDC;
	memDC.CreateCompatibleDC(&dc);
	CBitmap memBitmap;
	memBitmap.CreateCompatibleBitmap(&dc,w,h);
	memDC.SelectObject(&memBitmap);
	memDC.Rectangle(0, 0, w, h);


	for (auto rect : rects) {
		rect.draw(memDC);
	}

	dc.BitBlt(0, 0, w, h, &memDC, 0, 0, SRCCOPY);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return true;
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	MyRect rect;
	rect.setColor(m_color);
	rect.setButtonDown(point);
	rects.push_back(rect);
	SetCapture();

	CWnd::OnLButtonDown(nFlags, point);
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if ((nFlags & MK_LBUTTON) != 0) {
		rects.back().setButtonUp(point);
		Invalidate();
	}
	

	CWnd::OnMouseMove(nFlags, point);
}

void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	rects.back().setButtonUp(point);
	Invalidate();

	ReleaseCapture();
	
	CWnd::OnLButtonUp(nFlags, point);
}

void CChildView::OnColorRed()
{
	m_color = RGB(255, 0, 0);
}

void CChildView::OnColorGreen()
{
	m_color = RGB(0, 255, 0);
}

void CChildView::OnColorBlue()
{
	m_color = RGB(0, 0, 255);
}
