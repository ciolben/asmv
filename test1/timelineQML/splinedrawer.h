#ifndef SPLINEDRAWER_H
#define SPLINEDRAWER_H

#include <QQuickPaintedItem>
#include <QPainter>

#include "Sequence.hpp"
#include "mathlib/spline.hpp"

class SplineDrawer : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(int curwidth READ curwidth WRITE setCurwidth)
    Q_PROPERTY(int curheight READ curheight WRITE setCurheight)
    Q_PROPERTY(int duration READ duration WRITE setduration NOTIFY durationChanged)
    Q_PROPERTY(int playposition READ playposition WRITE setplayposition NOTIFY playpositionChanged)

public:
    explicit SplineDrawer(QQuickItem *parent = 0);
    void paint(QPainter* painter);

    //typedef std::pair<ulong, magnet::math::Spline*> Sequence;

    int curwidth() const { return m_curwidth; }
    void setCurwidth(const int& width) { m_curwidth = width; }
    int curheight() const { return m_curheight; }
    void setCurheight(const int& height) { m_curheight = height; }
    int duration() const { return m_duration; }
    void setduration(const int& duration) { m_duration = duration; emit durationChanged(duration);}
    int playposition() const { return m_playPosition; }
    void setplayposition(const int& playPosition) { m_playPosition = playPosition; emit playpositionChanged(playPosition);}
    QList<Sequence*> getSequences() const { return m_sequences; }

    void addKey(int seqId, ulong time, double map);
    void modifyKey(ulong time, long new_map);
    void beginAddSequence() { m_editing = true; }

    QList<float> getInterpolationFactors(int tpf, ulong time);

    void initView(const ulong& duration = 0);
    void updatePoints();

    int addSequence(ulong start, ulong end);
    void removeSequence(int sequenceId);

    bool isModified() { return m_modified; }

    float getYScalingFactor() { return m_curheight / (m_maxDiff - m_minDiff); }
    float getXScalingFactor() { return m_curwidth / m_duration; }

signals:
    void durationChanged(int);
    void playpositionChanged(int);

public slots:
    void mouseOnClick(int x, int y);
    void mouseOnButtonPressed(int x, int y, bool supr);
    void mouseOnButtonReleased(int x, int y);

private:
    int m_curwidth;
    int m_curheight;
    int m_duration;
    int m_playPosition;
    int m_mod;
    int m_curIndex;

    ulong m_max;
    ulong m_numKeys;
    ulong m_currentModifyingPoint;

    long m_maxDiff;
    long m_minDiff;

    bool m_editing;
    bool m_dragging;
    bool m_modified; //true when user add/rm/move a keypoint at least one time

    Sequence* m_currentSequence;
    QList<Sequence*> m_sequences;

    void removeSequence(Sequence *seq);

    inline void fromPlanToLocal(double &x, double &y);
    inline long SplineDrawer::computeDiff(ulong time, long map);

    static const int HALF_RECWIDTH = 5;
    typedef std::pair<ulong, double> pair;
};

#endif // SPLINEDRAWER_H
