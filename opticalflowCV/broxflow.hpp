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

    uGPU.download(flowU);
    vGPU.download(flowV);
}

static void drawOptFlowMap(const Mat& flow, Mat& cflowmap, int step,
                    double, const Scalar& color)
{
    for(int y = 0; y < cflowmap.rows; y += step)
        for(int x = 0; x < cflowmap.cols; x += step)
        {
            const Point2f& fxy = flow.at<Point2f>(y, x);
            line(cflowmap, Point(x,y), Point(cvRound(x+fxy.x), cvRound(y+fxy.y)),
                 color);
            circle(cflowmap, Point(x,y), 2, color, -1);
        }
}

void farnebackOpticalFlowCPU(const Mat& image1, const Mat& image2, Mat& flow, Mat&visual)
{
    Mat im1gray, im2gray;
    cvtColor(image1, im1gray, CV_BGR2GRAY);
    cvtColor(image2, im2gray, CV_BGR2GRAY);

//    CvSize size; size.height = image1.rows; size.width = image1.cols;
//    fl = cvCreateImage(size, IPL_DEPTH_32F, 2);
   // cv::Mat _flow = cv::cvarrToMat(fl);
    cv::calcOpticalFlowFarneback(im1gray, im2gray, flow, 0.5, 3, 15, 3, 5, 1.2, 0);

    cvtColor(im1gray, visual, CV_GRAY2BGR);
    drawOptFlowMap(flow, visual, 16, 1.5, CV_RGB(0, 255, 0));

//    namedWindow("b",CV_WINDOW_NORMAL);
//    imshow("b", visual );
//    waitKey();
}


