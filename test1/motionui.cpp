#include "motionui.h"
#include "ui_motionui.h"

#include <QFile>
#include <QDir>
#include <QProcess>

MotionUi::MotionUi(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MotionUi),
    m_thread(NULL)
{
    ui->setupUi(this);
    //path is ./
    QFile fileM2d("Motion2D.exe");
    QFile fileWFlow("wflow.exe");
    bool ok = true;
    if (!fileM2d.exists()) {
        logText("Motion2D cannot be found in ", "red");
        logText("Motion2D.exe.", "", false, true);
        ok = false;
    }
    if (!fileWFlow.exists()) {
        logText("wflow.exe cannot be found in ", "red");
        logText("wflow.exe.", "", false, true);
        ok = false;
    }
    if (ok) {
        logText("Ready to compute motion estimation.", "blue");
    } else {
       logText("Fix the problem and launch again this dialog.");
    }
}

MotionUi::~MotionUi()
{
    if (m_thread != NULL) {
        m_thread->close();
        m_thread->exit();
        m_thread->wait();
        delete m_thread;
    }
    delete ui;
}

void MotionUi::setVideoSource(const QString &source)
{
    //ui->txtSource->setText(source);
    ui->txtSource->setText("C:/Users/Loic/Coding_Main/ADM/test1/snow1.mp4");
}

void MotionUi::logText(const QString &text, const QString &color, bool bold, bool italic)
{
    QString toappend = text;
    if (!color.isEmpty()) {
        toappend = "<font color=\"" + color + "\">" + toappend + "</font>";
    }
    if (bold) {
        toappend = "<b>" + toappend + "</b>";
    }
    if (italic) {
        toappend = "<i>" + toappend + "</i>";
    }
    ui->txtOut->append(toappend);
}

void MotionUi::on_btStart_clicked()
{
    if (m_thread != NULL) {
        logText("Closing previous work");
        m_thread->close(); m_thread->exit(); m_thread->wait();
        delete m_thread;
    }

    logText("Started", "green", false, true);

    m_thread = new MotionThread(ui->txtSource->text());
    m_thread->setSteps( ((ui->chkAffine->isChecked()) ? MotionThread::Affine : MotionThread::None)
                      | ((ui->chkwflow->isChecked()) ? MotionThread::wflow : MotionThread::None)
                      | ((ui->chkProfiling->isChecked()) ? MotionThread::Profile : MotionThread::None));
    m_thread->setOthers( (ui->chkWriteMotion->isChecked()) ? MotionThread::WriteMotion: MotionThread::NoOther);
    if (ui->rdAfflow->isChecked()) { m_thread->addFilesFilters("afflow"); }
    if (ui->rdWflow->isChecked()) { m_thread->addFilesFilters("wflow"); }
    if (ui->rdBoth->isChecked()) { m_thread->addFilesFilters("afflow"); m_thread->addFilesFilters("wflow"); }
    m_thread->setSmootingIntensity(ui->slSmooth->value());
    connect(m_thread, &MotionThread::logText, this, &MotionUi::logText);

    //forward signal
    connect(m_thread, &MotionThread::motionProfileComputed, this, &MotionUi::motionProfileComputed);

    m_thread->start();
}

void MotionUi::closeEvent(QCloseEvent*)
{
    emit windowClosed("motion");
}
