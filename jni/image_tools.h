//
// Created by Developer on 17-7-3.
//

#ifndef CBIR_IMAGE_TOOLS_H
#define CBIR_IMAGE_TOOLS_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <dirent.h>
#include <cmath>

using namespace cv;
using namespace std;

Mat *imageToGray(Mat &img);

int rgbToGray(int r, int g, int b);

#endif //CBIR_IMAGE_TOOLS_H
