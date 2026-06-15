
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "typing.h"
#include "ChildView.h"

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
	ON_WM_CHAR()
	ON_WM_ERASEBKGND()
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

	CRect textRect(0, 0, w, h);
	memDC.DrawText(m_str,&textRect,DT_LEFT|DT_TOP);

	dc.BitBlt(0, 0, w, h, &memDC, 0, 0, SRCCOPY);

}


void CChildView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (nChar == VK_BACK) {
		if (m_str.GetLength() > 0) m_str.Delete(m_str.GetLength() - 1, 1);
	}
	else if (nChar == VK_RETURN) {
		m_str += _T("\r\n");
	}
	else {
		m_str += TCHAR(nChar);
	}
	Invalidate();

	CWnd::OnChar(nChar, nRepCnt, nFlags);
}

BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return true;
}
