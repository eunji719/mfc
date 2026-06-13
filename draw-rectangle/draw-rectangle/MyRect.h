#pragma once


class MyRect {
private:
	int m_w;
	int m_h;
	CPoint p1, p2;
	COLORREF m_color;
public:
	MyRect() {
		m_w = 0; m_h = 0;
		m_color=RGB(255, 0, 0);
	}
	
	void draw(CDC &dc) {
		CPen pen(PS_SOLID, 3, m_color);
		CBrush brush(m_color);
		dc.SelectObject(&pen);
		dc.SelectObject(&brush);
		dc.Rectangle(p1.x,p1.y,p1.x+m_w,p1.y+m_h);
	}
	void setButtonDown(CPoint pt) {
		m_w = 0; m_h = 0;
		p1 = pt;
		p2 = pt;
	}
	void setButtonUp(CPoint pt) {
		p2 = pt;
		m_w = p2.x - p1.x;
		m_h = p2.y - p1.y;
	}

	void setColor(COLORREF color) {
		m_color = color;
	}
	
	
};