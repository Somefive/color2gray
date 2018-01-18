//
// Created by somefive on 17-12-20.
//

#ifndef COLOR2GRAY_UTILS_H
#define COLOR2GRAY_UTILS_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <cmath>

using namespace cv;

double crunch(double x, double alpha);

double calDelta(double alpha, double theta, const Vec3b& color_i, const Vec3b& color_j);

bool valid(Mat mat, int r, int c);

#endif //COLOR2GRAY_UTILS_H
