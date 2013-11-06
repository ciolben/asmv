#include "opticalflowcv.h"

#include "broxflow.hpp"

QString* getGPUinfo() {
    // Show CUDA information
    cv::gpu::printShortCudaDeviceInfo(cv::gpu::getDevice());
    return NULL;
}

QImage* computeFlow(const QImage &frame1, const QImage &frame2) {
    //convert qImage to mat

    Mat image1 = QImage2Mat(frame1);
    Mat image2 = QImage2Mat(frame2);

    //compute flow
    Mat flowU, flowV;
    broxOpticalFlow(image1, image2, flowU, flowV);

    //combine flow x y
    Mat flow = cv::Mat(Size(image1.cols, image1.rows),CV_8UC3);
    drawColorField(flowU, flowV, flow);

//        namedWindow("a",CV_WINDOW_NORMAL);
//        namedWindow("flow",CV_WINDOW_NORMAL);
//        imshow("a", image1);
//        imshow("flow", flow);
//        waitKey();
    //return qimage
    return &Mat2QImage(flow);
}

QImage Mat2QImage(cv::Mat const& src)
{
     cv::Mat temp; // make the same cv::Mat
     cvtColor(src, temp,CV_BGR2RGB); // cvtColor Makes a copt, that what i need
     QImage dest((uchar*) temp.data, temp.cols, temp.rows, temp.step, QImage::Format_RGB888);
     QImage dest2(dest);
     dest2.detach(); // enforce deep copy
     return dest2;
}

cv::Mat QImage2Mat(QImage const& src)
{
     cv::Mat tmp(src.height(),src.width(),CV_8UC3,(uchar*)src.bits(),src.bytesPerLine());
     cv::Mat result; // deep copy just in case (my lack of knowledge with open cv)
     cvtColor(tmp, result,CV_BGR2RGB);
     return result;
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
