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
    QImage *seekSpecifiedFrame(); //TODO
    /*
     * http://stackoverflow.com/questions/504792/ffmpeg-av-seek-frame
     * http://dranger.com/ffmpeg/functions.html#av_seek_frame
     */

    void setOptUseMemcpy(bool value);
    void cleanMem();

    int getFramesToSkip() const;
    void setFramesToSkip(int value);

    int getCurrentFrameIndex() const;

private:
    QString filename;
    AVFormatContext* pFormatContext;
    AVCodecContext* pCodecContext;

    AVPacket* packet;
    AVFrame* frame;
    AVFrame* frameDst;
    uint8_t* buffer;

    int videoStream;
    int audioStream;
    int framesToSkip;
    bool optUseMemcpy;

    unsigned curFrame;

    SwsContext* pSwsContext;
};

#endif // VIDEOTOOLS_H
