#include <vector>
class CChildView : public CWnd
{
public:
    CChildView();

public:
    std::vector<CPoint>m_points;
    CPoint pt1, pt2;
    bool m_Dragging;

protected:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

public:
    virtual ~CChildView();

protected:
    afx_msg void OnPaint();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

    DECLARE_MESSAGE_MAP()
public:
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};