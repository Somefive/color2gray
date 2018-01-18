//
// Created by somefive on 17-12-20.
//

#include "utils.h"

double crunch(double x, double alpha) {
    return alpha > 0 ? alpha * tanh(x / alpha) : 0;
}

double calDelta(double alpha, double theta, const Vec3b& color_i, const Vec3b& color_j) {
    double Lij = color_i(0) - color_j(0);
    double Cij_a = color_i(1) - color_j(1), Cij_b = color_i(2) - color_j(2);
    double color_dis = sqrt(Cij_a * Cij_a + Cij_b * Cij_b);
    double crunch_res = crunch(color_dis, alpha);
    if (abs(Lij) > crunch_res) return Lij;
    else if (Cij_a * cos(theta) + Cij_b * sin(theta) >= 0) return crunch_res;
    else return -crunch_res;
}

bool valid(Mat mat, int r, int c) {
    return r >= 0 && r < mat.rows && c >= 0 && c < mat.cols;
}
