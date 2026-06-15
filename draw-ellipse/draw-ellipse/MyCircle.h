#pragma once

class MyCircle {
private:
	double m_radius;
	CPoint pt1, pt2;
public:
	MyCircle() {
		m_radius = 0;
		pt1 = CPoint(0, 0);
		pt2 = CPoint(0, 0);
	}
	MyCircle(double r,CPoint p1,CPoint p2) {
		m_radius = r;
		pt1 = p1;
		pt2 = p2;
	}
	void draw(CDC &dc) {
		dc.Ellipse(pt1.x - m_radius, pt1.y - m_radius, pt1.x + m_radius, pt1.y + m_radius);
	}
};