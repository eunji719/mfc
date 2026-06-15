
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "expand-bitmap.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChildView

CChildView::CChildView()
{
	pt1 = CPoint(0, 0);
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


	CBitmap img;
	img.LoadBitmapW(IDB_BITMAP2);
	BITMAP bmpInfo;
	img.GetBitmap(&bmpInfo);
	int imgW = bmpInfo.bmWidth;
	int imgH = bmpInfo.bmHeight;

	int x = pt1.x, y = pt1.y;
	if (x < 0) x = 0;
	if (y < 0) y = 0;
	if (x > imgW - 100) x = imgW - 100;
	if (y > imgH - 100) y = imgH - 100;


	CDC imgDC;
	imgDC.CreateCompatibleDC(&memDC);
	imgDC.SelectObject(&img);


	memDC.BitBlt(0, 0, imgW, imgH, &imgDC, 0, 0, SRCCOPY);

	CPen pen(PS_SOLID, 3, RGB(255, 0, 0));
	memDC.SelectStockObject(NULL_BRUSH);
	memDC.SelectObject(&pen);
	memDC.Rectangle(x, y, x + 100, y + 100);

	memDC.StretchBlt(
		imgW, 0, 300, 300,
		&imgDC,
		x, y, 100, 100
		, SRCCOPY);


	dc.BitBlt(0, 0, w, h, &memDC, 0, 0, SRCCOPY);
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
	pt1 = point;
	Invalidate();
	SetCapture();
	CWnd::OnLButtonDown(nFlags, point);
}

void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
	if ((nFlags & MK_LBUTTON) != 0) {
		pt1 = point;
		Invalidate();
	}
	CWnd::OnMouseMove(nFlags, point);
}

void CChildView::OnLButtonUp(UINT nFlags, CPoint point)                        
{
	pt1 = point;
	Invalidate();
	ReleaseCapture();
	CWnd::OnLButtonUp(nFlags, point);
}

BOOL CChildView::OnEraseBkgnd(CDC* pDC)
{
	return true;
}
