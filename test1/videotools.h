#ifndef VIDEOTOOLS_H
#define VIDEOTOOLS_H

#include <QString>
#include <QImage>

extern "C" {
    #include "libavcodec/avcodec.h"
    #include "libavformat/avformat.h"
    #include "libswscale/swscale.h"
}

//#include <QtMultimedia>

//http://qt-project.org/doc/qt-5.1/qtmultimedia/multimediaoverview.html

class VideoTools
{
public:
    VideoTools();
    static void getMediaInfo(const QString &file);
    static int testFfmpeg(const QString &file);

    int initFfmpeg(const QString &qfile);
    QImage *seekNextFrame();

private:
    QString filename;
    AVFormatContext* pFormatContext;
    AVCodecContext* pCodecContext;

    int videoStream;
    int audioStream;

    unsigned curFrame;

    SwsContext* pSwsContext;
};

#endif // VIDEOTOOLS_H
