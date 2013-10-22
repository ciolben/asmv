#ifndef SEQUENCE_HPP
#define SEQUENCE_HPP

#include <QtGlobal>
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

    void modifyBeginning(const ulong& begin) { m_begin = begin; }
    void modifyEnding(const ulong& end) { m_end = end; m_valid = false; }
    void addPoint(ulong x, double y) {
        m_spline.addPoint(x - m_begin, y); //spline is drawn in local spline coord
        m_controlPoints.append(pair(x - m_begin, y)); }

    ulong getBeginning() const { return m_begin; }
    ulong getEnding() const { return m_end; }

//this is not the simpliest way
//    typedef std::vector<std::pair<double, double>> base;
//    base::const_iterator cBegin() { m_spline.begin(); }
//    base::const_iterator cEnd() { m_spline.end; }
//that one si better
    QList<pair> getControlPointsList() { return m_controlPoints; }

    double computeSpline(ulong x) {
        if (!m_valid) {
            m_spline.clear();
            m_spline.addPoint(0.0, 0.0);
            m_spline.addPoint(m_end - m_begin, 0.0);
            foreach (pair p, m_controlPoints) {
                m_spline.addPoint(p.first, p.second);
            }
        }
        if (m_spline.size() <= 2) {
            return 0;
        }
        return m_spline(x);
    }
};
#endif // SEQUENCE_HPP
