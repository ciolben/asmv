#ifndef OPTICALFLOWTOOLS_H
#define OPTICALFLOWTOOLS_H

#include <QString>
#include <QImage>
#include <QLibrary>
#include <QProcess>

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

    QImage* computeFlow(const QImage* frame1, const QImage* frame2, const QString& f1 = "", const QString& f2 = "");
    QList<float>* getInterpolationFactors(int tpf, ulong time);
    QImage* interpolate(const QImage* frame1, const QImage* frame2, const float factor, const QString& f1 = "", const QString &f2 = "", const QString& suffix = "i", const bool compressedFormat = true);

    QList<Sequence *> getSequences() const { return m_sequences; }
    void setSequences(const QList<Sequence *> &sequences) { m_sequences = sequences; }
    void setComputationMod(ComputationMods computationMod) { m_computationMod = computationMod; }

private:
    QList<Sequence*> m_sequences;
    ComputationMods m_computationMod;

    QLibrary* m_optflowLib;
    typedef QImage*(*computeOptflowFunction)(const QImage& frame1, const QImage& frame2, const QString& basefilename);
    computeOptflowFunction computeOptFlow;
    typedef QImage*(*computeInterpolationFunction)(const QImage& frame1, const QImage& frame2, const float factor, const QString& basefilename);
    computeInterpolationFunction computeInterpolation;

    QProcess* m_process;

};

#endif // OPTICALFLOWTOOLS_H
