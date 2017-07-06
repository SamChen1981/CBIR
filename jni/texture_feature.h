//
// Created by Developer on 17-7-3.
//

#ifndef CBIR_TEXTURE_FEATURE_H
#define CBIR_TEXTURE_FEATURE_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <dirent.h>
#include <cmath>

using namespace cv;
using namespace std;

typedef struct TextureFeature {
    double eentropy;
    double eidm;
    double econ;
    double easm;
    double centropy;
    double cidm;
    double ccon;
    double casm;
} TextureFeature;

TextureFeature * calculateTextureFeature(const char *path);

/** 256灰度级的8个区间
/* 0 ~ 31
 * 32 ~ 64
 * 65 ~ 97
 * 98 ~ 130
 * 131 ~ 163
 * 164 ~ 196
 * 197 ~ 229
 * 230 ~ 256
**/

// 计算 0度方向共生矩阵
double *calcCOOMatrix0(Mat &img);

// 计算 45度方向共生矩阵
double *calcCOOMatrix45(Mat &img);

// 计算 135度方向共生矩阵
double *calcCOOMatrix135(Mat &img);

// 计算 180度方向共生矩阵
double *calcCOOMatrix180(Mat &img);

// 划分区间
int calcInterval(int gray);

// 归一化
void regression(double *matrix);

/**
 * 计算熵，统计图像的复杂度
 * @param matrix
 * @return
 */
double Entropy(double *matrix);

/**
 * 反映了纹理的清晰程度和规则程度，纹理清晰、规律性较强、易于描述的，值较大；杂乱无章的，难于描述的，值较小。
 * @param matrix
 * @return
 */
double IDM(double *matrix);

double Con(double *matrix);

/**
 * 角二阶矩是图像灰度分布均匀程度和纹理粗细的一个度量，当图像纹理绞细致、灰度分布均匀时，能量值较大，反之，较小
 * @param matrix
 * @return
 */
double ASM(double *matrix);

double COR(double *matrix);

#endif //CBIR_TEXTURE_FEATURE_H
