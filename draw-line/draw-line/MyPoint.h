#pragma once

class MyPoint {
protected:
	double m_x, m_y;
public:
	MyPoint(double x,double y) {
		m_x = x;
		m_y = y;
	}
	double getX() { return m_x; }
	double getY() { return m_y; }
};
