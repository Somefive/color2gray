//
// Created by somefive on 17-12-21.
//

#include <iostream>
#include "Color2Gray.h"
#include "utils.h"

Mat source, target;
int rows, cols, N;

void exec(const String &filename, const String& outFile, int u, int max_iter, double alpha, double theta) {
    source = imread(filename);
    cvtColor(source, source, cv::ColorConversionCodes::COLOR_RGB2Lab);
    rows = source.rows;
    cols = source.cols;
    N = rows * cols;

    double * deltas = new double[N];
    int * counters = new int[N];
    int * g = new int[N];
    for (int i=0; i<N; ++i) {
        deltas[i] = 0;
        counters[i] = 0;
        g[i] = 127;
    }

    int avgL = 0;
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int r_start = u > 0 ? ((row - u > 0) ? row - u : 0) : 0;
            int r_end = u > 0 ? ((row + u < rows) ? row + u : rows - 1) : rows - 1;
            int c_start = u > 0 ? ((col - u > 0) ? col - u : 0) : 0;
            int c_end = u > 0 ? ((col + u < cols) ? col + u : cols - 1) : cols - 1;
            for (int r = r_start; r <= r_end; ++r) {
                for (int c = c_start; c <= c_end; ++c) {
                    if (r == row && c == col) continue;
                    deltas[row * cols + col] += calDelta(alpha, theta, source.at<Vec3b>(row, col), source.at<Vec3b>(r, c));
                    ++counters[row * cols + col];
                }
            }
            g[row * cols + col] = source.at<Vec3b>(row, col)[0];
            avgL += source.at<Vec3b>(row, col)[0];
        }
    }

    for (int iter = 0; iter < max_iter; ++iter) {
        printf("\riter: %i", iter);
        std::flush(std::cout);
        int currentAverageL = 0;
        int currentDis = 0;
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                int sum = 0;
                int r_start = u > 0 ? ((row - u > 0) ? row - u : 0) : 0;
                int r_end = u > 0 ? ((row + u < rows) ? row + u : rows - 1) : rows - 1;
                int c_start = u > 0 ? ((col - u > 0) ? col - u : 0) : 0;
                int c_end = u > 0 ? ((col + u < cols) ? col + u : cols - 1) : cols - 1;
                for (int r = r_start; r <= r_end; ++r) {
                    for (int c = c_start; c <= c_end; ++c) {
                        if (r == row && c == col) continue;
                        sum += g[r * cols + c];
                    }
                }
                int index = row * cols + col;
                g[index] = static_cast<int>((sum + deltas[index]) / counters[index]);
                currentAverageL += g[index];
            }
        }
        currentDis = (avgL - currentAverageL) / rows / cols;
        for (int row = 0; row < rows; ++row)
            for (int col = 0; col < cols; ++col)
                g[row * cols + col] += currentDis;
    }
    printf("\nfinished\n");

    target = Mat(rows, cols, CV_8U);
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int _g = g[row * cols + col];
            if (_g < 0) _g = 0;
            if (_g > 255) _g = 255;
            target.at<uchar>(row, col) = static_cast<uchar>(_g);
        }
    }
    imwrite(outFile, target);
    delete [] deltas;
    delete [] counters;
    delete [] g;
}
