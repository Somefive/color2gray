//
// Created by somefive on 17-12-21.
//

#ifndef COLOR2GRAY_COLOR2GRAY_H
#define COLOR2GRAY_COLOR2GRAY_H

#include <opencv/cv.hpp>

using namespace cv;

void exec(const String& filename, const String& outFile, int u=1, int max_iter=5, double alpha=5, double theta=M_PI_4);

#endif //COLOR2GRAY_COLOR2GRAY_H
