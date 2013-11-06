#include "project.h"
#include "Image.h"
#include "OpticalFlow.h"
#include <iostream>

#include "opticalflowtools.h"
#include "opticalflowui.h"

#include <QDebug>

OpticalFlowTools::OpticalFlowTools() :
    m_sequences(QList<Sequence*>())
{
    //QMLRegister::regQMLObject("optflowtools", this);
}

///
/// \brief OpticalFlowTools::getInterpolationFactors
/// \param tpf time per frame
/// \param time at which the original frame was played
/// \return the set of factors (0 < a <= 1) to multiply the flow with.
/// Note : this method should be used from the beginning to the end in order to
///to accumulate the time.
///
QList<float>* OpticalFlowTools::getInterpolationFactors(int tpf, ulong time)
{
    //coherence check
    if (tpf <= 0) {
        qDebug() << "getInterpolationFactor : warning : fps <= 0";
        return NULL;
    }
    if (time == 0) {
        qDebug() << "getInterpolationFactor : warning : time = 0";
        return NULL;
    }

    //find to which sequence time is part of (time given in ms)
    //asumption : two sequences are enough separated :
    //end != begin
    bool found = false;
    ulong accumulatedTime = 0; //seqs are sorted
    ulong nextSeqBegin = 0;
    Sequence* selectedSeq;
    for (int i = 0; i < m_sequences.size(); i++) {
        Sequence* selectedSeq = m_sequences[i];
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
    auto ratios = new QList<float>();
    if (!found) { //I'm not in sequence (at least at the beginning)
        ratios->append(1.f);
        return ratios;
    }

    float cumulatedRatio = 0;
    float rate = 0;
    ulong resetTime = time - selectedSeq->getBeginning();
    do {
        if (cumulatedRatio != 0) { ratios->append(cumulatedRatio); }
        rate = (float) selectedSeq->computeSpline(resetTime);
        if (rate < 0) { //slowmotion
            rate = -1.f / rate;
            resetTime += tpf * rate;
        } else { //acceleration
            /* not yet implemented */
            rate = 1.f; //just highpass filtering
        }
    } while ((cumulatedRatio += rate) <= 1.f);
    return ratios;
}

///
/// \brief OpticalFlowTools::createWindow
/// Open a new QT object window.
/// Note used anymore : Once created, the object opticalflow tools is available
/// in QMLRegister.
OpticalFlowTools* OpticalFlowTools::createWindow(QWidget *parent)
{
    /*
     * CPP version
     */

    OpticalFlowUI* ui = new OpticalFlowUI(parent);
    ui->show();

    OpticalFlowTools* optflowTools = new OpticalFlowTools();
    ui->setOpticalFlowTools(optflowTools);

    return optflowTools;

    /*-----------------------------
     *QML window : not used because cpp dynamic image loading is a mess with qml
     *
    QUrl qmlSource("opticalflowUI.qml");
    qmlRegisterType<OpticalFlowTools>("OpticalFlowTools", 1, 0, "OpticalFlowTools");
    QQmlEngine* engine = new QQmlEngine();

    engine->addImageProvider();

    // this->connect(engine, signal, slot);
    QQmlComponent* component = new QQmlComponent(engine);
    component->loadUrl(qmlSource);
    if (!component->isReady()) {
        qDebug() << "Error while loading opticaflowUI.qml : " << component->errorString();
        return;
    }

    QQuickWindow* opticalflowUI = (QQuickWindow*) component->create();
    opticalflowUI->show();
    component->deleteLater();

    OpticalFlowTools* optflowtools = (OpticalFlowTools*) QMLRegister::getQMLObject("optflowtools");
    optflowtools->setQMLWindow(opticalflowUI);
    */
}

void OpticalFlowTools::computeFlow(const QImage* frame1, const QImage* frame2, QImage* flow)
{
    if (frame1 == NULL || frame2 = NULL) {
        flow = NULL;
        return;
    }

    //TODO

}

QImage* OpticalFlowTools::computeCoarse2Fine(const QString& im1, const QString& im2) {
    DImage dimg1,dimg2;

    dimg1.imread(im1);
    dimg2.imread(im2);

    if (dimg2.IsEmpty() || dimg2.IsEmpty()) {
        return NULL;
    }

    // get the parameters
    double alpha= 1;
    double ratio=10.0;
    int minWidth= 40;
    int nOuterFPIterations = 3;
    int nInnerFPIterations = 1;
    int nSORIterations= 20;

    double interp = 0.5;

    DImage vx,vy,warpI2;
    OpticalFlow::Coarse2FineFlow(vx,vy,warpI2,dimg1,dimg2,
                                 alpha,ratio,
                                 minWidth,nOuterFPIterations,nInnerFPIterations,nSORIterations
                                 , 1.0);

    warpI2.imwrite("_flowResult1.jpg");
    //we have the flow
    //compute interpolation
    OpticalFlow::warpFL(warpI2, dimg1, dimg2, vx, vy, interp);


//    DImage featureImage;
//    OpticalFlow::im2feature(featureImage, warpI2);

//    flow.Coarse2FineFlowLevel(vx,vy,warpI2,dimg1,dimg2,
//                                 alpha,ratio, 1,
//                                 nOuterFPIterations,nInnerFPIterations,nSORIterations);

//    OpticalFlow::ComputeOpticalFlow(dimg1, dimg2, warpI2);

    bool res = true;

//    int img_width = warpI2.width();
//    int img_height = warpI2.height();
//    uchar* imgbuf = (uchar*) malloc(img_width*img_height*4);
//    QImage* imgres = new QImage(imgbuf,img_width,img_height,QImage::Format_RGB32);
//    res = warpI2.imwrite("flowout.jpg");

//    res = featureImage.imwrite("feature.jpg");

    res = warpI2.imwrite("_flowResult2.jpg");
    return res ? NULL : new QImage();

//    dimg2.imwrite(imgres);
    //            return imgres;
}

