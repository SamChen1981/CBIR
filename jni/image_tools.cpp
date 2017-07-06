//
// Created by Developer on 17-7-3.
//

#include "image_tools.h"

Mat *imageToGray(Mat &img) {
    Mat *grayImg = new Mat(img.size(), CV_8U);
    for (int i = 0; i < img.rows; i++) {
        for (int j = 0; j < img.cols; j++) {
            int r, g, b;
            r = img.at<Vec3b>(i, j)[0];
            g = img.at<Vec3b>(i, j)[1];
            b = img.at<Vec3b>(i, j)[2];
            grayImg->at<uchar>(i, j) = rgbToGray(r, g, b);
        }
    }
    return grayImg;
}

int rgbToGray(int r, int g, int b) {
    return 0.30 * r + 0.59 * g + 0.11 * b;
}
