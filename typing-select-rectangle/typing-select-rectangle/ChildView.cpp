
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "typing-select-rectangle.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	m_box[0] = CRect(300, 300, 800, 600);
	m_box[1] = CRect(300, 700, 800, 1000);
	m_selected = -1;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_WM_ERASEBKGND()
	ON_WM_CHAR()
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

	for (int i = 0; i < 2; i++) {
		COLORREF borderColor;

		if (i == m_selected) borderColor = RGB(0, 200, 200);
		else borderColor = RGB(0, 0, 0);

		CPen pen(PS_SOLID, 3, borderColor);
		memDC.SelectObject(&pen);

		memDC.Rectangle(m_box[i]);
		memDC.SetBkMode(TRANSPARENT);
		memDC.DrawText(m_str[i], &m_box[i], DT_LEFT | DT_TOP);
	}

	
	

	dc.BitBlt(0, 0, w, h, &memDC, 0, 0, SRCCOPY);
}


BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return true;
}

void CChildView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (m_selected == -1) return;
	CString& str = m_str[m_selected];

	if (nChar == VK_RETURN) {
		str += _T("\r\n");
	}
	else if (nChar == VK_BACK) {
		if (str.GetLength() > 0) str.Delete(str.GetLength() - 1, 1);
	}
	else {
		str += TCHAR(nChar);
	}

	Invalidate();

	CWnd::OnChar(nChar, nRepCnt, nFlags);
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_selected = -1;

	for (int i = 0; i < 2; i++) {
		if (m_box[i].left <= point.x && m_box[i].right >= point.x && m_box[i].bottom >= point.y && m_box[i].top <= point.y) {
			m_selected = i;
			break;
		}
	}

	Invalidate();
	CWnd::OnLButtonDown(nFlags, point);
}
