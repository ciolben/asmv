#ifndef MAIN_HPP
#define MAIN_HPP

// Other Includes
#define M_PI 3.14159265359

#include "opencv2/opencv.hpp"
#include <dirent.h>

using namespace cv;
void drawColorField(Mat &imgU, Mat &imgV, Mat &imgColor);
std::vector<String> listOfFiles();
Mat *convertFlowToImage(String filename, bool save = true);

int main(int argc, char *argv[]) {
    if (argc < 1 || argc > 2) { return 0; }
    bool modeVideo = false;
    if (argc == 2) {
        String opt(argv[1]);
        if (opt.compare("-v") == 0) {
            modeVideo = true;
        }
    }

    if (!modeVideo && argc == 2) {
        convertFlowToImage(argv[1]);
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

                Mat* colored = convertFlowToImage(filename, !modeVideo);
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

Mat* convertFlowToImage(String filename, bool save) {
    //load the optical flow
    String filter;
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

    if (filename.front() == 'a') { //affine flow
        filter = "afflow";
    } else { //w-flow
        filter = "wflow";
    }

    Mat flow;
    file[filter] >> flow;

    //apply coloring
    Mat flowU;
    Mat flowV;

    Mat mats[2];
    split(flow, mats);
    flowU = mats[0];
    flowV = mats[1];

    Mat* colorImg = new Mat(flow.rows, flow.cols, CV_8UC3);
    drawColorField(flowU, flowV, *colorImg);

    if (save) {
        //save the optical flow
        imwrite(filename.append(".png"), *colorImg);
    }
    file.release();

    return colorImg;
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

#endif // MAIN_HPP
