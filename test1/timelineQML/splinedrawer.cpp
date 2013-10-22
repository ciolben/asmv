#include "splinedrawer.h"
#include "qmlregister.h"

#include <utility>
#include <vector>
#include "QDebug"

SplineDrawer::SplineDrawer(QQuickItem *parent) :
    QQuickPaintedItem(parent)
    //, m_keys(QMap<ulong, double>())
    //, m_seqs(QMap<ulong, magnet::math::Spline*>())
  , m_sequences(QList<Sequence*>())
  , m_editing(false)
  , m_currentSequence(NULL)
    , m_max(0)
    , m_maxDiff(5.f)
    , m_minDiff(-5.f)
    , m_numKeys(0)
  , m_duration(0)
    , m_spline(magnet::math::Spline()) {
    QMLRegister::regQMLObject("spline", this);
}

void SplineDrawer::paint(QPainter *painter) {

    if (m_duration == 0) { return; }

    //general draw parameters
    double const local_width = m_duration;
    double const local_height = m_maxDiff - m_minDiff;
    float yscalingSum = m_curheight / 2.f;
    float yscalingProd = m_curheight / (m_maxDiff - m_minDiff);
    float xscalingProd = m_curwidth / local_width;
    double lastOffset = 0;
    ulong startOffset = 0;
    QColor color("blue");
    QPen pen;

    //draw control points (before scaling)
    QColor blueColor("blue");
    QColor magentaColor("magenta");
    pen = QPen(color);
    pen.setWidth(4);
    painter->setPen(pen);
    int halfRecWidth = 5;
    int recWidth = 2 * halfRecWidth;
    typedef std::pair<ulong, double> pair;
    QList<pair> ctrlPoints;
    foreach (Sequence* seq, m_sequences) {
        startOffset = seq->getBeginning();
        lastOffset = seq->getEnding();
        ctrlPoints = seq->getControlPointsList();
        pen.setColor(blueColor);
        painter->setPen(pen);
        foreach (pair p, ctrlPoints) {
            painter->drawRoundRect((p.first + startOffset) * xscalingProd - halfRecWidth
                              , p.second * yscalingProd + yscalingSum - halfRecWidth
                              , recWidth, recWidth);
        }
        pen.setColor(magentaColor);
        painter->setPen(pen);
        painter->drawRoundRect(startOffset * xscalingProd - halfRecWidth, yscalingSum - halfRecWidth, recWidth, recWidth);

        if(lastOffset != 0) { //while editing
            painter->drawRoundRect(lastOffset * xscalingProd - halfRecWidth, yscalingSum - halfRecWidth, recWidth, recWidth);
        }
    }

    //draw the lines (scaled)
    color = QColor("red");
    pen = QPen(color);
    painter->setPen(pen);

    //draw parameters
    painter->scale(m_curwidth / local_width, 1.f);
    double resolution = 0;

    //draw sequences
    bool firstIteration = true;
    int xi, yi, xil = 0, yil = 0;
    double xd, yd;

    foreach (Sequence* seq, m_sequences) {
        startOffset = seq->getBeginning();
        lastOffset = seq->getEnding();
        
        if (firstIteration) {
            firstIteration = false;
            //draw first unchanged sequence
            if (startOffset != 0) {
                painter->drawLine(0, yscalingSum, startOffset, yscalingSum);
            }
        }
        
        //10 samples bw control points
        resolution = (lastOffset - startOffset) / (10 * (seq->getControlPointsList().size() + 1));

        //link two sequences
        if(xil != 0 && yil != 0) {
            painter->drawLine(xil, yil, startOffset, yscalingSum);
        }

        xil = startOffset;
        yil = yscalingSum;
        for (double x = resolution; x <= lastOffset - startOffset; x += resolution) {
            xd = x + startOffset;
            yd = seq->computeSpline(x) * yscalingProd + yscalingSum;

            //adjust rasterization on x
            xi = xd - 0.5 <= (int)xd ? xd : xd + 0.5;

            //adjust rasterization on y
            yi = yd - 0.5 <= (int)yd ? yd : yd + 0.5;

            painter->drawLine(xil, yil, xi, yi);
            xil = xi;
            yil = yi;
        }
    }
    
    //draw last sequence
    if (lastOffset != local_width) {
        painter->drawLine(lastOffset, yscalingSum, local_width, yscalingSum);
    }
}

inline long SplineDrawer::computeDiff(ulong time, long map) {
    if (time > m_max) {
        m_max = time;
    }

    long diff = time - map;
    if (diff < m_minDiff) {
        m_minDiff = diff;
    } else if (diff > m_maxDiff) {
        m_maxDiff = diff;
    }

    return diff;
}

void SplineDrawer::addKey(ulong time, long map) {
    //m_spline.addPoint((double) time, computeDiff(time, map));
    //m_keys[time] = map;
    //m_numKeys++;
}

void SplineDrawer::modifyKey(ulong time, long new_map) {
    m_spline.modifyYPoint(time, computeDiff(time, new_map));
    //m_keys[time] = new_map;
}

void SplineDrawer::addSequence(ulong start, ulong end) {
    m_sequences.append(new Sequence(start, end));
}

void SplineDrawer::initView(const ulong &duration) {
    if(duration != 0) {
        m_duration = duration;
    }

    /*
     * Add equally spaced points to the spline, from 0 to maxtime
     */


}

void SplineDrawer::mouseOnClick(int x, int y) {
    double nx = m_duration * (double)x / m_curwidth;
    double ny = (m_maxDiff - m_minDiff) * (double)y / m_curheight - (m_maxDiff - m_minDiff) / 2.f;

    if (m_editing) {
        m_numKeys++;

        //editing
        if(m_numKeys == 1) {
            //add begin + create sequence
            m_currentSequence = new Sequence();
            m_sequences.append(m_currentSequence);
            m_currentSequence->modifyBeginning(nx);
        } else {
            //add end
            m_currentSequence->modifyEnding(nx);
        }

        if (m_numKeys == 2) {
            m_editing = false;
            m_numKeys = 0;
            qDebug() << "Editing sequence finished.";
        }
    } else {

        if (m_currentSequence != NULL) {
            //add point to current Sequence
            if (nx < m_currentSequence->getBeginning() || nx > m_currentSequence->getEnding()) {
                qDebug() << "Point outside sequence.";
            } else {
                m_currentSequence->addPoint(nx, ny);
            }
        }
    }
    this->update();
}
