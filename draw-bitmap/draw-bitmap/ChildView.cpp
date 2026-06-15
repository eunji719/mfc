
// ChildView.cpp: CChildView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
#include "draw-bitmap.h"
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
	memBitmap.CreateCompatibleBitmap(&dc, w, h);
	memDC.SelectObject(&memBitmap);
	memDC.Rectangle(0, 0, w, h);

	CBitmap img;
	img.LoadBitmapW(IDB_BITMAP2);

	BITMAP bmpInfo; //비트맵 정보
	img.GetBitmap(&bmpInfo);

	//실제 비트맵 크기
	int imgW = bmpInfo.bmWidth;
	int imgH = bmpInfo.bmHeight;

	//화면에 출력하는 크기
	int drawW = imgW;
	int drawH = imgH;

	CDC imgDC;
	imgDC.CreateCompatibleDC(&dc);
	imgDC.SelectObject(&img); //도화지가 앞으로 그릴때 비트맵을 사용하겠다

	// 창보다 이미지가 크면 그때만 줄이기
	if (imgW > w || imgH > h) {
		double scaleX = (double)w / imgW;
		double scaleY = (double)h / imgH;
		double scale = min(scaleX, scaleY);

		drawW = (int)(imgW * scale);
		drawH = (int)(imgH * scale);
		//최대한 크게 보여야함!
	}

	// 항상 중앙
	int x = (w - drawW) / 2;
	int y = (h - drawH) / 2;

	// 크기가 원본이면 원본 출력, 줄어들어야 하면 축소 출력
	memDC.StretchBlt(
		x, y, drawW, drawH, //목적지
		&imgDC,
		0, 0, imgW, imgH, //어디에서 가져올것인가
		SRCCOPY);
	// imgDC->memDC로 크기 변경해서 복사

	dc.BitBlt(0, 0, w, h, &memDC, 0, 0, SRCCOPY); 
	// memDC->dc 크기 변경없이 복사

}

