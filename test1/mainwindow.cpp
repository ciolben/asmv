#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QScrollBar>
#include <QTime>
#include <QThread>

#include "opticalflowtools.h"

#include "qmlregister.h"
#include "mathlib/bsplinefitter.h"
#include "mathlib/filtering.h"
#include "utils/filesutils.h"

#include <QtQuick/QQuickView>

#include <stdio.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , worker(NULL)
  , imageEater(NULL)
  , spline(NULL)
  , m_optflowtools(NULL)
  , timer(this)
  , m_interpUi(NULL)
  , m_motionUi(NULL)
{
    ui->setupUi(this);
    connect(&timer, &QTimer::timeout, this, &MainWindow::handleTimeout);
    spline = (SplineDrawer*)QMLRegister::getQMLObject("spline");

    qRegisterMetaType<std::vector<float> >("std::vector<float>");

    ui->txtFit->setText(QString::number(1));
}

MainWindow::~MainWindow()
{
    if(worker != NULL) {
        worker->close();
    }
    if(m_interpUi != NULL) { delete m_interpUi; }
    if(m_motionUi != NULL) { delete m_motionUi; }
    delete ui;
}

void MainWindow::handleResult(const QString *res)
{
    logText(res);
//    char buff[100];
//    sprintf_s(buff, "current dts : %d (%d)", vtools.getCurrentDts(), vtools.getCurrentTs());
//    QString* result = new QString(buff);
//    logText(result);
}

void MainWindow::handleNewValidFrame(qlonglong time)
{
    //SplineDrawer* spline = (SplineDrawer*)QMLRegister::getQMLObject("spline");
    //spline->addKey(time, time);
   // logText(&QString("ts : %1").arg(time));
}

///
/// \brief MainWindow::threadFinished
///Worker has finished.
void MainWindow::threadFinished()
{
    timer.stop();
    worker = NULL;
    imageEater = NULL;
}

void MainWindow::handleImageEaten()
{
    /* don */
}

void MainWindow::handleTimeout()
{
    //routines
    if(imageEater != NULL) {
        ui->pbBuffer->setValue(imageEater->getBufferUtilization());
        logText(&QString("current ts : %1").arg(vtools.getCurrentTs()));
    }

    if(spline != NULL) {
        spline->setplayposition(vtools.getCurrentTs());
    } else {
        //try applying value
        spline = (SplineDrawer*)QMLRegister::getQMLObject("spline");
        if(spline == 0) {
            spline = NULL;
        }
    }
    //too heavy
//    SplineDrawer* spline = (SplineDrawer*)QMLRegister::getQMLObject("spline");
    //    spline->update();
}

void MainWindow::handleNeedSequences(QList<Sequence *>& sequences)
{
    if (spline != NULL) {
        sequences = spline->getSequences();
    }
}

void MainWindow::initializeNewProfile(const QString &file, std::vector<float> profile)
{
    m_currentProfile = profile;
    m_profile = profile;

    //ui stuff
    ui->txtFile->setText(file);
    ui->chkRemapped->setChecked(true);
    ui->sbReduction->setValue(0);
    ui->lblSplineInfo->setText("Profile loaded.");

    //reset videotools
    if (vtools.getFilename().compare(file) != 0) {
        vtools.initFfmpeg(file);
    }

    //set spTolerance to max value (so user have an idea)
    float max(filter::findAbsMax<float>(profile));
    ui->spTolerance->setValue(max / 2.f);

    loadMotionProfile(profile);
}

void MainWindow::loadMotionProfile(std::vector<float> profile
                                   , double keySimplificationFactor
                                   , bool recomputeAverage
                                   , float ampFactor)
{
    if (profile.empty()) { return; }

    //get duration and sample the space
    int duration = vtools.getDurationMs();
    double sampling = duration / profile.size();
    qDebug() << "duration : " << duration << ", nb keys : " << profile.size() << "time bw frames : " << sampling;

    //compute the main motion tendency
    float varianceCenter(0);
    if (recomputeAverage) {
        foreach (float f, profile) {
            varianceCenter += f;
        }
        varianceCenter /= profile.size();
    }

    //save filter points
    QList<std::pair<ulong, float>> filterPoints;
    if (!spline->getSequences().isEmpty()) {
        foreach (auto p, spline->getSequences().first()->extraPointsList)
        filterPoints.append(p);
    }

    //init spline
    spline->initView(duration);

    //set up sequence
    int seqId = spline->addSequence(0, duration);
    if (seqId == -1) {
        qDebug() << "Cannot modify motion profile.";
        return;
    }

    //setup filter points
    foreach (auto p, filterPoints) {
        spline->getSequences().first()->extraPointsList.append(p);
    }

    //create raw spline
    int count(0);
    float max(-10000), min(10000);
    foreach (float f, profile) {
        if (recomputeAverage) {
            float ratio = f / varianceCenter;
            float sign = -1.f;
            //check if range is 1 to inf
            if (ratio < 1) {
                //if not, need to convert from [0,1[ space to [1, inf] space
                ratio = varianceCenter / f;
                sign = 1.f;
            }

            ratio = sign * (ratio - 1.0) * ampFactor;
            if (ratio > max) { max = ratio; }
            if (ratio < min) { min = ratio; }

            spline->addKey(seqId, count * sampling, ratio);

        } else {
            float famp(f * ampFactor);
            if (famp > max) { max = famp; }
            if (famp < min) { min = famp; }
            spline->addKey(seqId, count * sampling,
                           famp);
        }
        count++;
    }

    //give curve hints
    ui->sbHigh->setValue(-min + 0.5);
    ui->sbLow->setValue(max + 0.5);

    //simplify curve
    if (keySimplificationFactor > 1 && profile.size() / keySimplificationFactor > 4) {
        float reductionFactor = keySimplificationFactor;
        int dimension = 2;
        int numSamples = profile.size();
        int degree = 1;
        int numCtrlPoints = profile.size() / reductionFactor;
        float* samples = (float*) malloc(numSamples * sizeof(float) * dimension);

        Sequence* seq = spline->getSequences().first(); //we know there is only one sequence at this time

        for (int i = 0; i < numSamples * dimension; i += dimension) {
            //x
            samples[i] = (int) i / dimension;
            //y
            samples[i + 1] = (float) seq->computeSpline(samples[i] * sampling);
        }

        std::pair<float*, char*> simplout = BSplineFitter::reduceKeys(numSamples, samples
                                                                      , degree, numCtrlPoints, true);
        float* simplified = simplout.first;
        spline->removeSequence(seqId);
        seqId = spline->addSequence(0, duration);

        for (int i = 0; i < numCtrlPoints * dimension; i += dimension) {
            int index = (int) simplified[i];
            spline->addKey(seqId, (ulong) index * sampling, simplified[i+1]);
        }

        QString errors(simplout.second);
        QStringList errList = errors.split(",");
        ui->lblSplineInfo->setText(QString("RMSD : %1, average distance : %2").arg(errList[0], errList[1]));

        delete []simplout.first;
        delete []simplout.second;
    }

    //update points
    spline->updatePoints();

}

void MainWindow::handleWindowDestroyed(const QString& windowName)
{
    if (windowName.compare("motion") == 0) {
        delete m_motionUi;
        m_motionUi = NULL;
    } else if (windowName.compare("flow") == 0) {
        delete m_optflowtools;
        m_optflowtools = NULL;
    } else if (windowName.compare("interpolation") == 0) {
        delete m_interpUi;
        m_interpUi = NULL;
    }
}

void MainWindow::on_btClose_clicked()
{
    if(worker != NULL) {
        worker->close();
    }
    QApplication::quit();
}


void MainWindow::on_btOpen_clicked()
{
    dc = 0;
    QString res = QFileDialog::getOpenFileName(this, "Open video file", QDir::currentPath());
    ui->txtFile->setText(res); 
}

//void MainWindow::initVtools(const QString& filename) {

//}

void MainWindow::on_btGo_clicked()
{
    if(worker != NULL) {
        return;
    }

    if (ui->chkRemapped->isChecked()) {
        //check if vtools is configured, if not, motion ui has probably not called
        //loadMotionProfile function

        if (!vtools.isConfigured()) {
            logText("Load motion profile.");
            ui->chkRemapped->setChecked(false);
            return;
        }

        on_btInterpolate_clicked();
        return;

    }
    QString txtContent = ui->txtFile->text();
    if (filename.isEmpty() || txtContent.compare(filename) != 0) {
        filename = txtContent;
        //VideoTools::getMediaInfo(res);
        //VideoTools::testFfmpeg(res);

        //TODO : deallocate resources if vtools already exists
        vtools = VideoTools();

        int out;
        out = vtools.initFfmpeg(filename);
        //qDebug("initFfmpeg : %d", out);
        logText(&QString("FFmpeg initialized. Video length : %1 ms").arg(vtools.getDurationMs()));

        //add two points for the spline
        spline = (SplineDrawer*)QMLRegister::getQMLObject("spline");

        spline->setduration(vtools.getDurationMs());
        spline->initView();
    } else {
        if (filename.isEmpty()) {
            logText("No source");
            return;
        }
    }

    QString outdir(getNameOfFile(filename) + "_Frames/");

    //interconnect elements
    vtools.setFramesToSkip(ui->txtSkipFrames->text().toInt());
    if (imageEater != NULL) { imageEater->close(); delete imageEater; }
    imageEater = new ImageEaterThread(this, ui->lblImage);
    imageEater->setRate(ui->slSpeed->value());
    ui->pbBuffer->setValue(0);
    imageEater->setBufferSize(ui->cboBuffer->currentText().toInt());
    ui->pbBuffer->setMaximum(ui->cboBuffer->currentText().toInt());
    WorkerThread *workerThread = new WorkerThread(this, ui->lblImage, &vtools, *imageEater);
    workerThread->setTiming(ui->txtFrame->text().toInt(), ui->txtDuration->text().toInt());
    workerThread->setOutputDir(outdir);
    connect(workerThread, &WorkerThread::resultReady, this, &MainWindow::handleResult);
    connect(workerThread, &WorkerThread::newValidFrame, this, &MainWindow::handleNewValidFrame);
    connect(workerThread, &WorkerThread::finished, workerThread, &QObject::deleteLater);
    connect(workerThread, &WorkerThread::finished, this, &MainWindow::threadFinished);

    //we don't need this one because finish event is handled in the workerThread
    //connect(imageEater, &ImageEaterThread::finished, imageEater, &QObject::threadFinished);

    connect(imageEater, SIGNAL(imageEaten()), this, SLOT(handleImageEaten()));

    //repaint
    connect(workerThread, SIGNAL(redraw()), ui->lblImage, SLOT(repaint()));
    //------
    workerThread->start();
    worker = workerThread;

    timer.start(500);
}

//void MainWindow::logText(const char* text) {
//    logText(&QString(text));
//}

void MainWindow::logText(const QString *text)
{
    QString plainText = ui->txtInfo->toPlainText();
    if (plainText.length() > 1000) {
        plainText.truncate(500);
    }
    ui->txtInfo->setPlainText(plainText + "\r\n" + *text);
    ui->txtInfo->verticalScrollBar()->setValue(ui->txtInfo->verticalScrollBar()->maximum());
}

void MainWindow::on_btFlow_clicked()
{

    m_optflowtools = OpticalFlowTools::createWindow(this, getNameOfFile(ui->txtFile->text()) + "_Frames/");
    if (spline != NULL) {
        m_optflowtools->setSequences(spline->getSequences());
    }

    /* QML version not used
     *
    OpticalFlowTools* m_optflowtools = (OpticalFlowTools*) QMLRegister::getQMLObject("optflowtools");
    optflowtools->initializeTools();
   */

    //tests
//    ui->->loadImages("img1.jpg", "img2.jpg");
//    //compute coarse2fine
//    QImage& image = *OpticalFlowTools::computeCoarse2Fine("car1.jpg", "car2.jpg");
//    //ui->wOpticalFlow->loadImOut(image);
//    ui->wOpticalFlow->loadImOut("flowout.jpg");
    //delete image;
}

void MainWindow::on_btTimeline_clicked()
{
    SplineDrawer* spline = (SplineDrawer*)QMLRegister::getQMLObject("spline");
    spline->beginAddSequence();

}

void MainWindow::on_slSpeed_sliderMoved(int position)
{
    if(imageEater != NULL) {
        imageEater->setRate(position);
    }
}

void MainWindow::on_cboBuffer_currentTextChanged(const QString &arg1)
{
    if(imageEater != NULL) {
        int value = arg1.toInt();
        imageEater->setBufferSize(value);
        ui->pbBuffer->setMaximum(value);
    }
}


void MainWindow::on_slSpeed_sliderReleased()
{
    logText(&QString("speed : %1").arg(ui->slSpeed->value()));
}

void MainWindow::on_btInterpolate_clicked()
{
    //only one interpolation ui is allowed
    if (m_interpUi != NULL) { return; }
    m_interpUi = new InterpolateUi(spline, this);
    m_interpUi->addBaseName(getNameOfFile(ui->txtFile->text()));
    connect(m_interpUi, &InterpolateUi::windowClosed, this, &MainWindow::handleWindowDestroyed);
    connect(m_interpUi, &InterpolateUi::needSequences, this, &MainWindow::handleNeedSequences
            , Qt::DirectConnection);
    m_interpUi->show();
}

void MainWindow::on_btMotion_clicked()
{
    //only one motion ui is allowed
    if (m_motionUi != NULL) { return; }
    m_motionUi = new MotionUi();

    connect(m_motionUi, &MotionUi::windowClosed, this, &MainWindow::handleWindowDestroyed);
    connect(m_motionUi, &MotionUi::motionProfileComputed, this, &MainWindow::initializeNewProfile);

    m_motionUi->setVideoSource(ui->txtFile->text());
    m_motionUi->show();
}

void MainWindow::on_chkRemapped_clicked()
{
    bool enabled = !ui->chkRemapped->isChecked();
    ui->txtFrame->setEnabled(enabled);
    ui->txtDuration->setEnabled(enabled);
    ui->txtSkipFrames->setEnabled(enabled);
}

void MainWindow::on_chkRemapped_stateChanged(int arg1)
{
    on_chkRemapped_clicked();
}

void MainWindow::on_sbReduction_valueChanged(double arg1)
{
    if (vtools.getFilename().isEmpty()) { return; }
    if (m_currentProfile.empty()) { return; }
    loadMotionProfile(m_currentProfile, arg1, ui->txtFit->text().toFloat());
}

void MainWindow::on_pbResetSpline_clicked()
{
    initializeNewProfile(vtools.getFilename(), m_profile);
}

void MainWindow::on_pbRemoveOutliers_clicked()
{
    filter::rescaleExcentricValues(m_currentProfile
                                               , (float) ui->spTolerance->value()
                                               , (double) ui->slOutliers->value() / 100.0);
    loadMotionProfile(m_currentProfile, ui->sbReduction->value(), true, ui->txtFit->text().toFloat());
}

void MainWindow::on_slOutliers_valueChanged(int value)
{
    QStringList parts = ui->lblSplineInfo->text().split("|");
    QString fpart = parts.at(0);
    ui->lblSplineInfo->setText(fpart
                               + "| cutoff : " + QString::number((float)value / 100.f));
}

void MainWindow::on_spTolerance_valueChanged(double arg1)
{
    QStringList parts = ui->lblSplineInfo->text().split("|");
    QString fpart = parts.at(0);
    ui->lblSplineInfo->setText(fpart
                               + "| tolerance : " + QString::number((float)arg1));
}

void MainWindow::on_btFilter_clicked()
{
    if (spline == NULL) { return; }
    if (spline->getSequences().isEmpty()) { return; }

    if (spline->isAddExtraPointEnded()) {
        spline->beginAddExtraPoint();
        return;
    }
}

void MainWindow::on_btApplyFilter_clicked()
{
    if (spline == NULL) { return; }
    if (spline->getSequences().isEmpty()) { return; }

    if (!spline->isAddExtraPointEnded()) {
        return;
    }

    Sequence* seq = spline->getSequences().first();
    pair<ulong, float> point(seq->extraPointsList.last());

    seq->extraPointsList.clear();
    seq->extraPointsList.append(point);

    //dump spline values to array for applying fitler on them
    vector<float> splineValues; splineValues.reserve(m_currentProfile.size());
    readSplineValues(splineValues, seq);

    //read params
    int mod = ui->dialMod->value();
    float fit = ((float)ui->dialFit->value() + 1.f) / (float)ui->dialFit->maximum();
    if (!ui->chkPlus->isChecked()) {
        fit *= 2.25f;
        fit += 1.f;
    }
    bool cut = ui->chkCut->isChecked();

    //apply filter
    filter::applyClocheFilter(splineValues
                              , point.first * m_currentProfile.size() / vtools.getDurationMs(), point.second, mod, fit, cut);
    loadMotionProfile(splineValues, 0, false);
    spline->updatePoints();
    ui->wTimeline->update();
}

void MainWindow::on_btFit_clicked()
{
    loadMotionProfile(m_currentProfile, ui->sbReduction->value(), true, ui->txtFit->text().toFloat());
}

void MainWindow::on_btUp_clicked()
{
    //move up the curve
    std::vector<float> splineValues; splineValues.reserve(m_currentProfile.size());
    readSplineValues(splineValues);
    for (auto it(splineValues.begin()); it != splineValues.end(); ++it) {
        *it -= 0.25f;
    }
    loadMotionProfile(splineValues, 0, false);
}

void MainWindow::on_btDown_clicked()
{
    //move down the curve
    std::vector<float> splineValues; splineValues.reserve(m_currentProfile.size());
    readSplineValues(splineValues);
    for (auto it(splineValues.begin()); it != splineValues.end(); ++it) {
        *it += 0.25f;
    }
    loadMotionProfile(splineValues, 0, false);
}

void MainWindow::readSplineValues(std::vector<float>& dest,  Sequence* seq) const {
    if (seq == NULL) { seq = spline->getSequences().first(); }
    if (seq == NULL) { return; }
    float sampling(spline->duration() / m_currentProfile.size());
    for (int i(0); i < m_currentProfile.size(); ++i) {
        //i must be transformed to video ms
        //then y is in spline coords
        dest.push_back(seq->computeSpline(i * sampling));
    }
}

void writeSplineValues(const std::vector<float>& src) {
    /* can be useful */
}

void MainWindow::on_btHighLow_clicked()
{
    //values are inversed : high is lowest value, and repsectively low is highest value.
    float high(-ui->sbHigh->value());
    float low(ui->sbLow->value());

    int size(m_currentProfile.size());
    std::vector<float> splineValues; splineValues.reserve(size);
    readSplineValues(splineValues);

    if (size < 3) { return; }
    for (auto it(splineValues.begin()); it != splineValues.end(); ++it) {
        if (*it < high) {
//            if (it != splineValues.begin()) {
//                *it = (*(it - 1) + *(it + 1)) / 2.f;
//            } else {
//                *it = *(it + 1);
//            }
            *it = high;
        } else if (*it > low) {
//            if (it != splineValues.end() - 1) {
//                *it = (*(it - 1) + *(it + 1)) / 2.f;
//            } else {
//                *it = *(it - 1);
//            }
            *it = low;
        }
    }

    loadMotionProfile(splineValues, ui->sbReduction->value(), false);
}
