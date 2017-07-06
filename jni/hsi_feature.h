//
// Created by Developer on 17-7-2.
//
#ifndef CBIR_HSI_FEATURE_H
#define CBIR_HSI_FEATURE_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <dirent.h>
#include <cmath>

using namespace cv;
using namespace std;

struct RGB {
    int r;
    int g;
    int b;
};

typedef struct HSI {
    float hsiWeight[3];
} HSI;

typedef struct HSI_CenterM {
    int weight; // 0 H, 1 S, 2 I
    double M1, M2, M3;
} HSI_Center_Matrix;

HSI *imageToHSI(Mat &img);

/**
 * 计算 M1 矩阵
 * @param hsiArray 保存图像hsi的数据
 * @param len hsiArray的长度
 * @param weight 每个hsi的分量
 * @return 返回中心矩的值
 */
double calculateM1(HSI hsiArray[], int len, int weight);

/**
 * 计算 M2 中心矩阵
 * @param hsiArray
 * @param len
 * @param weight
 * @param m1
 * @return
 */
double calculateM2(HSI hsiArray[], int len, int weight, double m1);

/**
  * 计算 M3 中心矩阵
 * @param hsiArray
 * @param len
 * @param weight
 * @param m1
 * @return
 */
double calculateM3(HSI *hsiArray, int len, int weight, double m1);

double calcHsiDistanceDirect(char* imagePath1, char* imagePath2);

/**
 * 计算三个hsi分量的相似度
 * @param r1
 * @param b1
 * @param g1
 * @param r2
 * @param b2
 * @param g2
 * @return
 */
double calcHsiDistance(HSI_Center_Matrix *r1,
                       HSI_Center_Matrix *b1,
                       HSI_Center_Matrix *g1,
                       HSI_Center_Matrix *r2,
                       HSI_Center_Matrix *b2,
                       HSI_Center_Matrix *g2);

HSI_CenterM *calculateHSICenterMByPath(const char *path, int weight);

/**
 * 计算图像的HSI中心矩
 * @param img
 * @param weight
 * @return
 */
HSI_CenterM *calculateHSICenterM(Mat &img, int weight);

#endif //CBIR_HSI_FEATURE_H
