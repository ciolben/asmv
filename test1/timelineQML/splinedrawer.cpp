#include "splinedrawer.h"
#include "qmlregister.h"

#include "QDebug"

SplineDrawer::SplineDrawer(QQuickItem *parent) :
    QQuickPaintedItem(parent)
    , m_keys(QMap<ulong, long>())
    , m_max(0)
    , m_maxDiff(0.f)
    , m_minDiff(0.f)
    , m_numKeys(0)
    , m_spline(magnet::math::Spline()) {
    QMLRegister::regQMLObject("spline", this);
}

void SplineDrawer::paint(QPainter *painter) {
    QColor redcolor = QColor("red");
    QPen pen(redcolor, 1);
    painter->setPen(pen);

    // using namespace magnet::math;

    double const local_width = m_max;
    double const local_height = m_maxDiff + m_minDiff;

    painter->translate(0.0, m_curheight / 2.f);
    //painter->scale(m_curwidth / local_width, m_curheight / local_height);
    painter->scale(m_curwidth / local_width, 1);

    int xi, yi;
    double xd, yd;
    for (double x = 0.0; x < local_width; x += 0.5) {
        xd = x;
        yd = m_spline(x);

        //rasterize on x
        xi = xd - 0.5 <= xd - (int)xd ? (int)xd : (int)(xd + 0.5);

        //rasterize on y
        yi = yd - 0.5 <= yd - (int)yd ? (int)yd : (int)(yd + 0.5);
        yi += m_maxDiff;
        painter->drawPoint(xi, yi);
    }


//    for (float x = 0; x < local_width; x += 20) {
//        spline.addPoint(x, local_height * abs(cos(x)));
//    }

//    painter->scale(m_curwidth / local_width, m_curheight / local_height);

    // QList<double> list = QList<double>();
//    int xi, yi;
//    double xd, yd;
//    for (double x = 0.0; x < local_width; x += 0.5) {
//        xd = x;
//        yd = spline(x);
//        //rasterize on x
//        xi = xd - 0.5 <= xd - (int)xd ? (int)xd : (int)(xd + 0.5);

//        //rasterize on y
//        yi = yd - 0.5 <= yd - (int)yd ? (int)yd : (int)(yd + 0.5);

//       painter->drawPoint(xi, yi);
//    }

}

int SplineDrawer::curwidth() const {
    return m_curwidth;

}

void SplineDrawer::setCurwidth(const int &width) {
    m_curwidth = width;
}


int SplineDrawer::curheight() const {
    return m_curheight;

}

void SplineDrawer::setCurheight(const int &height) {
    m_curheight = height;
}

void SplineDrawer::addKey(ulong time, ulong map) {
    if (time > m_max) {
        m_max = time;
    }

    long diff = time - map;
    if (diff < m_minDiff) {
        m_minDiff = diff;
    } else if (diff > m_maxDiff) {
        m_maxDiff = diff;
    }

    m_spline.addPoint((double) time, diff);
    m_keys[time] = map;
    m_numKeys++;
}
