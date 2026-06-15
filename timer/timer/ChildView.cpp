
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "timer.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_h = 0;
	m_m = 0;
	m_s = 0;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	

	ON_COMMAND(ID_BUTTON_H, &CChildView::OnButtonH)
	ON_COMMAND(ID_BUTTON_M, &CChildView::OnButtonM)
	ON_COMMAND(ID_BUTTON_S, &CChildView::OnButtonS)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
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

	CString str;
	if (m_s > 59) {
		m_s = 0;
		m_m++;
	}
	if (m_m > 59) {
		m_m = 0;
		m_h++;
	}
	str.Format(_T("%02d:%02d:%02d"), m_h, m_m, m_s);
	CFont font;
	font.CreatePointFont(300,_T("Arial"));
	CRect rect1(0, 0, 400, 250);
	memDC.SelectObject(&font);
	memDC.SetBkMode(TRANSPARENT);
	memDC.DrawText(str, &rect1, DT_CENTER | DT_VCENTER | DT_SINGLELINE);



	dc.BitBlt(0, 0, w, h, &memDC, 0, 0, SRCCOPY);

}



void CChildView::OnButtonH()
{
	m_h++;
	Invalidate();
}

void CChildView::OnButtonM()
{
	m_m++;
	Invalidate();

}

void CChildView::OnButtonS()
{
	m_s++;
	Invalidate();

}

int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	
	SetTimer(0, 1000,NULL);

	return 0;
}

BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return true;
}

void CChildView::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 0) {
		m_s++;
		Invalidate();
	}

	CWnd::OnTimer(nIDEvent);
}
