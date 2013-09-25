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
    , curFrame(0)
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

    curFrame = 0;
    return 0;
}

QImage* VideoTools::seekNextFrame()
{
    if (pFormatContext == NULL || pCodecContext == NULL) {
        qDebug("FFmpeg not initialized.");
        return NULL;
    }

    QImage* qImage      = NULL;
    AVFrame* frame      = avcodec_alloc_frame();
    AVFrame* frameDst   = avcodec_alloc_frame();
    AVPacket* packet = new AVPacket();
    if (av_read_frame(pFormatContext, packet) >= 0) {
        if (packet->stream_index == videoStream) {

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
                qDebug("Unable to read frame %d.\n", pic_ptr);
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

                pSwsContext = sws_getCachedContext(pSwsContext, w, h, pCodecContext->pix_fmt, w2, h2,
                                                   PIX_FMT_RGB24, SWS_BICUBIC, NULL, NULL, NULL);

                if (pSwsContext == NULL) {
                    qFatal("Conversion not possible !\n");
                    //TODO : skip conversion
                    return NULL;
                }

                int num_bytes = avpicture_get_size(PIX_FMT_RGB24, w2, h2);
                uint8_t* frameDst_buffer = (uint8_t *)av_malloc(num_bytes*sizeof(uint8_t));
                avpicture_fill((AVPicture*)frameDst, frameDst_buffer, PIX_FMT_RGB24, w2, h2);
                sws_scale(pSwsContext, frame->data, frame->linesize, 0, h,
                          frameDst->data, frameDst->linesize);

                qImage = new QImage(w, h, QImage::Format_RGB32); //RGB888 : need check

                //copy
                /*for(int y = 0; y < h; y++) {
                   memcpy(qImage.scanLine(y), frameDst->data[0] + y * frameDst->linesize[0], w * 3);
                }*/
                unsigned char *src = (unsigned char *)frameDst->data[0];
                for (int y = 0; y < h; y++)
                {
                    QRgb *scanLine = (QRgb *)qImage->scanLine(y);
                    for (int x = 0; x < w; x++)
                    {
                        scanLine[x] = qRgb(src[3*x], src[3*x+1], src[3*x+2]); //TODO revise this part
                    }
                    src += frameDst->linesize[0];
                }

                //we're done !
            }

            av_free_packet(packet);
        #ifdef AUDIO_SUPPORT
        } else if (packet.stream_index == audioStream) {

        #endif
        } else {
            av_free_packet(packet);
        }

        curFrame++;
        return qImage; //TODO : return NULL if no change
    } else {
        //End of stream
        qDebug("End of stream reached (frame_nb : %d)", curFrame);
        return NULL;
    }
}



