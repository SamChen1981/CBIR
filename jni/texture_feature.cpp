//
// Created by Developer on 17-7-3.
//

#include "texture_feature.h"
#include "image_tools.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <dirent.h>
#include <cmath>

/**
 * rgb图像求0度矩阵
 * @param img
 * @return
 */
double *calcCOOMatrix0(Mat &img) {
    // 第一步，区间化，构建8*8矩阵
    double *resultMatrix = new double[64];
    memset(resultMatrix, 0, 64 * sizeof(double));
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols - 1; j++) {
            int interval1 = calcInterval(
                    rgbToGray(img.at<Vec3b>(i, j)[0], img.at<Vec3b>(i, j)[1], img.at<Vec3b>(i, j)[2]));
            int interval2 = calcInterval(
                    rgbToGray(img.at<Vec3b>(i, j + 1)[0], img.at<Vec3b>(i, j + 1)[1], img.at<Vec3b>(i, j + 1)[2]));
            resultMatrix[(interval1 - 1) * 8 + (interval2 - 1)]++;
        }
    }
//    for (int i = 0;i < 64;i ++) {
//        cout << resultMatrix[i] << endl;
//    }
    regression(resultMatrix);
    return resultMatrix;
}

int calcInterval(int gray) {
    if (gray <= 31) {
        return 1;
    } else if (gray <= 64) {
        return 2;
    } else if (gray <= 97) {
        return 3;
    } else if (gray <= 130) {
        return 4;
    } else if (gray <= 163) {
        return 5;
    } else if (gray <= 196) {
        return 6;
    } else if (gray <= 229) {
        return 7;
    } else {
        return 8;
    }
}

double *calcCOOMatrix45(Mat &img) {
    double *resultMatrix = new double[64];
    memset(resultMatrix, 0, 64 * sizeof(double));
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            if (i - 1 < 0 || j + 1 >= img.cols || i - 1 >= img.rows || j + 1 < 0) {
                continue;
            }

            int interval1 = calcInterval(
                    rgbToGray(img.at<Vec3b>(i, j)[0], img.at<Vec3b>(i, j)[1], img.at<Vec3b>(i, j)[2]));
            int interval2 = calcInterval(
                    rgbToGray(img.at<Vec3b>(i - 1, j + 1)[0], img.at<Vec3b>(i - 1, j + 1)[1],
                              img.at<Vec3b>(i - 1, j + 1)[2]));
            resultMatrix[(interval1 - 1) * 8 + (interval2 - 1)]++;
        }
    }
    regression(resultMatrix);
    return resultMatrix;
}

double *calcCOOMatrix135(Mat &img) {
    double *resultMatrix = new double[64];
    memset(resultMatrix, 0, 64 * sizeof(double));
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            if (i - 1 < 0 || j - 1 < 0 || i - 1 >= img.rows || j - 1 >= img.cols) {
                continue;
            }

            int interval1 = calcInterval(
                    rgbToGray(img.at<Vec3b>(i, j)[0], img.at<Vec3b>(i, j)[1], img.at<Vec3b>(i, j)[2]));
            int interval2 = calcInterval(
                    rgbToGray(img.at<Vec3b>(i - 1, j - 1)[0], img.at<Vec3b>(i - 1, j - 1)[1],
                              img.at<Vec3b>(i - 1, j - 1)[2]));
            resultMatrix[(interval1 - 1) * 8 + (interval2 - 1)]++;
        }
    }
    regression(resultMatrix);
    return resultMatrix;
}

double *calcCOOMatrix180(Mat &img) {
    double *resultMatrix = new double[64];
    memset(resultMatrix, 0, 64 * sizeof(double));
    for (int i = 0; i < img.rows; i++) {
        for (int j = 1; j < img.cols; j++) {
            int interval1 = calcInterval(
                    rgbToGray(img.at<Vec3b>(i, j)[0], img.at<Vec3b>(i, j)[1], img.at<Vec3b>(i, j)[2]));
            int interval2 = calcInterval(
                    rgbToGray(img.at<Vec3b>(i, j - 1)[0], img.at<Vec3b>(i, j - 1)[1],
                              img.at<Vec3b>(i, j - 1)[2]));
            resultMatrix[(interval1 - 1) * 8 + (interval2 - 1)]++;
        }
    }
    regression(resultMatrix);
    return resultMatrix;
}

void regression(double *matrix) {
    double sum = 0;
    for (int i = 0; i < 64; i++) {
        sum += matrix[i];
    }

    if (sum == 0) {
        return;
    }

    for (int i = 0; i < 64; i++) {
        matrix[i] /= sum;
    }
}

double ASM(double *matrix) {
    double sum = 0;
    for (int i = 0; i < 64; i++) {
        sum += pow(matrix[i], 2);
    }
    return sum;
}

double Entropy(double *matrix) {
    double result = 0;
    for (int i = 0; i < 64; i++) {
        if (matrix[i] == 0) {
            continue;
        }
        result += matrix[i] * (-log(matrix[i]));
    }
    return result;
}

double IDM(double *matrix) {
    double result = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            result += (matrix[i * 8 + j] / (1 + pow(i - j, 2)));
        }
    }
    return result;
}

double Con(double *matrix) {
    double result = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            result += (matrix[i * 8 + j] * pow(i - j, 2));
        }
    }
    return result;
}

double COR(double *matrix) {
    double u1, u2, s1, s2;
    double cor = 0;
    u1 = u2 = s1 = s2 = 0;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            u1 += i * matrix[i * 8 + j];
            u2 += j * matrix[i * 8 + j];
        }
    }

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            s1 += matrix[i * 8 + j] * pow(i - u1, 2);
            s2 += matrix[i * 8 + j] * pow(i - u2, 2);
        }
    }

    double temp = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            temp = i * j * matrix[i * 8 + j] - u1 * u2 / s1 / s2;
            cor += temp;
        }
    }
    return cor;
}

TextureFeature *calculateTextureFeature(const char *path) {
    Mat img = imread(path);
    TextureFeature *textureFeature = new TextureFeature();

    double *matrix0 = calcCOOMatrix0(img);
    double *matrix45 = calcCOOMatrix45(img);
    double *matrix135 = calcCOOMatrix135(img);
    double *matrix180 = calcCOOMatrix180(img);

    double entropy1 = Entropy(matrix0);
    double entropy2 = Entropy(matrix45);
    double entropy3 = Entropy(matrix135);
    double entropy4 = Entropy(matrix180);

    double avgEntropy = (entropy1 + entropy2 + entropy3 + entropy4) / 4;
    textureFeature->eentropy = avgEntropy;
    double cEntropy = sqrt(
            (powf(entropy1 - avgEntropy, 2) + powf(entropy2 - avgEntropy, 2) + powf(entropy3 - avgEntropy, 2) +
             powf(entropy4 - avgEntropy, 2)) / 4);
    textureFeature->centropy = cEntropy;

    double idm1 = IDM(matrix0);
    double idm2 = IDM(matrix45);
    double idm3 = IDM(matrix135);
    double idm4 = IDM(matrix180);

    double avgIdm = (idm1 + idm2 + idm3 + idm4) / 4;
    textureFeature->eidm = avgIdm;
    double cIdm = sqrt(
            (powf(idm1 - avgIdm, 2) + powf(idm2 - avgIdm, 2) + powf(idm3 - avgIdm, 2) + powf(idm4 - avgIdm, 2)) / 4
    );
    textureFeature->cidm = cIdm;

    double con1 = Con(matrix0);
    double con2 = Con(matrix45);
    double con3 = Con(matrix135);
    double con4 = Con(matrix180);

    double avgCon = (con1 + con2 + con3 + con4) / 4;
    textureFeature->econ = avgCon;
    double ccon = sqrt(
            (powf(con1 - avgCon, 2) + powf(con2 - avgCon, 2) + powf(con3 - avgCon, 2) + powf(con4 - avgCon, 2)) / 4
    );
    textureFeature->ccon = ccon;

    double asm1 = ASM(matrix0);
    double asm2 = ASM(matrix45);
    double asm3 = ASM(matrix135);
    double asm4 = ASM(matrix180);

    double avgAsm = (asm1 + asm2 + asm3 + asm4) / 4;
    textureFeature->easm = avgAsm;
    double casm = sqrt(
            (powf(asm1 - avgAsm, 2) + powf(asm2 - avgAsm, 2) + powf(asm3 - avgAsm, 2) + powf(asm4 - avgAsm, 2)) / 4
    );
    textureFeature->casm = casm;

    return textureFeature;
}
