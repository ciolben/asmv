#ifndef OPTICALFLOWTOOLS_H
#define OPTICALFLOWTOOLS_H

#include <QString>
#include <QImage>
#include <QLibrary>

#include "timelineQML/Sequence.hpp"

class OpticalFlowTools {

public:
    static QImage* computeCoarse2Fine(const QString& im1, const QString& im2);
    static OpticalFlowTools *createWindow(QWidget *parent);

    OpticalFlowTools();
    ~OpticalFlowTools() {}

    enum ComputationMods {
        GPU, CPU, Matlab
    };

    void computeFlow(const QImage* frame1, const QImage* frame2, QImage* flow);
    QList<float>* getInterpolationFactors(int tpf, ulong time);

    QList<Sequence *> getSequences() const { return m_sequences; }
    void setSequences(const QList<Sequence *> &sequences) { m_sequences = sequences; }
    void setComputationMod(ComputationMods computationMod) { m_computationMod = computationMod; }

private:
    QList<Sequence*> m_sequences;
    ComputationMods m_computationMod;

    QLibrary* optflowLib;
    typedef QImage*(*computeOptflowFunction)(const QImage& frame1, const QImage& frame2);

};

#endif // OPTICALFLOWTOOLS_H
