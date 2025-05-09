#include "bilateral_filtering.h"

cv::Mat bilateralFiltering(const cv::Mat &image, const int d, const double sigmaColor, const double sigmaSpace) {
    cv::Mat bilateral;
    bilateralFilter(image, bilateral, d, sigmaColor, sigmaSpace);
    return bilateral;
}

