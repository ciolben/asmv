/*
 * LibAV docs: http://libav.org/doxygen/master/avformat_8h.html
 * Tutorial: http://dranger.com/ffmpeg/tutorial01.html
 */

#include "videotools.h"
#include <QDebug>

VideoTools::VideoTools()
    : pFormatContext(NULL)
    , pCodecContext(NULL)
    , videoStream(-1)
    , audioStream(-1)
    , duration(0)
    , curFrame(0)
    , curDts(0)
    , lastDts(0)
    , curTs(0)
    , framesToSkip(0)
    , optUseMemcpy(true)
{
    //don
}

/*
 * Test with QMediaPlayer : horrible
 *  don't run most of videos
 *  don't display easily metadata
 *  not easy to go frame by frame
 */
/*void VideoTools::getMediaInfo(const QString &file)
{

    QMediaPlayer player = new QMediaPlayer();
    player.setMedia(QMediaContent(QUrl::fromLocalFile(file)));
    player.play();
    QMediaResource resource = player.media().canonicalResource();
    qDebug() << "a_bitrate : " << resource.audioBitRate();
    qDebug() << "other prop : " << resource.videoBitRate();

}*/
void VideoTools::getMediaInfo(const QString &file) {

}

/*
 * Test with ffmpeg version of 18.09.13 (32bits), qt. 5.1.1 ok
 */
int VideoTools::testFfmpeg(const QString &qfile)
{
    av_register_all();

    QByteArray qbfile = qfile.toLocal8Bit();
    const char* file = qbfile.constData();

    AVFormatContext* pFormatContext_tmp = avformat_alloc_context();

    int ret;
    if ((ret = avformat_open_input(&pFormatContext_tmp, file, NULL, NULL)) != 0) {
        qDebug("Could not open file %s.\n", file);
        return ret;
    }

    if (avformat_find_stream_info(pFormatContext_tmp, NULL) < 0) {
        qDebug("No stream information found.\n");
        return -2;
    }

    av_dump_format(pFormatContext_tmp, 0, file, 0);

    AVCodecContext *pCodecContext;
    int videoStream = -1;
    int nbstream = int (pFormatContext_tmp->nb_streams);
    for (int i = 0; i < nbstream; i++) {
        if (pFormatContext_tmp->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoStream = i;
            pCodecContext = pFormatContext_tmp->streams[i]->codec;
            AVRational fps = pFormatContext_tmp->streams[i]->r_frame_rate;
            qDebug("Frame rate: %d/%d = %f\n", fps.num, fps.den, (float)fps.num / fps.den);
        }
    }

    avformat_free_context(pFormatContext_tmp);
    return 0;
}

int VideoTools::initFfmpeg(const QString &qfile)
{
    av_register_all();

    QByteArray qbfile = qfile.toLocal8Bit();
    const char* file = qbfile.constData();

    if (pFormatContext != NULL) {
        qDebug() << "Old context replaced !\n";
        avformat_free_context(pFormatContext);
    }

    //init context
    pFormatContext = avformat_alloc_context();
    if (avformat_open_input(&pFormatContext, file, NULL, NULL) != 0) {
        qDebug("Could not open file %s.\n", file);
        return -1;
    }
    if (avformat_find_stream_info(pFormatContext, NULL) < 0) {
        qDebug("No stream information found.\n");
        return -2;
    }
    //av_dump_format(pFormatContext, 0, file, 0);

    //Find video stream (1st)
    //AUDIO_SUPPORT : futur support for audio
    unsigned i = 0;
    videoStream = -1;
    audioStream = -1;
    for (i; i < pFormatContext->nb_streams; i++){
        if (pFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO && videoStream < 0){
            videoStream = i;
        }
        #ifdef AUDIO_SUPPORT
        if (pFormatContext->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO && audioStream < 0){
            audioStream = i;
        }
        #endif
    }
    if (videoStream == -1){
       qDebug("No video stream found in %s!\n", file);
       return -3;
    }

    #ifdef AUDIO_SUPPORT
    if (audioStream == -1){
       qDebug("No audio stream found in %s!\n", file);
       return -4;
    }
    #endif

    //TODO audio processing

    // Get a pointer to the codec context for the video stream
    pCodecContext = pFormatContext->streams[videoStream]->codec;

    // Find the decoder for the video stream
    AVCodec* pCodec = avcodec_find_decoder(pCodecContext->codec_id);
    if (pCodec == NULL){
       qFatal("Unsupported codec [2]!\n");
       return -5;
    }

    // Open codec
    if (avcodec_open2(pCodecContext, pCodec, NULL) < 0){
       qFatal("Unsupported codec [3]!\n");
       return -6;
    }

    //Manage sw context
    pSwsContext = sws_alloc_context();

    //allocate frames
    frame      = avcodec_alloc_frame();
    frameDst   = avcodec_alloc_frame();

    //define a buffer
    // Determine required buffer size and allocate buffer
    int numBytes = avpicture_get_size(PIX_FMT_RGB24, pCodecContext->width, pCodecContext->height);
    buffer = new uint8_t[numBytes];

    // Assign appropriate parts of buffer to image planes in pFrameRGB
    avpicture_fill((AVPicture *)frameDst, buffer, PIX_FMT_RGB24,
        pCodecContext->width, pCodecContext->height);

    curFrame = 0;

    //save duration (ms)
    ulong secs = pFormatContext->duration / AV_TIME_BASE;
    ulong us = pFormatContext->duration % AV_TIME_BASE;
    ulong l = secs*1000 + us/1000;
    duration = l;

    return 0;
}

void freeResources(AVPacket* packet, AVCodecContext* ctx, AVFrame* frame1, AVFrame* frame2) {
    //avcodec_default_release_buffer(ctx, frame1);
    //av_freep(frame1);
   // av_freep(frame2);
   // avcodec_free_frame(&frame1);
    //avcodec_default_release_buffer(ctx, frame2);
   // avcodec_free_frame(&frame2);
    av_free_packet(packet);
    //delete frame1;
    //delete frame2;
    delete packet;
}

///
/// \brief VideoTools::seekNextFrame
/// Method is unsynchronized.
/// \return
///
QImage* VideoTools::seekNextFrame()
{
    if (pFormatContext == NULL || pCodecContext == NULL) {
        qDebug("FFmpeg not initialized.");
        return NULL;
    }

    QImage* qImage      = NULL;
    AVPacket* packet = new AVPacket();
    if (av_read_frame(pFormatContext, packet) >= 0) {
        if (packet->stream_index == videoStream) {

            AVRational millisecondbase = {1, 1000};

            //revise this part if going backward is allowed
            lastDts = curDts;
            curDts = packet->dts;

            curTs = av_rescale_q(packet->dts,pFormatContext->streams[videoStream]->time_base, millisecondbase);
//            qDebug(QString("frame %1 : dts = %2, tb = %3/%4, rescaled = %5").arg(
//                       QString("%1").arg(curFrame),
//                       QString("%1").arg(f),
//                       QString("%1").arg(pFormatContext->streams[videoStream]->time_base.num),
//                       QString("%1").arg(pFormatContext->streams[videoStream]->time_base.den),
//                       QString("%1").arg(t)).toLocal8Bit().constData());

            /* -----Some note from doc of ffmpeg------
             *
             *@warning The input buffer must be FF_INPUT_BUFFER_PADDING_SIZE larger than
             * the actual read bytes because some optimized bitstream readers read 32 or 64
             * bits at once and could read over the end.
             *
             * @warning The end of the input buffer buf should be set to 0 to ensure that
             * no overreading happens for damaged MPEG streams.
             *
             * @note You might have to align the input buffer avpkt->data.
             * The alignment requirements depend on the CPU: on some CPUs it isn't
             * necessary at all, on others it won't work at all if not aligned and on others
             * it will work but it will have an impact on performance.
             *
             * In practice, avpkt->data should have 4 byte alignment at minimum.
             *
             * @note Some codecs have a delay between input and output, these need to be
             * fed with avpkt->data=NULL, avpkt->size=0 at the end to return the remaining frames.
             *
             */

            int pic_ptr; //if non-zero : success
            avcodec_decode_video2(pCodecContext, frame, &pic_ptr, packet);
            if (pic_ptr == 0) {
                qDebug("Ignore : Unable to read frame %d.\n", pic_ptr);
                return NULL;
            } else {
                //TODO : make distinction bw useful/useless frames

                //rescaling stuff (yet just a template)
                //TODO : check if PIX_FMT_RGB24 is really generic
                /* TODO : choice of the filter
                 *  SWS_FAST_BILINEAR     1
                    SWS_BILINEAR          2
                    SWS_BICUBIC           4     arbitrarily chosen
                    SWS_X                 8
                    SWS_POINT          0x10
                    SWS_AREA           0x20
                    SWS_BICUBLIN       0x40
                    SWS_GAUSS          0x80
                    SWS_SINC          0x100
                    SWS_LANCZOS       0x200
                    SWS_SPLINE        0x400
                 */
                int w = pCodecContext->width;
                int h = pCodecContext->height;
                int w2 = w;
                int h2 = h;

                AVPixelFormat format = AV_PIX_FMT_RGB24;
                pSwsContext = sws_getCachedContext(pSwsContext, w, h, pCodecContext->pix_fmt, w2, h2,
                                                   format, SWS_BICUBIC, NULL, NULL, NULL);

                if (pSwsContext == NULL) {
                    qFatal("Conversion not possible !\n");
                    //TODO : skip conversion
                    freeResources(packet, pCodecContext, frame, frameDst);
                    return NULL;
                }

                int num_bytes = avpicture_get_size(format, w2, h2);
                uint8_t* frameDst_buffer = (uint8_t *)av_malloc(num_bytes*sizeof(uint8_t));
                avpicture_fill((AVPicture*)frameDst, frameDst_buffer, format, w2, h2);
                sws_scale(pSwsContext, frame->data, frame->linesize, 0, h,
                          frameDst->data, frameDst->linesize);

                qImage = new QImage(w, h, QImage::Format_RGB888); //RGB888 : need check (seems ok)

                //copy
                bool use_memcpy = true;
                if (use_memcpy) { //should be faster
                    for(int y = 0; y < h2; y++) {
                       memcpy(qImage->scanLine(y), frameDst->data[0] + y * frameDst->linesize[0], w2 * 3);
                    }
                } else {
                    unsigned char *src = (unsigned char *)frameDst->data[0];
                    for (int y = 0; y < h; y++)
                    {
                        QRgb *scanLine = (QRgb *)qImage->scanLine(y);
                        for (int x = 0; x < w; x++)
                        {
                            scanLine[x] = qRgb(src[3*x], src[3*x+1], src[3*x+2]); //ok I will not use it
                        }
                        src += frameDst->linesize[0];
                    }
                }

                av_free(frameDst_buffer);
                //we're done !
            }

        #ifdef AUDIO_SUPPORT
        } else if (packet.stream_index == audioStream) {

        #endif
        } else {
            
        }

        if (qImage != NULL) { curFrame++; }
        freeResources(packet, pCodecContext, frame, frameDst);
        return qImage; //TODO : return NULL if no change
    } else {
        //End of stream
        qDebug("End of stream reached (frame_nb : %d)", curFrame);
        freeResources(packet, pCodecContext, frame, frameDst);
        return NULL;
    }
}

void VideoTools::setOptUseMemcpy(bool value)
{
    optUseMemcpy = value;
}

void VideoTools::cleanMem()
{
    //test of mem cleaning
    if (buffer) {
        delete [] buffer;
    }

    if(frame) {
        av_free(frame);
    }

    if(frameDst) {
        av_free(frameDst);
    }

    avcodec_close(pCodecContext);
    av_close_input_file(pFormatContext);
}

///
/// \brief VideoTools::getCurrentFrameIndex
/// The frame that is last decoded, does not count NULL frames.
/// \return
///
int VideoTools::getCurrentFrameIndex() const {
    return curFrame;
}

int64_t VideoTools::getDuration() const
{
    return duration;
}

int VideoTools::getDurationMs() const {
    return duration;
}

int VideoTools::getFramesToSkip() const
{
    return framesToSkip;
}

void VideoTools::setFramesToSkip(int value)
{
    framesToSkip = value;
}

int64_t VideoTools::getCurrentDts() const {
    return curDts;
}

int64_t VideoTools::getCurrentTs() const {
    return curTs;
}

///
/// \brief VideoTools::isCurrentFrameValid
/// \return true if the current frame contains new data, false otherwise.
///
bool VideoTools::isCurrentFrameValid() const
{
    return curDts > lastDts;
}





