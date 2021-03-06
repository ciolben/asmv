#ifndef OPTICALFLOWCV_H
#define OPTICALFLOWCV_H

#include "opticalflowcv_global.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/gpu/gpu.hpp>

#include <QImage>

using namespace cv;
using namespace cv::gpu;

extern "C" OPTICALFLOWCVSHARED_EXPORT QImage* computeFlow(const QImage& frame1, const QImage& frame2, const QString &basefilename);
extern "C" OPTICALFLOWCVSHARED_EXPORT QImage* computeFlowCPU(const QImage& frame1, const QImage& frame2, const QString &basefilename);
extern "C" OPTICALFLOWCVSHARED_EXPORT QImage* interpolate(const QImage& frame1, const QImage& frame2, const float factor, const QString& basefilename);
extern "C" OPTICALFLOWCVSHARED_EXPORT QImage* interpolateCPU(const QImage& frame1, const QImage& frame2, const float factor, const QString& basefilename);
extern "C" OPTICALFLOWCVSHARED_EXPORT QString* getGPUinfo();

QImage *Mat2QImage(Mat const& src, bool reversedRGB = true);
Mat QImage2Mat(QImage const& src);

Mat getColorField(Mat &imgU, Mat &imgV, Mat &imgColor);
void drawColorField(Mat &imgU, Mat &imgV, Mat &imgColor);
void hsv2rgb(float h, float s, float v, unsigned char &r, unsigned char &g, unsigned char &b);

#endif // OPTICALFLOWCV_H
