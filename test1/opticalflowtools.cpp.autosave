#include "project.h"
#include "Image.h"
#include "OpticalFlow.h"
#include <iostream>

#include "opticalflowtools.h"

QImage* OpticalFlowTools::computeCoarse2Fine(const QString& im1, const QString& im2) {
    DImage dimg1,dimg2;

    dimg1.imread(im1);
    dimg2.imread(im2);

    if (dimg2.IsEmpty() || dimg2.IsEmpty()) {
        return NULL;
    }

    // get the parameters
    double alpha= 1;
    double ratio=0.5;
    int minWidth= 40;
    int nOuterFPIterations = 3;
    int nInnerFPIterations = 1;
    int nSORIterations= 20;

    DImage vx,vy,warpI2;
    OpticalFlow::Coarse2FineFlow(vx,vy,warpI2,dimg1,dimg2,
                                 alpha,ratio,
                                 minWidth,nOuterFPIterations,nInnerFPIterations,nSORIterations);


//    DImage featureImage;
//    OpticalFlow::im2feature(featureImage, warpI2);

//    flow.Coarse2FineFlowLevel(vx,vy,warpI2,dimg1,dimg2,
//                                 alpha,ratio, 1,
//                                 nOuterFPIterations,nInnerFPIterations,nSORIterations);

//    OpticalFlow::ComputeOpticalFlow(dimg1, dimg2, warpI2);

    bool res = true;

//    int img_width = warpI2.width();
//    int img_height = warpI2.height();
//    uchar* imgbuf = (uchar*) malloc(img_width*img_height*4);
//    QImage* imgres = new QImage(imgbuf,img_width,img_height,QImage::Format_RGB32);
//    res = warpI2.imwrite("flowout.jpg");

//    res = featureImage.imwrite("feature.jpg");

    res = warpI2.imwrite("flow2.jpg");
    return res ? NULL : new QImage();

//    dimg2.imwrite(imgres);
//            return imgres;
}
