#include "opticalflowcv.h"

#include "broxflow.hpp"
#include <QImageWriter>
#include <QDebug>
#include <QFile>
#include <QTextStream>

#if defined(OPTICALFLOWCV_LIBRARY)
#else
//for chaining tools, not as fast as dll build, because exe as to be call
//for each pair of frame.
//arg : mod[flow|interpolate], frame1, frame2, out, type=CPU[GPU|Matlab], interpfactor=0
int main(int argc, char *argv[])
{
    QFile file ("log.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);

    short mod = -1;
    QString s_mod(argv[1]);
    if (s_mod.compare("flow") == 0) {
        mod = 1;
    } else if (s_mod.compare("interpolate") == 0) {
        mod = 2;
    }
    if (mod == -1) {
        out << "Unrecognized mod.\n";
        std::cout << "Unrecognized mod." << std::endl;
    }

    if (mod == -1 || (argc != 5 && argc != 6 && argc != 7)) {
        std::cout << "args : mod[flow|interpolate], frame1, frame2, out, type=CPU[GPU|Matlab], interpfactor=0" << std::endl;
        return -1;
    }

    out << argv[1] << " " << argv[2] << " " << argv[3] << " " << argv[4] <<" ";

    QString type("CPU");
    if (argc > 5) {
        out << argv[5] << " ";
        type = QString(argv[5]);
    }

    float interp = 0.f;
    if (argc > 6) {
        out << argv[6];
        bool ok;
        interp = QString(argv[6]).toFloat(&ok);
        if (!ok) {
            interp = 0;
            out << " (cannot convert : will use 0 -> no interp)";
        }
    }
    out << "\n";

    QImage frame1; bool ok = frame1.load(argv[2]);
    if (!ok) {
        std::cout << "frame1 does not exists" << std::endl;
        out << "frame1 does not exist.\n";
        return -1;
    }
    QImage frame2; ok = frame2.load(argv[3]);
    if (!ok) {
        std::cout << "frame2 does not exists" << std::endl;
        out << "frame2 does not exist.\n";
        return -1;
    }

    QImage* flow;
    QFile basefile(argv[2]);
    QString basefilename = basefile.fileName();

    //----------------------------------------------------flow mod
    if (mod == 1) {
        if (type.compare("CPU") == 0) {
            flow = computeFlowCPU(frame1, frame2, basefilename);
        } else if (type.compare("GPU") == 0) {
            flow = computeFlow(frame1, frame2, basefilename);
        } else if (type.compare("Matlab") == 0) {
            std::cout << "Matlab not yet implemented" << std::endl;
            out << "Matlab not yet implemented\n";
            return -2;
        } else {
            std::cout << "Unknown computation type";
            out << "Unknown computation type\n";
            return -2;
        }

        if (flow == NULL) {
            std::cout << "Error while computing flow." << std::endl;
            out << "Error while computing flow.\n";
            return -3;
        }

        //pipeline bw any application for visualizing the flow
        QString filename(argv[4]);
        QImageWriter writer(filename);
        if(!writer.write(*flow))
        {
            qDebug() << writer.errorString() << "\n will use opencv instead of Qt.";
            //try to use opencv instead
            Mat cvflow = QImage2Mat(*flow);
            if (!imwrite(filename.toStdString(), cvflow)) {
                qDebug() << "Cannot save the file with opencv";
                std::cout << "Cannot save the file" << std::endl;
                out << "Cannot save the file\n";
                return -4;
            } else {
                qDebug() << "Save ok.";
            }
        }

    }
    //----------------------------------------------------interpolation mod
    else {
        if (interp == 0) {
            std::cout << "Interpolation factor is 0" << std::endl;
            out << "Interpolation factor is 0\n";
            return -5;
        }

        Mat fx, fy, bx, by;
        short compmod = readMatrices(basefilename.toStdString(), fx, fy, bx, by);

        Mat res;
        switch(compmod) {
        case 0: //gpu -> brox (OK, better quality in general)
            interpFrames(QImage2Mat(frame1), QImage2Mat(frame2), res, fx, fy, bx, by, interp);
            break;
        case 1: //cpu -> farneback (OK)
            interpFramesCPU(QImage2Mat(frame1), QImage2Mat(frame2), res, fx, fy, interp);
            break;
        }

        QImage* wrap = Mat2QImage(res, (compmod == 1) ? false : true);
        QString filename(argv[4]);
        QImageWriter writer(filename);
        if(!writer.write(*wrap))
        {
            qDebug() << writer.errorString() << "\n will use opencv instead of Qt.";
            //try to use opencv instead
            if (!imwrite(filename.toStdString(), res)) {
                qDebug() << "Cannot save the file with opencv";
                std::cout << "Cannot save the file" << std::endl;
                out << "Cannot save the file\n";
                return -4;
            } else {
                qDebug() << "Save ok.";
                out << "Saved with OpenCV.\n";
            }
        }
    }

    out << "OK\n";
    return 0;
}
#endif

QString* getGPUinfo() {
    // Show CUDA information
    cv::gpu::printShortCudaDeviceInfo(cv::gpu::getDevice());
    return NULL;
}


static void drawOptFlowMap(const Mat& flow, Mat& cflowmap, int step, double, const Scalar& color) {
    for(int y = 0; y < cflowmap.rows; y += step)
        for(int x = 0; x < cflowmap.cols; x += step)
        {
            const Point2f& fxy = flow.at<Point2f>(y, x);
            line(cflowmap, Point(x,y), Point(cvRound(x+fxy.x), cvRound(y+fxy.y)),
                 color);
            circle(cflowmap, Point(x,y), 2, color, -1);
        }
}

///
/// \brief computeFlow BROX on GPU
/// \param frame1
/// \param frame2
/// \return
///
QImage* computeFlow(const QImage &frame1, const QImage &frame2, const QString& basefilename) {
    //convert qImage to mat

    Mat image1 = QImage2Mat(frame1);
    Mat image2 = QImage2Mat(frame2);

    //compute flow forward
    Mat flowUf, flowVf;
    broxOpticalFlow(image1, image2, flowUf, flowVf);

    //compute flow backward
    Mat flowUb, flowVb;
    broxOpticalFlow(image2, image1, flowUb, flowVb);

    //save flows
    saveMatrices(basefilename.toStdString(), 0, flowUf, flowVf, flowUb, flowVb);

    //combine flow x y for forward only
    Mat flow = cv::Mat(Size(image1.cols, image1.rows),CV_8UC3);
    drawColorField(flowUf, flowVf, flow);

//        namedWindow("a",CV_WINDOW_NORMAL);
//        namedWindow("flow",CV_WINDOW_NORMAL);
//        imshow("a", image1);
//        imshow("flow", flow);
//        waitKey();
    //return qimage
    return Mat2QImage(flow);
}

QImage* computeFlowCPU(const QImage &frame1, const QImage &frame2, const QString &basefilename) {
    Mat image1 = QImage2Mat(frame1);
    Mat image2 = QImage2Mat(frame2);

    //compute flow forward
    Mat flowF;
    farnebackOpticalFlowCPU(image1, image2, flowF);

    //compute flow backward
    Mat flowB;
    farnebackOpticalFlowCPU(image2, image1, flowB);

    //save flow
    saveMatrices(basefilename.toStdString(), 1, flowF, flowB);

    //Visualization for forward flow only
    Mat visual;
    image1.copyTo(visual);
    //cvtColor(im1gray, visual, CV_GRAY2BGR);
    drawOptFlowMap(flowF, visual, 16, 1.5, CV_RGB(0, 255, 0));

    return Mat2QImage(visual, false);
}



QImage* Mat2QImage(cv::Mat const& src0, bool reversedRGB)
{
    Mat src1;
    if (reversedRGB) {
        cvtColor(src0, src1, CV_BGR2RGB);
    } else {
        src1 = src0;
    }

    CvMat* src = new CvMat(src1);

//    namedWindow( "result", CV_WINDOW_AUTOSIZE );
//    imshow("result", *src);
//    waitKey();

//    QImage res0 = QImage(src.data, src.cols, src.rows,
//                             src.step, QImage::Format_ARGB6666_Premultiplied).copy();
//    //copy to a pointer
//    QImage* res = new QImage(res0);
//    res->detach();
//    return res;

    int origin = 0;

    CvMat* image2Draw_mat = cvCreateMat(src->rows, src->cols, CV_8UC3);
    QImage* image2Draw_qt = new QImage(image2Draw_mat->data.ptr, image2Draw_mat->cols
                           , image2Draw_mat->rows, image2Draw_mat->step, QImage::Format_RGB888);

    cvConvertImage(src, image2Draw_mat, (origin != 0 ? CV_CVTIMG_FLIP : 0) + CV_CVTIMG_SWAP_RB);
    //cvtColor(src, *image2Draw_mat, CV_BGR2RGB);
    return image2Draw_qt;

//     cv::Mat temp; // make the same cv::Mat
//     cvtColor(src, temp,CV_BGR2RGB); // cvtColor Makes a copt, that what i need
//     QImage dest((uchar*) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
//     QImage* dest2 = new QImage(dest);
//     dest2->detach(); // enforce deep copy
//     return dest2;

    //src1.copyTo(*src);

    //return new QImage((uchar*)src->data, src->cols, src->rows, src->step, QImage::Format_RGB888);

//    double scale = 255.0;
//    QImage* dest = new QImage(src0.cols, src0.rows, QImage::Format_ARGB32);
//    for (int y = 0; y < src0.rows; ++y) {
//            const double *srcrow = src0[y];
//            QRgb *destrow = (QRgb*)dest->scanLine(y);
//            for (int x = 0; x < src0.cols; ++x) {
//                    unsigned int color = srcrow[x] * scale;
//                    destrow[x] = qRgba(color, color, color, 255);
//            }
//    }
//    return dest;
}

cv::Mat QImage2Mat(QImage const& src)
{
    cv::Mat mat = cv::Mat(src.height(), src.width(), CV_8UC4, (uchar*)src.bits(), src.bytesPerLine());
    cv::Mat mat2 = cv::Mat(mat.rows, mat.cols, CV_8UC3 );
    int from_to[] = { 0,0,  1,1,  2,2 };
    cv::mixChannels( &mat, 1, &mat2, 1, from_to, 3 );
    return mat2;
}

void drawColorField(Mat &imgU, Mat &imgV, Mat &imgColor)
{
    Mat imgColorHSV = cv::Mat::zeros(Size(imgColor.cols,imgColor.rows),CV_32FC3);

    float max_s = 0;
    float *hsv_ptr, *u_ptr, *v_ptr;
    unsigned char *color_ptr;
    unsigned char r = 0, g = 0, b = 0;
    float angle = 0.0;
    float h = 0.0, s = 0.0, v = 0.0;
    float deltaX = 0.0, deltaY = 0.0;
    int x = 0, y = 0;

    // Generate hsv image
    for( y = 0; y < imgColor.rows; y++ )
    {
        hsv_ptr = imgColorHSV.ptr<float>(y);
        u_ptr = imgU.ptr<float>(y);
        v_ptr = imgV.ptr<float>(y);

        for( x = 0; x < imgColorHSV.cols; x++)
        {
             deltaX = u_ptr[x];
             deltaY = -v_ptr[x];
             angle = atan2(deltaY,deltaX);

             if( angle < 0)
             {
                angle += 2*M_PI;
             }

             hsv_ptr[3*x] = angle * 180 / M_PI;
             hsv_ptr[3*x+1] = sqrt(deltaX*deltaX + deltaY*deltaY);
             hsv_ptr[3*x+2] = 0.9;

             if( hsv_ptr[3*x+1] > max_s )
             {
                 max_s = hsv_ptr[3*x+1];
             }
        }
    }

     // Generate color image
    for(y = 0; y < imgColor.rows; y++ )
    {
        hsv_ptr = imgColorHSV.ptr<float>(y);
        color_ptr = imgColor.ptr<unsigned char>(y);

        for( x = 0; x < imgColor.cols; x++)
        {
              h = hsv_ptr[3*x];
              s = hsv_ptr[3*x+1] / max_s;
              v = hsv_ptr[3*x+2];

              hsv2rgb(h,s,v,r,g,b);

              color_ptr[3*x] = b;
              color_ptr[3*x+1] = g;
              color_ptr[3*x+2] = r;
       }
    }

    //drawLegendHSV(imgColor,15,25,15);
}

/** This function calculates rgb values from hsv color space                     */
void hsv2rgb(float h, float s, float v, unsigned char &r, unsigned char &g, unsigned char &b)
{
     float c = 0.0, hp = 0.0, hpmod2 = 0.0, x = 0.0;
     float m = 0.0, r1 = 0.0, g1 = 0.0, b1 = 0.0;

     if(h > 360)
     {
        h = h - 360;
     }

     c = v*s;   // chroma
     hp = h / 60;
     hpmod2 = hp - (float)((int)(hp/2))*2;

     x = c*(1 - fabs(hpmod2 - 1));
     m = v - c;

     if(0 <= hp && hp < 1)
     {
          r1 = c;
          g1 = x;
          b1 = 0;
     }
     else if(1 <= hp && hp < 2)
     {
          r1 = x;
          g1 = c;
          b1 = 0;
     }
     else if(2 <= hp && hp < 3)
     {
          r1 = 0;
          g1 = c;
          b1 = x;
     }
     else if(3 <= hp && hp < 4)
     {
          r1 = 0;
          g1 = x;
          b1 = c;
     }
     else if(4 <= hp && hp < 5)
     {
          r1 = x;
          g1 = 0;
          b1 = c;
     }
     else
     {
          r1 = c;
          g1 = 0;
          b1 = x;
     }

     r = (unsigned char)(255*(r1 + m));
     g = (unsigned char)(255*(g1 + m));
     b = (unsigned char)(255*(b1 + m));
}


QImage *interpolate(const QImage &frame1, const QImage &frame2, const float factor, const QString &basefilename) {
    Mat f1 = QImage2Mat(frame1);
    Mat f2 = QImage2Mat(frame2);
    Mat result;

    Mat _0_fx, _0_fy, bx, by;
    short computationMod = readMatrices(basefilename.toStdString(), _0_fx, _0_fy, bx, by);

    switch (computationMod) {
    case 0: //GPU
        interpFrames(f1, f2, result, _0_fx, _0_fx, bx, by, factor);
        break;
    case 1: //CPU
        interpFramesCPU(f1, f2, result, _0_fx, _0_fx, factor);
        break;
    default:
        return NULL;
    }

    return Mat2QImage(result, (computationMod == 1) ? false : true);
}

//if saved format is not farneback, the wrap image will be undefined
QImage *interpolateCPU(const QImage &frame1, const QImage &frame2, const float factor, const QString &basefilename) {
    Mat f1 = QImage2Mat(frame1);
    Mat f2 = QImage2Mat(frame2);
    Mat result;

    Mat flowF, flowB, empty;
    readMatrices(basefilename.toStdString(), flowF, flowB, empty, empty);

    interpFramesCPU(f1, f2, result, flowF, flowB, factor);

    return Mat2QImage(result, false);
}
