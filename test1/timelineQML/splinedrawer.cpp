#include "splinedrawer.h"
#include "qmlregister.h"

#include <utility>
#include <vector>
#include "QDebug"

SplineDrawer::SplineDrawer(QQuickItem *parent) :
    QQuickPaintedItem(parent)
    , m_sequences(QList<Sequence*>())
    , m_editing(false)
    , m_dragging(false)
    , m_currentSequence(NULL)
    , m_currentModifyingPoint(0)
    , m_mod(0)
    , m_curIndex(0) //O(1) lookup for neighboring sequences
    , m_max(0)
    , m_maxDiff(5.f)
    , m_minDiff(-5.f)
    , m_numKeys(0)
    , m_duration(0) {
    QMLRegister::regQMLObject("spline", this);
}

void SplineDrawer::paint(QPainter *painter) {

    if (m_duration == 0) {
        return;
    }

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
    QColor magentaColor("darkMagenta");
    QColor selectionColor("magenta");
    pen = QPen(color);
    pen.setWidth(4);
    painter->setPen(pen);
    int halfRecWidth = HALF_RECWIDTH;
    int recWidth = 2 * halfRecWidth;
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

        if (seq == m_currentSequence) {
            pen.setColor(selectionColor);
            painter->setPen(pen);
        } else {
            pen.setColor(magentaColor);
            painter->setPen(pen);
        }

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
        if (m_editing && seq == m_currentSequence) {
            continue;
        }
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
        if(xil != 0) {
            painter->drawLine(xil, yil, startOffset, yscalingSum);
        }

        xil = startOffset;
        yil = yscalingSum;
        double x;
        for (x = resolution; x <= lastOffset - startOffset; x += resolution) {
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
        // add what is missing if needed
        if (lastOffset - startOffset - x != 0) {
            painter->drawLine(xil, yil, lastOffset, yscalingSum);
            xil = lastOffset;
            yil = yscalingSum;
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

///
/// \brief SplineDrawer::addKey
///     Add a key by sequence id. Create a sequence with
///     <i> addSequence </i> before.
/// \param seqId the sequence id.
/// \param time  =x
/// \param map  =y
///
void SplineDrawer::addKey(int seqId, ulong time, double map) {

    if (!(seqId >= 0 && seqId < m_sequences.size())) { return; }
    Sequence* seq = m_sequences.at(seqId);
    if (!(time <= seq->getBeginning() || time >= seq->getEnding())) {
        seq->addPoint(time, map);
    }
}

void SplineDrawer::modifyKey(ulong time, long new_map) {
    //  m_spline.modifyYPoint(time, computeDiff(time, new_map));
    //m_keys[time] = new_map;
}

///
/// \brief SplineDrawer::getInterpolationFactor
///         Assume that rate of video is constant
/// \param tpf time per frame
/// \param time when the frame wants to be played in original time
/// \return set of interpolation factors
///
QList<float> SplineDrawer::getInterpolationFactors(int tpf, ulong time)
{
    auto ratios = QList<float>();

    //coherence check
    if (tpf <= 0) {
        qDebug() << "getInterpolationFactor : warning : fps <= 0";
        return ratios;
    }
    if (time < 0) {
        qDebug() << "getInterpolationFactor : warning : time < 0";
        return ratios;
    }

    //find to which sequence time is part of (time given in ms)
    //asumption : two sequences are enough separated :
    //end != begin
    bool found = false;
    ulong accumulatedTime = 0; //seqs are sorted
    ulong nextSeqBegin = 0;
    Sequence* selectedSeq;
    for (int i = 0; i < m_sequences.size(); i++) {
        selectedSeq = m_sequences[i];
        accumulatedTime = selectedSeq->getBeginning();
        if (time >= selectedSeq->getBeginning()) {
            if (time <= selectedSeq->getEnding()) {
                found = true;
                if (++i < m_sequences.size()) {
                    nextSeqBegin = m_sequences[i]->getBeginning();
                }
                break;
            } else {
                accumulatedTime = selectedSeq->getEnding();
            }
        }
    }

    //find interpolation factor based on the space bw two frames
    if (!found) { //I'm not in sequence (at least at the beginning)
        ratios.append(1.f);
        return ratios;
    }

    float cumulatedRatio(0);
    float splineValue(0);
    float ratio;
    //rescaling
    ulong rescaledTime = time - selectedSeq->getBeginning();

    do {
        splineValue = (float) selectedSeq->computeSpline(rescaledTime);

        if (splineValue < 0) { //slowmotion
            //convert to ratio ([0,1] space)
            ratio = 1 / (-1.f * splineValue + 1.f);
            rescaledTime += tpf * ratio;
        } else { //acceleration
            //keep ratio in [1,inf] space
            //(2.5 means skip t and t+1 frames and dump image in the middle of t+1 and t+2)
            ratio = splineValue + 1.f;
        }

        ratios.append(ratio);
    } while ((cumulatedRatio += ratio) <= 1.f);

    return ratios;
}

int SplineDrawer::addSequence(ulong start, ulong end) {
    if (start >= end) { return -1; }
    Sequence* seq = new Sequence(start, end);
    m_sequences.append(seq);
    qSort(m_sequences.begin(), m_sequences.end(), []
    (const Sequence* s1, const Sequence* s2) {
        return s1->getBeginning() < s2->getBeginning();
    });
    return m_sequences.indexOf(seq);
}

void SplineDrawer::removeSequence(int sequenceId)
{
    if (sequenceId < 0 || sequenceId >= m_sequences.size()) {
        return;
    }
    removeSequence(m_sequences[sequenceId]);
}

void SplineDrawer::removeSequence(Sequence *seq) {
    if (seq == NULL) { return; }
    int index = m_sequences.indexOf(seq);
    if (index == -1) { return; }
    m_sequences.removeAt(index);
    if (seq == m_currentSequence) {
        m_currentSequence = NULL;
        m_curIndex = 0;
    }
    delete seq;
}

void SplineDrawer::fromPlanToLocal(double &x, double &y) {
    x = m_duration * (double)x / m_curwidth;
    y = (m_maxDiff - m_minDiff) * (double)y / m_curheight - (m_maxDiff - m_minDiff) / 2.f;
}

void SplineDrawer::initView(const ulong &duration) {
    if(duration != 0) {
        m_duration = duration;
    }

    //clean data
    foreach (Sequence* seq, m_sequences) {
        delete seq;
    }
    m_sequences.clear();
    m_currentSequence = NULL;

}

void SplineDrawer::updatePoints()
{
    this->update();
}

void SplineDrawer::mouseOnClick(int x, int y) {

    double nx = x, ny = y;
    fromPlanToLocal(nx, ny);

    if (m_editing) {
        //check if new point is valid, if not return
        foreach (Sequence* seq, m_sequences) {
            if (nx >= seq->getBeginning() && nx <= seq->getEnding()) {
                return;
            }
        }

        m_numKeys++;

        //editing
        if(m_numKeys == 1) {

            //add begin + create sequence
            m_currentSequence = new Sequence();
            m_sequences.append(m_currentSequence);
            m_currentSequence->modifyBeginning(nx);
            qSort(m_sequences.begin(), m_sequences.end(), []
            (const Sequence* s1, const Sequence* s2) {
                return s1->getBeginning() < s2->getBeginning();
            });
            m_curIndex = m_sequences.indexOf(m_currentSequence);
        } else {

            //add end
            //check if sequence will be valid (no over crossing)
            if (nx <= m_currentSequence->getBeginning() + 100) {
                m_numKeys--;
                return;
            }
            if (m_curIndex != m_sequences.size() - 1) {
                if (nx >= m_sequences.at(m_curIndex + 1)->getBeginning() - 100) {
                    m_numKeys--;
                    return;
                }
            }
            m_currentSequence->modifyEnding(nx);
        }

        if (m_numKeys == 2) {
            m_editing = false;
            m_numKeys = 0;
        }
    } else {

        //try to select a sequence
        bool found = false;
        for (int i = 0; i < m_sequences.size(); i++) {
            Sequence* seq = m_sequences[i];
            if (nx >= seq->getBeginning() && nx <= seq->getEnding()) {
                if (m_currentSequence != seq) {
                    m_currentSequence = seq;
                    m_curIndex = i;
                    //highlight selection and return
                    this->update();
                    return;
                } else {
                    /* continue adding point or return */
                }
                found = true;
                break;
            }
        }

        if (!found) {
            m_currentSequence = NULL;
        }
        //add point if we have to, else return
        if (m_currentSequence != NULL && !m_dragging) {
            //add point to current Sequence if not outside
            if (!(nx <= m_currentSequence->getBeginning() || ny >= m_currentSequence->getEnding())) {
                m_currentSequence->addPoint(nx, ny);
            }
        }
    }
    this->update();
}

void SplineDrawer::mouseOnButtonPressed(int x, int y, bool supr) {
    if (m_currentSequence == NULL) { return; }

    double nx = x, ny = y;
    fromPlanToLocal(nx, ny);

    if (m_dragging) {
        //move the object if it is possible (sequences are ordered)
        if (m_currentModifyingPoint == nx) { return; }

        int spacing = HALF_RECWIDTH * m_duration / m_curwidth;
        auto ctrlList = m_currentSequence->getControlPointsList();

        switch (m_mod) {
        case -1:
            //left
            if (m_curIndex == 0) {
                if (nx <= spacing) { return; }
            } else {
                Sequence* seq = m_sequences[m_curIndex - 1];
                if (seq->getEnding() >= nx - spacing) {
                    return;
                }
            }
            //right
            if (ctrlList.isEmpty()) {
                if (nx + spacing >= m_currentSequence->getEnding() - spacing) {
                    return;
                }
            } else {
                //play with nx which is dynamic (so that we are never stuck)
                if ((ctrlList[ctrlList.size() - 1].first + nx + spacing)
                        >= m_currentSequence->getEnding() - spacing) {
                    return;
                }
            }
            break;
        case 1:
            //right
            if (m_curIndex == m_sequences.size() - 1) {
                if (nx >= m_duration - spacing) {
                    return;
                }
            } else {
                Sequence* seq = m_sequences[m_curIndex + 1];
                if (seq->getBeginning() - spacing <= nx + spacing) {
                    return;
                }
            }
            //left
            if (ctrlList.isEmpty()) {
                if (nx - spacing <= m_currentSequence->getBeginning() + spacing) {
                    return;
                }
            } else {
                if ((ctrlList[ctrlList.size() - 1].first + m_currentSequence->getBeginning() + spacing)
                        >= nx - spacing) {
                    return;
                }
            }
            break;
        default:
            //left
            if (nx - spacing <= m_currentSequence->getBeginning() + spacing) {
                return;
            }
            //right
            if (nx + spacing >= m_currentSequence->getEnding() - spacing) {
                return;
            }
            break;
        }

        m_currentSequence->delPoint(m_currentModifyingPoint, m_mod);
        m_currentModifyingPoint = nx;
        if (m_mod == 0) {
            m_currentSequence->addPoint(nx, ny);
        }
        this->update();

    } else {
        //check if we are in an existing control points (ctrl pts sorted)
        m_mod = 0;
        double half_recwidth_localX = HALF_RECWIDTH, half_recwidth_localY = HALF_RECWIDTH + m_curheight / 2.f;
        fromPlanToLocal(half_recwidth_localX, half_recwidth_localY);
        if (nx >= m_currentSequence->getBeginning() - half_recwidth_localX
                && nx <= m_currentSequence->getBeginning() + half_recwidth_localX
                && ny >= -half_recwidth_localY && ny <= half_recwidth_localY) {
            if (supr) {
                removeSequence(m_currentSequence);
                this->update(); return;
            }
            m_mod = -1;
            m_currentModifyingPoint = m_currentSequence->getBeginning();
        } else if (nx <= m_currentSequence->getEnding() + half_recwidth_localX
                   && nx >= m_currentSequence->getEnding() - half_recwidth_localX
                   && ny >= -half_recwidth_localY && ny <= half_recwidth_localY) {
            if (supr) {
                removeSequence(m_currentSequence);
                this->update(); return;
            }
            m_mod = 1;
            m_currentModifyingPoint = m_currentSequence->getEnding();
        }

        if (m_mod != 0) {
            m_dragging = true;    //found beggining or ending
            return;
        }

        nx -= m_currentSequence->getBeginning(); //from local to sequence coords
        foreach (pair p, m_currentSequence->getControlPointsList()) {
            if (nx >= p.first - half_recwidth_localX && nx <= p.first + half_recwidth_localX
                    && ny >= p.second - half_recwidth_localY && ny <= p.second + half_recwidth_localY) {
                if (supr) {
                    m_currentSequence->delPoint(p);
                    this->update(); return;
                }
                m_currentModifyingPoint = p.first + m_currentSequence->getBeginning(); //from seq coords to local
                m_dragging = true;
                break; // found control points
            }
        }
    }
}

void SplineDrawer::mouseOnButtonReleased(int x, int y) {
    //if we were dragging a control point, adjust its position
    if (m_dragging) {
        m_dragging = false;
        m_currentModifyingPoint = 0;
        this->update();
    }
}
