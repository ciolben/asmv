#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <QtGlobal>
#include <QtAlgorithms>
#include <mathlib/spline.hpp>

class Sequence {
private:
    ulong m_begin;
    ulong m_end;
    magnet::math::Spline m_spline;
    typedef std::pair<ulong, double> pair;
    QList<pair> m_controlPoints;
    bool m_valid;

public:
    Sequence(ulong begin, ulong end) :
        m_begin(begin)
      , m_end(end)
      , m_valid(true)
      , m_spline(magnet::math::Spline()) {
        m_spline.addPoint(0, 0.0);
        m_spline.addPoint(end - begin, 0.0);
    }
    Sequence() :
        m_begin(0)
      , m_end(0)
      , m_valid(false)
      , m_spline(magnet::math::Spline()) {
        m_spline.addPoint(0, 0.0);
    }
    ~Sequence() { /* don */ }

    void modifyBeginning(const ulong& begin) { m_begin = begin; m_valid = false; }
    void modifyEnding(const ulong& end) { m_end = end; m_valid = false; }
    void addPoint(ulong x, double y) {
        m_spline.addPoint(x - m_begin, y); //spline is drawn in local spline coords
        m_controlPoints.append(pair(x - m_begin, y)); }
    void delPoint(const pair& p) {
        m_controlPoints.removeAt(m_controlPoints.indexOf(p));
        m_valid = false; }
    void delPoint(ulong x, int mod = 0) {
        if (mod == -1) { modifyBeginning(x); return; }
        if (mod == 1) { modifyEnding(x); return; }
        x -= m_begin; //switch to local spline coords
        int res = -1; for(int i = 0; i < m_controlPoints.size(); i++) {
            if (m_controlPoints[i].first == x) { res = i; break; }
        };
        if (res != -1) { m_controlPoints.removeAt(res); m_valid = false;} }

    ulong getBeginning() const { return m_begin; }
    ulong getEnding() const { return m_end; }

    QList<pair> getControlPointsList() { return m_controlPoints; }

    double computeSpline(ulong x) {
        if (m_controlPoints.isEmpty()) { return 0.0; }
        if (!m_valid) {
            m_spline.clear();
            m_spline.addPoint(0.0, 0.0);
            m_spline.addPoint(m_end - m_begin, 0.0);

            qSort(m_controlPoints.begin(), m_controlPoints.end(), []
                  (const pair& p1, const pair& p2) {
                return p1.first < p2.second;
            });

            for (int i = 0; i < m_controlPoints.size(); i++) {
                pair& p = m_controlPoints[i];
                m_spline.addPoint(p.first, p.second);
            }
            m_valid = true;
        }
        if (m_spline.size() <= 2) {
            return 0;
        }
        return m_spline(x);
    }
};
#endif // SEQUENCE_HPP
