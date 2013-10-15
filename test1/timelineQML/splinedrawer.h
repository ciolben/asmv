#ifndef SPLINEDRAWER_H
#define SPLINEDRAWER_H

#include <QQuickPaintedItem>
#include <QPainter>

#include "mathlib/spline.hpp"

class SplineDrawer : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(int curwidth READ curwidth WRITE setCurwidth)
    Q_PROPERTY(int curheight READ curheight WRITE setCurheight)

public:
    explicit SplineDrawer(QQuickItem *parent = 0);
    void paint(QPainter* painter);

    int curwidth() const;
    void setCurwidth(const int& width);
    int curheight() const;
    void setCurheight(const int& height);

    void addKey(ulong time, ulong map);

signals:

public slots:

private:
    int m_curwidth;
    int m_curheight;

    ulong m_max;
    ulong m_numKeys;

    long m_maxDiff;
    long m_minDiff;

    magnet::math::Spline m_spline;

    QMap<ulong, long> m_keys;
};

#endif // SPLINEDRAWER_H
