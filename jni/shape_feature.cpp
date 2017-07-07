//
// Created by Developer on 17-7-3.
//

#include "shape_feature.h"
#include "image_tools.h"

HuMatrix *calculateHuMatrix(Mat &img) {
    // 灰度化
    Mat *grayImg = imageToGray(img);
    // 中值滤波
    Mat *medianImg = new Mat();
    medianBlur(*grayImg, *medianImg, 7);
    // sobel锐化
    Mat *sobelImg1 = new Mat();
    Sobel(*medianImg, *sobelImg1, medianImg->depth(), 0, 1);
    Mat *sobelImg2 = new Mat();
    Sobel(*sobelImg1, *sobelImg2, medianImg->depth(), 0, 1);
    // 二值化
    Mat *result = threshBinary(*sobelImg2);

    delete (sobelImg1);
    delete (sobelImg2);
    delete (medianImg);
    delete (grayImg);

    return realCalculate(*result);
}

HuMatrix *realCalculate(Mat &img) {
    double m_00 = 0, m_01 = 0, m_10 = 0;
    double x_gravity = 0, y_gravity = 0;
    double x_center = 0, y_center = 0;
    double H_00 = 0, H_02 = 0, H_03 = 0, H_11 = 0, H_12 = 0, H_20 = 0, H_21 = 0, H_30 = 0;
    float eta_02 = 0, eta_03 = 0, eta_11 = 0, eta_12 = 0, eta_20 = 0, eta_21 = 0, eta_30 = 0;
    float m_mo_1, m_mo_2, m_mo_3, m_mo_4, m_mo_5, m_mo_6;

    // 第一步，求解M00，M01，M10
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            int tempValue = img.at<uchar>(i, j);
            m_00 += powf(i, 0) * powf(j, 0) * tempValue;
            m_01 += powf(i, 0) * powf(j, 1) * tempValue;
            m_10 += powf(i, 1) * powf(j, 0) * tempValue;
        }
    }
    x_gravity = m_10 / m_00;
    y_gravity = m_01 / m_00;

    // 第二步，求解中心矩
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            int tempValue = img.at<uchar>(i, j);
            x_center = i - x_gravity;
            y_center = j - y_gravity;
            H_00 += pow(x_center, 0) * pow(y_center, 0) * tempValue;
            H_02 += pow(x_center, 0) * pow(y_center, 2) * tempValue;
            H_03 += pow(x_center, 0) * pow(y_center, 3) * tempValue;
            H_11 += pow(x_center, 1) * pow(y_center, 1) * tempValue;
            H_12 += pow(x_center, 1) * pow(y_center, 2) * tempValue;
            H_20 += pow(x_center, 2) * pow(y_center, 0) * tempValue;
            H_21 += pow(x_center, 2) * pow(y_center, 1) * tempValue;
            H_30 += pow(x_center, 3) * pow(y_center, 0) * tempValue;
        }
    }

    //第三部，矩阵的归一化
    eta_02 = H_02 / pow(H_00, 2);
    eta_03 = H_03 / pow(H_00, 2.5);
    eta_11 = H_11 / pow(H_00, 2);
    eta_12 = H_12 / pow(H_00, 2.5);
    eta_20 = H_20 / pow(H_00, 2);
    eta_21 = H_21 / pow(H_00, 2.5);
    eta_30 = H_30 / pow(H_00, 2.5);
    //矩不变特征
    m_mo_1 = eta_20 + eta_02;
    m_mo_2 = pow(eta_20 - eta_02, 2) + 4 * pow(eta_11, 2);
    m_mo_3 = pow(eta_30 - 3 * eta_12, 2) + pow(3 * eta_21 - eta_03, 2);
    m_mo_4 = pow(eta_30 + eta_12, 2) + pow(eta_21 + eta_03, 2);
    m_mo_5 = (eta_30 - 3 * eta_12) * (eta_03 + eta_21) * (pow(eta_30 + eta_12, 2) - 3 * pow(eta_21 + eta_03, 2)) +
             (3 * eta_12 - eta_03) * (eta_21 + eta_30) * (3 * pow(eta_30 + eta_12, 2) - pow(eta_21 + eta_03, 2));
    m_mo_6 = (eta_20 - eta_02) * (pow(eta_30 + eta_12, 2) - pow(eta_21 + eta_03, 2)) +
             4 * eta_11 * (eta_30 + eta_12) * (eta_03 + eta_21);

    HuMatrix *matrix = new HuMatrix();
    matrix->m[0] = m_mo_1;
    matrix->m[1] = m_mo_2;
    matrix->m[2] = m_mo_3;
    matrix->m[3] = m_mo_4;
    matrix->m[4] = m_mo_5;
    matrix->m[5] = m_mo_6;
    return matrix;
}

/**
 * 将传入的灰度图像二值化
 * @param img
 * @return
 */
Mat *threshBinary(Mat &img) {
    int thresh1 = 100;
    int thresh2 = 100;
    float blow, above;
    int blowNum, aboveNum;

    do {
        thresh1 = thresh2;
        blowNum = aboveNum = 0;
        blow = above = 0.0;

        for (int i = 0; i < img.rows; i++) {
            for (int j = 0; j < img.cols; j++) {
                int gray = img.at<uchar>(i, j);
                if (gray <= thresh1) {
                    blowNum++;
                    blow += gray;
                } else {
                    aboveNum++;
                    above += gray;
                }
            }
        }

        int u1 = blow / blowNum;
        int u2 = above / aboveNum;
        thresh2 = (u1 + u2) / 2;

    } while (abs(thresh1 - thresh2) > 1);

    Mat *result = new Mat();
//    cout << "thresh" << thresh1 << endl;
    threshold(img, *result, thresh1, 255, CV_THRESH_BINARY);
    return result;
}

HuMatrix *calculateHuMatrix(const char *path) {
    Mat img = imread(path);
    return calculateHuMatrix(img);
}
