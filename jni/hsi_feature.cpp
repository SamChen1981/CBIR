//
// Created by Developer on 17-7-2.
//
#include "hsi_feature.h"

HSI *imageToHSI(Mat &img) {
    HSI *hsi = new HSI[img.rows * img.cols];

    int rows = img.rows;
    int cols = img.cols;
    for (int rowIndex = 0; rowIndex < rows; rowIndex++) {
        for (int colIndex = 0; colIndex < cols; colIndex++) {
            double h, s, i;
            int r = img.at<Vec3b>(rowIndex, colIndex).val[0];
            int g = img.at<Vec3b>(rowIndex, colIndex).val[1];
            int b = img.at<Vec3b>(rowIndex, colIndex).val[2];

            //    cout << r << " " << g << " " << b << endl;
            // 注意，这里的tempAngle是以弧度为单位
            double PI_Angle = 0;
            if (g == b) {
                PI_Angle = 0;
            } else {
                double tempAngle = ((float) (2 * r - g - b)) / (sqrt(3) * (g - b));
                PI_Angle = M_PI / 2 - atan(tempAngle);
            }

            if (g >= b) {
                h = PI_Angle;
            } else {
                h = PI_Angle + M_PI;
            }

            s = 2 / sqrt(6) * sqrt((pow(r - g, 2) + (r - b) * (g - b)));
            i = (r + g + b) / sqrt(3);

            hsi[rowIndex * cols + colIndex].hsiWeight[0] = h;
            hsi[rowIndex * cols + colIndex].hsiWeight[1] = s;
            hsi[rowIndex * cols + colIndex].hsiWeight[2] = i;
        }
    }
    return hsi;
}

double calculateM1(HSI *hsiArray, int len, int weight) {
    if (len == 0) {
        cout << "error! hsiArray length is 0";
        exit(0);
    }
    double result = 0;
    for (int i = 0; i < len; i++) {
        result += hsiArray[i].hsiWeight[weight];
    }
//    cout << "calculateM1 len: " << len << endl;
//    cout << "calculateM1 result: " << result << endl;
//    cout << "calculateM1 result / len: " << result / len << endl;
    return result / len;
}

double calculateM2(HSI *hsiArray, int len, int weight, double m1) {
    if (len == 0) {
        cout << "error! hsiArray length is 0";
        exit(0);
    }
    double result = 0;
    for (int i = 0; i < len; i++) {
        result += pow((hsiArray[i].hsiWeight[weight] - m1), 2);
    }
    result /= len;
    return sqrt(result);
}

double calculateM3(HSI *hsiArray, int len, int weight, double m1) {
    if (len == 0) {
        cout << "error! hsiArray length is 0";
        exit(0);
    }

//    cout << m1 << " m1 " << endl;

    double result = 0;
    for (int i = 0; i < len; i++) {
//        cout << hsiArray[i].hsiWeight[weight];
        result += pow((hsiArray[i].hsiWeight[weight] - m1), 3);
    }
//    cout << result << " result " << endl;
//    cout << result / len << " result / len " << endl;
//    cout << powf(result / len, 1.0 / 3) << " pow " << endl;
//    cout << -powf(abs(result / len), 1.0 / 3) << " pow " << endl;
    result /= len;
    return -powf(abs(result), 1.0 / 3);
}

HSI_CenterM *calculateHSICenterM(Mat &img, int weight) {
    double M1, M2, M3;
    M1 = M2 = M3 = 0;

    int length = img.rows * img.cols;

    HSI *hsi = imageToHSI(img);

//    for (int i  = 0;i < length;i ++) {
//        cout << " " << hsi[i].hsiWeight[weight];
//    }

    M1 = calculateM1(hsi, length, weight);
    M2 = calculateM2(hsi, length, weight, M1);
    M3 = calculateM3(hsi, length, weight, M1);

    HSI_CenterM *centerM = new HSI_CenterM();
    centerM->weight = weight;
    centerM->M1 = M1;
    centerM->M2 = M2;
    centerM->M3 = M3;

    delete hsi;
    return centerM;
}

double calcHsiDistance(HSI_Center_Matrix *r1, HSI_Center_Matrix *b1, HSI_Center_Matrix *g1,
                       HSI_Center_Matrix *r2, HSI_Center_Matrix *b2, HSI_Center_Matrix *g2) {

    double temp = r1->M1 * r2->M1 + r1->M2 * r2->M2 + r1->M3 * r2->M3 +
                  g1->M1 * g2->M1 + g1->M2 * g2->M2 + g1->M3 * g2->M3 +
                  b1->M1 * b2->M1 + b1->M2 * b2->M2 + b1->M3 * b2->M3;

    double temp2 =
            sqrt(
                    powf(r1->M1, 2) +
                    powf(r1->M2, 2) +
                    powf(r1->M3, 2) +
                    powf(g1->M1, 2) +
                    powf(g1->M2, 2) +
                    powf(g1->M3, 2) +
                    powf(b1->M1, 2) +
                    powf(b1->M2, 2) +
                    powf(b1->M3, 2)) *
            sqrt(
                    powf(r2->M1, 2) +
                    powf(r2->M2, 2) +
                    powf(r2->M3, 2) +
                    powf(g2->M1, 2) +
                    powf(g2->M2, 2) +
                    powf(g2->M3, 2) +
                    powf(b2->M1, 2) +
                    powf(b2->M2, 2) +
                    powf(b2->M3, 2));
    return temp / temp2;
}

HSI_CenterM *calculateHSICenterMByPath(const char *path, int weight) {
    Mat img = imread(path);
    return calculateHSICenterM(img, weight);
}

double calcHsiDistanceDirect(char *imagePath1, char *imagePath2) {
    Mat img1 = imread(imagePath1);
    Mat img2 = imread(imagePath2);

    HSI_CenterM *hsi_centerM1R = calculateHSICenterM(img1, 0);
    HSI_CenterM *hsi_centerM2R = calculateHSICenterM(img2, 0);

    HSI_CenterM *hsi_centerM1G = calculateHSICenterM(img1, 1);
    HSI_CenterM *hsi_centerM2G = calculateHSICenterM(img2, 1);

    HSI_CenterM *hsi_centerM1B = calculateHSICenterM(img1, 2);
    HSI_CenterM *hsi_centerM2B = calculateHSICenterM(img2, 2);

    return calcHsiDistance(hsi_centerM1R,
                           hsi_centerM1G,
                           hsi_centerM1B,
                           hsi_centerM2R,
                           hsi_centerM2G,
                           hsi_centerM2B);
}

