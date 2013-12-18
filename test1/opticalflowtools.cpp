#include "project.h"
#include "Image.h"
#include "OpticalFlow.h"
#include <iostream>

#include "opticalflowtools.h"
#include "opticalflowui.h"

#include <QDebug>

OpticalFlowTools::OpticalFlowTools() :
    m_sequences(QList<Sequence*>())
  , m_optflowLib(NULL)
  , m_process(NULL)
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

QImage *OpticalFlowTools::interpolate(const QImage *frame1, const QImage *frame2
                                      , const float factor, const QString &f1, const QString &f2
                                      , const QString& outFolderCst
                                      , const QString& suffix, const bool compressedFormat)
{
    if (frame1 == NULL || frame2 == NULL) {
        return NULL;
    }

    if (m_process == NULL && m_optflowLib == NULL) {
        QString libpath = "";
        QLibrary* library = new QLibrary(libpath + "opticalflowCV.dll");
        if (!library->load()) {
            qDebug() << "Cannot load opticalflowCV.dll : " << library->errorString();
            qDebug() << "Will use chain tools instead";

            QString exepath = QString("opticalflowCV.exe");
            QFile file(exepath); qDebug() << "file exist ? : " << file.exists();
//            qDebug() << "exe path : " << exepath;
            if (!file.exists()) {
                return NULL;
            }
            m_process = new QProcess();

            int id = f1.lastIndexOf(".");
            if (id == -1) { id = f1.length(); }
            int id_b = f1.lastIndexOf("/");
            if (id_b == -1) { id_b = f1.lastIndexOf("\\"); }
            if (id_b == -1) { id_b = 0; }
            QString outFolder(outFolderCst);
            if (!(outFolder.endsWith("/") || outFolder.endsWith("\\"))) {
                outFolder += "/";
            }
            QString outName = f1.mid(id_b + 1, id) + suffix + f1.mid(id);
            QStringList args; args.append("interpolate"); args.append(f1); args.append(f2);
            args.append(outFolder + outName); args.append("-"); args.append(QString("%1").arg(factor));

            int exitCode;
            qDebug() << "execute : " << m_process->execute(exepath, args);
//            qDebug() << "error : " << m_process->errorString();
            m_process->waitForFinished();
//            qDebug() << "Output : " << QString(m_process->readAll());
            qDebug() << "exit code : " << (exitCode = m_process->exitCode());

            QImage* res = NULL;
//            if (exitCode == 0) {
//                res = new QImage(outName);
//            }
            delete m_process;
            m_process = NULL;
            return res;
        } else {
            qDebug() << "Library LOADED.";

            computeInterpolation = (computeInterpolationFunction )library->resolve("interpolate");

            if (!computeInterpolation) {
                qDebug() << "Cannot find \"computeFlow\" signature in opticalflowCV.dll";
                return NULL;
            }
            m_optflowLib = library;
        }
    }
    //compute the optical flow
    if (m_optflowLib != NULL ) { return computeInterpolation(*frame1, *frame2, factor, f1); }
    return NULL;
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

QImage* OpticalFlowTools::computeFlow(const QImage* frame1, const QImage* frame2, const QString& f1, const QString& f2)
{
    if (frame1 == NULL || frame2 == NULL) {
        return NULL;
    }

    //try to load dll
    if (m_process == NULL && m_optflowLib == NULL) {
        QString libpath = "../../build-opticalflowCV-Desktop_Qt_5_1_1_MSVC2010_32bit_OpenGL-Debug/debug/";
        QLibrary* library = new QLibrary(libpath + "opticalflowCV.dll");
        if (!library->load()) {
            qDebug() << "Cannot load opticalflowCV.dll : " << library->errorString();
            qDebug() << "Will use chain tools instead";

            QString exepath = QString("../build-opticalflowCV-Desktop_Qt_5_1_1_MSVC2010_32bit_OpenGL-Debug/debug/") + "opticalflowCV.exe";
            QFile file(exepath); qDebug() << "file exist ? : " << file.exists();
            qDebug() << "exe path : " << exepath;
            if (!file.exists()) {
                return NULL;
            }
            m_process = new QProcess();

            QString outName("flow.jpg");
            QStringList args; args.append("flow"); args.append(f1); args.append(f2); args.append(outName);
            if (m_computationMod == GPU) {
                args.append("GPU");
            } else if (m_computationMod == CPU) {
                args.append("CPU");
            } else {
                args.append("Matlab");
            }

            int exitCode;
            qDebug() << "execute : " << m_process->execute(exepath, args);
            qDebug() << "error : " << m_process->errorString();
            m_process->waitForFinished();
            qDebug() << "Output : " << QString(m_process->readAll());
            qDebug() << "exit code : " << (exitCode = m_process->exitCode());

            QImage* res = NULL;
            if (exitCode == 0) {
                res = new QImage(outName);
            }
            delete m_process;
            m_process = NULL;
            return res;
        } else {
            qDebug() << "Library LOADED.";

            if (m_computationMod == GPU) {
                computeOptFlow = (computeOptflowFunction )library->resolve("computeFlow");
            } else if (m_computationMod == CPU) {
                computeOptFlow = (computeOptflowFunction )library->resolve("computeFlowCPU");
            } else {
                qDebug() << "Computation mod not implemented";
                return NULL;
            }

            if (!computeOptFlow) {
                qDebug() << "Cannot find \"computeFlow\" signature in opticalflowCV.dll";
                return NULL;
            }
            m_optflowLib = library;
        }
    }
    //compute the optical flow
    if (m_optflowLib != NULL ) { return computeOptFlow(*frame1, *frame2, f1); }
    return NULL;
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

