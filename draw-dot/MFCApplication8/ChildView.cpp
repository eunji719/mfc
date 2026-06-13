
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication8.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_Dragging = false;
	
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_ERASEBKGND()
	ON_WM_RBUTTONUP()
	ON_WM_RBUTTONDOWN()
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

int numDots = 0;
void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.
	
	CRect rect;
	GetClientRect(&rect);
	int w = rect.Width();
	int h = rect.Height();

	CDC memDC;
	memDC.CreateCompatibleDC(&dc);

	CBitmap memBitmap;
	memBitmap.CreateCompatibleBitmap(&dc, w, h);

	memDC.SelectObject(&memBitmap);

	memDC.Rectangle(0, 0, w, h);
	if (m_Dragging) memDC.Rectangle(pt1.x, pt1.y, pt2.x, pt2.y);
	CBrush brush(RGB(0, 0, 0));
	memDC.SelectObject(&brush);
	//memDC.SelectStockObject(BLACK_PEN);

	CString str;
	str.Format(_T("점 개수: %d"),numDots);
	memDC.TextOutW(0, 0, str);

	for (auto e : m_points) {
		memDC.Ellipse(e.x - 2, e.y - 2, e.x + 2, e.y + 2);
		
	}
	
	

	dc.BitBlt(0, 0, w, h, &memDC, 0, 0, SRCCOPY);
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_points.push_back(point);
	numDots++;
	Invalidate();
	CWnd::OnLButtonDown(nFlags, point);
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if ((nFlags & MK_LBUTTON) != 0) {
		m_points.push_back(point);
		numDots++;
	}
	if ((nFlags & MK_RBUTTON) != 0) {
		m_Dragging = true;
		pt2 = point;
	}
	Invalidate();
	CWnd::OnMouseMove(nFlags, point);
}



void CChildView::OnLButtonUp(UINT nFlags, CPoint point)
{
	
	CWnd::OnLButtonUp(nFlags, point);
}

BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return true;
}

void CChildView::OnRButtonUp(UINT nFlags, CPoint point)
{
	m_Dragging = false;
	int left  = (pt1.x < pt2.x) ? pt1.x : pt2.x;
	int right = pt1.x < pt2.x ? pt2.x : pt1.x;
	int top = pt1.y < pt2.y ? pt1.y : pt2.y;
	int bottom = pt1.y < pt2.y ? pt2.y : pt1.y;
	for (int i = 0; i < m_points.size();) {
		/*if (m_points[i].x > pt1.x && m_points[i].x<pt2.x && m_points[i].y>pt1.y && m_points[i].y < pt2.y) {
			m_points.erase(m_points.begin() + i);
		} 이 방식대로하면 위에서아래로갈때 안지워짐*/
		if (m_points[i].x > left&& m_points[i].x<right && m_points[i].y>top && m_points[i].y < bottom) {
			m_points.erase(m_points.begin() + i);
		}
		else i++;
	}
	numDots = m_points.size();
	Invalidate();
	CWnd::OnRButtonUp(nFlags, point);
}

void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
	pt1 = point;
	pt2 = point;

	CWnd::OnRButtonDown(nFlags, point);
}
