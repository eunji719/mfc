
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "change-shape-color.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	isSelected = false;
	pt = CPoint(0, 0);
	color = RGB(255, 255, 255);
	num = 1;
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_SHAPE_RECTANGLE, &CChildView::OnShapeRectangle)
	ON_COMMAND(ID_SHAPE_CIRCLE, &CChildView::OnShapeCircle)
	ON_WM_ERASEBKGND()
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

	CPen pen(PS_SOLID, 3, RGB(0, 0, 0));
	memDC.SelectObject(&pen);

	CBrush brush1(RGB(255, 0, 0));
	CBrush brush2(RGB(0, 255, 0));
	CBrush brush3(RGB(0, 0, 255));
	         
	memDC.SelectObject(&brush1);
	memDC.Rectangle(30, 30, 80, 70);

	memDC.SelectObject(&brush2);
	memDC.Rectangle(100, 30, 150,70);

	memDC.SelectObject(&brush3);
	memDC.Rectangle(170, 30, 220, 70);

	

	

	
	if(!isSelected) {
		memDC.SelectStockObject(NULL_BRUSH);
		switch (num) {
		case 1: memDC.Ellipse(30, 100, 220, 290);	break;
		case 2: memDC.Rectangle(30, 100, 220, 290); break;
		}
		
	}
	else {
		CBrush brush(color);
		memDC.SelectObject(&brush);
		switch (num) {
		case 1: memDC.Ellipse(30, 100, 220, 290);	break;
		case 2: memDC.Rectangle(30, 100, 220, 290); break;
		}
		
	}
	
	


	



	dc.BitBlt(0, 0, w, h, &memDC, 0, 0, SRCCOPY);
}


void CChildView::OnShapeRectangle()
{
	num = 2;
	Invalidate();
}
void CChildView::OnShapeCircle()
{
	num = 1;
	Invalidate();
}

BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return true;
}

void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	pt = point;
	if (pt.x > 30 && pt.x < 80 && pt.y < 70 && pt.y>30) {
		isSelected = true;
		color = RGB(255, 0, 0);
	}
	if (pt.x > 100 && pt.x < 150 && pt.y < 70 && pt.y>30) {
		isSelected = true;
		color = RGB(0, 255, 0);
	}
	if (pt.x > 170 && pt.x < 220 && pt.y < 70 && pt.y>30) {
		isSelected = true;
		color = RGB(0, 0, 255);
	}
	Invalidate();

	CWnd::OnLButtonDown(nFlags, point);
}
