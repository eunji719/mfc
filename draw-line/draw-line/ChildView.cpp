
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "draw-line.h"
#include "ChildView.h"
#include "MyPoint.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
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

MyPoint toRatio(CPoint pt, int w, int h) {
	double x = (double)pt.x / w;
	double y = (double)pt.y / h;
	MyPoint mPoint=MyPoint(x, y);
	return mPoint;
}

CPoint toScreen(MyPoint p, int w, int h) {
	CPoint pt = CPoint(p.getX()*w, p.getY()*h);
	return pt;
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

	//점이 두개이상이어야 for문이 실행 되도록
	for (int i = 1;i<m_currentLine.size();i++) {
		CPoint p1 = toScreen(m_currentLine[i - 1], w, h);
		CPoint p2 = toScreen(m_currentLine[i], w, h);
		memDC.MoveTo(p1);
		memDC.LineTo(p2);
	}

	for (auto line : m_lines) {
		for (int i = 1; i < line.size(); i++) {
			CPoint p1 = toScreen(line[i - 1], w, h);
			CPoint p2 = toScreen(line[i], w, h);
			memDC.MoveTo(p1);
			memDC.LineTo(p2);
		}
	}

	dc.BitBlt(0, 0, w, h, &memDC, 0, 0, SRCCOPY);

}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return true;
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if ((nFlags & MK_LBUTTON) != 0) {
		CRect rect;
		GetClientRect(&rect);
		m_currentLine.push_back(toRatio(point,rect.Width(),rect.Height()));
		Invalidate();
	}

	CWnd::OnMouseMove(nFlags, point);
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect rect;
	GetClientRect(&rect);
	m_currentLine.clear();
	m_currentLine.push_back(toRatio(point, rect.Width(), rect.Height()));
	
	Invalidate();

	CWnd::OnLButtonDown(nFlags, point);
}

void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CRect rect;
	GetClientRect(&rect);
	m_currentLine.push_back(toRatio(point, rect.Width(), rect.Height()));
	m_lines.push_back(m_currentLine);
	m_currentLine.clear();
	Invalidate();

	CWnd::OnLButtonUp(nFlags, point);
}
