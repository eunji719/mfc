
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "ChildView.h"
#include "draw-ellipse.h"
#include "framework.h"
#include "MyCircle.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	
	radius = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
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
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc, w, h);
	memDC.SelectObject(&bitmap);
	memDC.Rectangle(0, 0, w, h);

	for (auto e : m_circles) {
		e.draw(memDC);
	}

	currentCircle.draw(memDC);

	
	

	dc.BitBlt(0, 0, w, h, &memDC, 0, 0, SRCCOPY);

}



BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return true;
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	pt1 = point;
	pt2 = point;
	SetCapture();
	Invalidate();

	CWnd::OnLButtonDown(nFlags, point);
}

void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	pt2 = point;
	double dx = pt2.x - pt1.x;
	double dy = pt2.y - pt1.y;
	radius = sqrt(dx * dx + dy * dy);
	MyCircle circle=MyCircle(radius,pt1,pt2);
	m_circles.push_back(circle);
	Invalidate();
	ReleaseCapture();

	CWnd::OnLButtonUp(nFlags, point);
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	
	if ((nFlags & MK_LBUTTON) != 0) {
		pt2 = point;
		double dx = pt2.x - pt1.x;
		double dy = pt2.y - pt1.y;
		radius = sqrt(dx * dx + dy * dy);
		MyCircle circle = MyCircle(radius, pt1, pt2);
		currentCircle = circle;
		Invalidate();
	}

	CWnd::OnMouseMove(nFlags, point);
}
