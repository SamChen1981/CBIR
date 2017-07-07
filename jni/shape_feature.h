//
// Created by Developer on 17-7-3.
//

#ifndef CBIR_HU_MATRIX_FEATURE_H
#define CBIR_HU_MATRIX_FEATURE_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <dirent.h>
#include <cmath>

using namespace cv;
using namespace std;

typedef struct HuMatrix {
    float m[6];
} HuMatrix;

HuMatrix *calculateHuMatrix(const char *path);

/**
 * 计算几何不变矩，这个才是对外的借口
 * @param img
 */
HuMatrix *calculateHuMatrix(Mat &img);

HuMatrix *realCalculate(Mat &img);

Mat *threshBinary(Mat &img);

#endif //CBIR_HU_MATRIX_FEATURE_H
