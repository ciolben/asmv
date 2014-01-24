//=============================================================================
//
// brox_flow.cpp
// Main file for testing OpenCV GPU Brox Optical Flow
// Author: Pablo F. Alcantarilla
// Institution: ALCoV, Université d'Auvergne
// Date: 23/11/2012
// Email: pablofdezalc@gmail.com
//=============================================================================

// System Includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <math.h>
#include <iostream>
#include <fstream>

// OpenCV Includes
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/gpu/gpu.hpp>
#include <opencv2/video/video.hpp>

// Other Includes
#define M_PI 3.14159265359

//******************************************************************************
//******************************************************************************

// Namespaces
using namespace std;
using namespace cv;
using namespace cv::gpu;

// Some global variables for the optical flow
const float alpha_ = 0.12;
const float gamma_ = 5;
const float scale_factor_ = 0.9;
const int inner_iterations_ = 3;
const int outer_iterations_ = 50;
const int solver_iterations_ = 20;

//******************************************************************************
//******************************************************************************

/*
void remap(InputArray src, OutputArray dst, InputArray map1, InputArray map2, int interpolation, int borderMode=BORDER_CONSTANT, const Scalar& borderValue=Scalar())
*/
void saveMatrices(const string savepathbase, short mod, const Mat& mat0_xf, const Mat& mat0_yf, const Mat& matxb =Mat(), const Mat& matyb =Mat(), bool compress = true) {
    string suffix((compress) ? ".gz" : "");
    FileStorage file(savepathbase + ".yml" + suffix, FileStorage::WRITE);
    switch (mod) {
    case 0: //from Brox (CV_8UC1) x 4 -> Point2f (I save as is)
        file << "xf" << mat0_xf;
        file << "yf" << mat0_yf;
        file << "xb" << matxb;
        file << "yb" << matyb;
        break;
    case 1: //from Farneback (CV_32FC2) x 2 -> Point2f
        file << "flowF" << mat0_xf;
        file << "flowB" << mat0_yf;
        break;
    default:
        return;
    }

    file.release();
}

///
/// \brief readMatrices
/// \param mat0_xf
/// \param matyf
/// \param matxb
/// \param matyb
/// \param readpathbase
/// \param uncompress
/// \return 1 for Farneback format, 0 for Brox, -1 if error
///
short readMatrices(const string readpathbase, Mat& mat0_xf, Mat& mat0_yf, Mat& matxb, Mat& matyb, bool uncompress = true) {
    string suffix ((uncompress) ? ".gz" : "");
    FileStorage file(readpathbase + ".yml" + suffix, FileStorage::READ);
    Mat test;
    short type = -1;
    file["flowF"] >> test;
    if (!test.empty()) {
        mat0_xf = test;
        file["flowB"] >> mat0_yf;
        type = 1;
    } else {
        file["xf"] >> test;
        if (!test.empty()) {
            mat0_xf = test;
            file["yf"] >> mat0_yf;
            file["xb"] >> matxb;
            file["yb"] >> matyb;
            type = 0;
        }
    }
    file.release();
    return type;
}

/* TODO : interpolation can be very fast if done at this step */
void broxOpticalFlow(const Mat& image1, const Mat& image2, Mat& flowU, Mat& flowV)
{
    // Variables for CUDA Brox Optical flow
    GpuMat image1GPU, image2GPU, uGPU, vGPU;
    Mat image1Gray, image2Gray, image1Gray_32, image2Gray_32;
    int width, height;

    // Create the optical flow object
    cv::gpu::BroxOpticalFlow dflow(alpha_,gamma_,scale_factor_,inner_iterations_,outer_iterations_,solver_iterations_);

    //init
    //frame1_rgb = cv::Mat(Size(image1.cols,image1.rows),CV_8UC3);
    width = image1.cols;
    height = image1.rows;

//    namedWindow("a",CV_WINDOW_NORMAL);
//    namedWindow("b",CV_WINDOW_NORMAL);
//    imshow("a", image1);
//    imshow("b", image2);
//    waitKey();

    // Allocate memory for the images
    image1Gray = cv::Mat(Size(width,height),CV_8UC1);
    image2Gray = cv::Mat(Size(width,height),CV_8UC1);
    image1Gray_32 = cv::Mat(Size(width,height),CV_32FC1);
    image2Gray_32 = cv::Mat(Size(width,height),CV_32FC1);

//    imshow("a", image1Gray);
//    imshow("b", image2Gray);
//    waitKey();

    // Convert the image to grey and float
    cvtColor(image1,image1Gray,CV_BGR2GRAY);
    cvtColor(image2,image2Gray,CV_BGR2GRAY);
    image1Gray.convertTo(image1Gray_32,CV_32FC1,1.0/255.0,0);
    image2Gray.convertTo(image2Gray_32,CV_32FC1,1.0/255.0,0);

    // Upload images to the GPU
    image1GPU.upload(image1Gray_32);
    image2GPU.upload(image2Gray_32);

//    imshow("a", image1Gray);
//    imshow("b", image2Gray);
//    waitKey();

    // Do the dense optical flow
    dflow(image1GPU,image2GPU,uGPU,vGPU);

    //std::cout << "flowU type : " << flowU.type() << std::endl; --> flowU type : 0 (CV_8UC1)

    uGPU.download(flowU);
    vGPU.download(flowV);
}

void farnebackOpticalFlowCPU(const Mat& image1, const Mat& image2, Mat& flow)
{
    Mat im1gray, im2gray;
    cvtColor(image1, im1gray, CV_BGR2GRAY);
    cvtColor(image2, im2gray, CV_BGR2GRAY);

//    CvSize size; size.height = image1.rows; size.width = image1.cols;
//    fl = cvCreateImage(size, IPL_DEPTH_32F, 2);
   // cv::Mat _flow = cv::cvarrToMat(fl);
    cv::calcOpticalFlowFarneback(im1gray, im2gray, flow, 0.5, 3, 15, 3, 5, 1.2, 0);

    //std::cout << "flow type : " << flow.type() << std::endl; --> flow type : 13 (CV_32FC2)
//    std::cout << "flow type : " << CV_64FC1 << std::endl;
//    std::cout << "flow type : " << CV_64FC2 << std::endl;
//    std::cout << "flow type : " << CV_64FC3 << std::endl;
//    std::cout << "flow type : " << CV_64FC4 << std::endl;
//    std::cout << "flow type- : " << CV_32FC1 << std::endl;
//    std::cout << "flow type : " << CV_32FC2 << std::endl; /* 13 */
//    std::cout << "flow type : " << CV_32FC3 << std::endl;
//    std::cout << "flow type : " << CV_32FC4 << std::endl;
//    std::cout << "flow type- : " << CV_32SC1 << std::endl;
//    std::cout << "flow type : " << CV_32SC2 << std::endl;
//    std::cout << "flow type : " << CV_32SC3 << std::endl;
//    std::cout << "flow type : " << CV_32SC4 << std::endl;    

//    namedWindow("b",CV_WINDOW_NORMAL);
//    imshow("b", visual );
//    waitKey();
}

void interpFrames(const Mat& frameColor1_, const Mat& frameColor2_, Mat& result
            , const Mat& flowFx, const Mat& flowFy, const Mat& flowBx, const Mat& flowBy
            , const float interpFactor) {

    Mat frameColor1, frameColor2;
    frameColor1_.convertTo(frameColor1, CV_32F, 1.0 / 255.0);
    frameColor2_.convertTo(frameColor2, CV_32F, 1.0 / 255.0);

    GpuMat f1_r, f1_g, f1_b, f2_r, f2_g, f2_b;
    Mat channels[3];

    cv::split(frameColor1, channels);
    f1_r.upload(channels[0]);
    f1_g.upload(channels[1]);
    f1_b.upload(channels[2]);

    cv::split(frameColor2, channels);
    f2_r.upload(channels[0]);
    f2_g.upload(channels[1]);
    f2_b.upload(channels[2]);

    GpuMat ffx; ffx.upload(flowFx);
    GpuMat ffy; ffy.upload(flowFy);
    GpuMat fbx; fbx.upload(flowBx);
    GpuMat fby; fby.upload(flowBy);

    GpuMat rNew, gNew, bNew, newFrame;
    GpuMat buf;

    // interpolate blue channel
    interpolateFrames(f1_b, f2_b, ffx, ffy, fbx, fby, interpFactor, bNew, buf);

    // interpolate green channel
    interpolateFrames(f1_g, f2_g, ffx, ffy, fbx, fby, interpFactor, gNew, buf);

    // interpolate red channel
    interpolateFrames(f1_r, f2_r, ffx, ffy, fbx, fby, interpFactor, rNew, buf);

    //merge channels
    GpuMat channels3[] = {bNew, gNew, rNew};
    gpu::merge(channels3, 3, newFrame);

    newFrame.download(result);
}

void interpFramesCPU(const Mat& frame1, const Mat& frame2, Mat& result
            , const Mat& flowF, const Mat& flowB
            , const float interpFactor) {

    Mat mapForward(flowF.size(), flowF.type());
    Mat mapBackward(flowB.size(), flowB.type());

    //Rewrite with parallel_for_
    /*
    MatConstIterator_<Point2f> itF = mapForward.begin<Point2f>();
    MatConstIterator_<Point2f> itB = mapBackward.begin<Point2f>();
    MatConstIterator itResF = mapForward.begin();
    MatConstIterator itResB = mapBackward.begin();
    MatConstIterator itf1 = frame1.begin();
    MatConstIterator itf2 = frame1.begin();
    MatConstIterator itEnd = frame1.end();
    for (; itf1 != itEnd; ++itf1, ++itf2, ++itF, ++itB) {

    }
    */

    //rebuild mapping (offset -> coords)
    int sizex = frame1.rows, sizey = frame1.cols;
    for (int x = 0; x < sizex; x++) {
        for (int y = 0; y < sizey; y++) {
            Point2f ff = flowF.at<Point2f>(x, y);
            Point2f fb = flowB.at<Point2f>(x, y); //maybe need to inverse
            mapForward.at<Point2f>(x, y) = Point2f(y - ff.x * interpFactor,x - ff.y * interpFactor);
            mapBackward.at<Point2f>(x ,y) = Point2f(y - fb.x * (1.f - interpFactor),x - fb.y * (1.f - interpFactor));
        }
    }

    //interpolate
    Mat res1, res2, emptymap; //INTER_CUBIC
    cv::remap(frame1, res1, mapForward, emptymap, INTER_CUBIC);
    cv::remap(frame2, res2, mapBackward, emptymap, INTER_CUBIC);
    result = (res1 + res2) / 2.f;
}
