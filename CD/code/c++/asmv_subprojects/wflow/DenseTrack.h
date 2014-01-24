#ifndef DENSETRACK_H_
#define DENSETRACK_H_

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <ctype.h>
//#include <sys/unistd.h>

#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <string>

#include "opencv/IplImageWrapper.h"
#include "opencv/IplImagePyramid.h"
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/io.hpp>

/*
 * MSVC compat
 */
#if _MSC_VER >= 1600
    #include "msvccompat.h"
#endif
/*
 *
 */

// parameters for descriptors
int patch_size = 32;
int nxy_cell = 2;
int nt_cell = 3;
bool fullOrientation = true;
float epsilon = 0.05;
const float min_flow = 0.4*0.4;
//const float PI = 3.14159;

// parameters for tracking
int start_frame = 0;
int end_frame = 1000000;
double quality = 0.001;
double min_distance = 5;
int init_gap = 1;
int track_length = 15;

int wFlow = 0;			// 0: use Optical flow for features | 1: use wFlow (Optical flow - Affine flow) to compute w-features
int featComb = 0;		// 0: traj, hog, hof/w-hof (hof hofwflow), mbh | 1: traj, dcs (curldiv shearC shearD)
int compute_models = 0;		// write Affine model files if 1 else compute descriptors

// parameters for the trajectory descriptor
const float min_var = sqrt(3.f);
const float max_var = 50;
const float max_dis = 20;

// parameters for multi-scale
int scale_num = 8;  
const float scale_stride = sqrt(2.f);

// parameters for saving flows
bool saveWflow = true;
bool saveAflow = false;

typedef struct TrackerInfo
{
    int trackLength; // length of the trajectory
    int initGap; // initial gap for feature detection
}TrackerInfo;

typedef struct DescInfo
{
    int nBins; // number of bins for vector quantization
    int fullOrientation; // 0: 180 degree; 1: 360 degree
    int norm; // 1: L1 normalization; 2: L2 normalization
    float threshold; //threshold for normalization
	int flagThre; // whether thresholding or not
    int nxCells; // number of cells in x direction
    int nyCells; 
    int ntCells;
	int dim; // dimension of the descriptor
    int blockHeight; // size of the block for computing the descriptor
    int blockWidth;
}DescInfo; 

typedef struct DescMat
{
    int height;
    int width;
    int nBins;
    float* desc;
}DescMat;

class PointDesc
{
public:
    std::vector<float> hog;
    std::vector<float> hof;
    std::vector<float> hof_wFlow;
    std::vector<float> mbhX;
    std::vector<float> mbhY;
    std::vector<float> curldiv;
    std::vector<float> shearC;
    std::vector<float> shearD;
    CvPoint2D32f point;

    PointDesc(const DescInfo& hogInfo, const DescInfo& hofInfo, const DescInfo& mbhInfo, const CvPoint2D32f& point_)
        : hog(hogInfo.nxCells * hogInfo.nyCells * hogInfo.nBins),
        hof(hofInfo.nxCells * hofInfo.nyCells * hofInfo.nBins),
        mbhX(mbhInfo.nxCells * mbhInfo.nyCells * mbhInfo.nBins),
                mbhY(mbhInfo.nxCells * mbhInfo.nyCells * mbhInfo.nBins),
        point(point_)
    {}

    PointDesc(int dummy, const DescInfo& hogInfo, const DescInfo& hofInfo, const DescInfo& mbhInfo, const CvPoint2D32f& point_)
        : hog(hogInfo.nxCells * hogInfo.nyCells * hogInfo.nBins),
        hof(hofInfo.nxCells * hofInfo.nyCells * hofInfo.nBins),
	hof_wFlow(hofInfo.nxCells * hofInfo.nyCells * hofInfo.nBins),
        mbhX(mbhInfo.nxCells * mbhInfo.nyCells * mbhInfo.nBins),
                mbhY(mbhInfo.nxCells * mbhInfo.nyCells * mbhInfo.nBins),
        point(point_)
    {}

    PointDesc(const DescInfo& curldivInfo, const DescInfo& shearCDInfo, const CvPoint2D32f& point_)
        : curldiv(curldivInfo.nxCells * curldivInfo.nyCells * curldivInfo.nBins),
        shearC(shearCDInfo.nxCells * shearCDInfo.nyCells * shearCDInfo.nBins),
        	shearD(shearCDInfo.nxCells * shearCDInfo.nyCells * shearCDInfo.nBins),
        point(point_)
    {}
};

class Track
{
public:
    std::list<PointDesc> pointDescs;
    int maxNPoints;

    Track(int maxNPoints_)
        : maxNPoints(maxNPoints_)
    {}

    void addPointDesc(const PointDesc& point)
    {
        pointDescs.push_back(point);
        if (pointDescs.size() > maxNPoints + 2) {
            pointDescs.pop_front();
		}
    }
};

#endif /*DENSETRACK_H_*/