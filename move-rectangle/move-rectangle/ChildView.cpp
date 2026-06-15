
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "move-rectangle.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	vx = 0; vy = 0;
	m_pt = CPoint(100, 100);
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
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

	CBitmap bmp;
	bmp.CreateCompatibleBitmap(&dc, w, h);

	memDC.SelectObject(&bmp);
	memDC.Rectangle(0, 0, w, h);

	memDC.Rectangle(m_pt.x, m_pt.y, m_pt.x + 100, m_pt.y + 100);

	dc.BitBlt(0, 0, w, h, &memDC, 0, 0, SRCCOPY);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return true;
}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetTimer(0, 30, NULL);

	return 0;
}

// 0.03초마다 호출
void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	float time = 0.03;
	if (nIDEvent == 0) {
		CRect rect;
		GetClientRect(&rect);
		int w = rect.Width();
		int h = rect.Height();

		if (m_pt.x + 100 >= w || m_pt.x <= 0) vx = -vx;
		if (m_pt.y + 100 >= h || m_pt.y <= 0) vy = -vy;

		m_pt.x += time * vx;
		m_pt.y += time * vy;


		Invalidate();
	}
	CWnd::OnTimer(nIDEvent);
}

void CChildView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	float sp = 500;
	switch (nChar) {
	case VK_LEFT:   vx=-sp; vy = 0; break;
	case VK_RIGHT:	vx=sp; vy = 0; break;
	case VK_DOWN:	vy=sp; vx = 0; break;
	case VK_UP:		vy = -sp; vx = 0; break;
	default:		break;
	}
	Invalidate();


	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	double dx = point.x - m_pt.x;
	double dy = point.y - m_pt.y;

	double len = sqrt(dx * dx + dy * dy);
	if (len != 0) {
		double speed = 500;
		//멀리누른다고 속도가 빨라지지 않도록 
		//거리 커져도 len으로 나눠서 조절
		vx = speed * dx / len;
		vy = speed * dy / len;
	}
	
	Invalidate();

	CWnd::OnLButtonDown(nFlags, point);
}
