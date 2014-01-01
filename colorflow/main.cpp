#ifndef MAIN_HPP
#define MAIN_HPP

// Other Includes
#define M_PI 3.14159265359

#include "opencv2/opencv.hpp"
#include "dirent.h"

using namespace cv;
void drawColorField(Mat &imgU, Mat &imgV, Mat &imgColor);
void drawOptFlowMap(const Mat& flow, Mat& cflowmap, int step, const Scalar& color);
std::vector<String> listOfFiles();
Mat *convertFlowToImage(String filename, bool save = true, bool color = false, const Scalar &rgb = NULL, const int step = 0, String origImg = "");

/*
 * Usage :
 *  colorflow input flow/or '.' [options] [--arrow_color r g b] [--step n] [--src filename]
 *
 *  no options : current folder as input, no -v, no -c, arrow color : green, step : 12, src : inputname.jpg
 *
 *  options :
 *  -v  encode the color map in an mp4 video (not fixed)
 *  -c  output will use rgb colors to express direction of flow instead of arrows
 *
 */
int main(int argc, char *argv[]) {
    if (argc < 1 || argc > 11) { return 0; }

    String input(".");
    String src("");
    bool modeVideo(false);
    bool modeColor(false);
    int r(0), g(255), b(0);
    int step(12);

    if (argc != 1) {
        input = argv[1];
        int mode(0); //1-3 : rgb, 4, step
        for (int i(2); i < argc; ++i) {
            String param(argv[i]);
            if (param.compare("-v") == 0) {
                modeVideo = true;
            } else if (param.compare("-c") == 0) {
                modeColor = true;
            } else if (param.compare("--arrow_color") == 0) {
                mode = 1;
            } else if (param.compare("--step") == 0) {
                mode = 4;
            } else if (param.compare("--src") == 0) {
                mode = 5;
            } else if (mode != 0){
                switch(mode) {
                case 1:
                    r = atoi(param.c_str());
                    break;
                case 2:
                    g = atoi(param.c_str());
                    break;
                case 3:
                    b = atoi(param.c_str());
                    mode = 6;
                    break;
                case 4:
                    step = atoi(param.c_str());
                    mode = 6;
                    break;
                case 5:
                    src = param;
                    break;
                }
                ++mode;
            }
        }
    }

    if (!modeVideo && argc == 2) {
        convertFlowToImage(input);
    } else {
        VideoWriter writer;
        bool initialized = false;
        auto files = listOfFiles();
        for (auto it = files.begin(); it != files.end(); ++it) {
            String filename = *it;
            //check if ending is in yml or gz
            int id = filename.find_last_of('.');
            if (id == String::npos) {
                continue; //file with no extension
            }

            if (filename.substr(id).compare(".gz") == 0
                    || filename.substr(id).compare(".yml") == 0) {
                std::cout << "Processing " << filename << "..." << std::endl;

                if (!modeColor) {
                    int id_b = filename.find_first_of('/');
                    if (id_b == String::npos) {
                        id_b = filename.find_first_of('\\');
                        if (id_b == String::npos) {
                            id_b = 0;
                        }
                    }
                    src = filename.substr(id_b, filename.find_first_of('.', id_b) - id_b);
                    src = filename.substr(0, id_b) + src + ".jpg";
                    std::cout << "-> src : " << src << std::endl;
                }

                Mat* colored = convertFlowToImage(filename, !modeVideo, modeColor, CV_RGB(r, g, b), step, src);
                if (modeVideo && !initialized) {
                    Size size(colored->rows, colored->cols);
                    //CV_FOURCC('D', 'I', 'V', 'X');
                    writer.open("colored.avi", CV_FOURCC('F', 'L', 'V', '1'), 30, size, true);
                    initialized = true;
                }
                if (modeVideo) {
                    writer << *colored;
                }
                delete colored;
            }
        }
        if (modeVideo) {
            writer.release();
        }
        std::cout << "Finished." << std::endl;
    }

    return 0;
}

Mat* convertFlowToImage(String filename, bool save, bool color, const Scalar &rgb, const int step, String origImg) {
    //load the optical flow
    FileStorage file(filename, FileStorage::READ);
    size_t oc = filename.find_last_of('\\');
    if (oc == String::npos) {
        oc = filename.find_last_of('/');
        if (oc == String::npos) {
            oc = 0;
        } else {
            ++oc;
        }
    } else {
        ++oc;
    }
    filename = filename.substr(oc, filename.find_first_of('.', oc) - oc);

    Mat flow;
    if (filename.front() == 'a') { //affine flow
        file["afflow"] >> flow;
    } else if (filename.front() == 'w') { //w-flow
        file["wflow"] >> flow;
    } else { //optflow
        file["flowF"] >> flow; //FlowF (Farneback)
        if (flow.empty()) {
            Mat xf, yf;
            file["xf"] >> xf; //xf (Brox)
            file["yf"] >> yf; //yf (Brox)
            std::vector<Mat> array;
            array.push_back(xf);
            array.push_back(yf);

            merge(array, flow);
        }
    }


    Mat* outputImg = new Mat(flow.rows, flow.cols, CV_8UC3);;

    if (color) {
        //apply coloring
        Mat flowU;
        Mat flowV;

        Mat mats[2];
        split(flow, mats);
        flowU = mats[0];
        flowV = mats[1];

        drawColorField(flowU, flowV, *outputImg);

    } else {
        //apply drawing
        Mat origMat = imread(origImg);
        origMat.copyTo(*outputImg);
        drawOptFlowMap(flow, *outputImg, step, rgb);

    }

    if (save) {
        //save the optical flow
        std::cout << "saved to : " << filename + "_flow.jpg" << std::endl;
        imwrite(filename.append("_flow.jpg"), *outputImg);
    }
    file.release();

    return outputImg;
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

void drawColorField(Mat &imgU, Mat &imgV, Mat &imgColor)
{
    Mat imgColorHSV = Mat::zeros(Size(imgColor.cols,imgColor.rows),CV_32FC3);

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

std::vector<String> listOfFiles() {
    DIR *dir;
    struct dirent *ent;
    std::vector<String> out;
    if ((dir = opendir (".")) != NULL) {

      while ((ent = readdir (dir)) != NULL) {
          if (ent->d_type != DT_DIR) {
              out.push_back(String(ent->d_name));
          }
      }
      closedir (dir);
    } else {
      /* could not open directory */
      perror ("");
    }

    return out;
}

void drawOptFlowMap(const Mat& flow, Mat& cflowmap, int step, const Scalar& color) {
    for(int y = step / 2; y < cflowmap.rows; y += step)
        for(int x = step / 2; x < cflowmap.cols; x += step)
        {
            const Point2f& fxy = flow.at<Point2f>(y, x);
//            line(cflowmap, Point(x,y), Point(cvRound(x+fxy.x), cvRound(y+fxy.y)),
//                 color);
//            circle(cflowmap, Point(x,y), 1, color, -1);
            Point p(cvRound(x+fxy.x), cvRound(y+fxy.y));
            line(cflowmap, Point(x,y), p,
                 color);
            circle(cflowmap, p, 1, color, -1);
        }
}


#endif // MAIN_HPP
