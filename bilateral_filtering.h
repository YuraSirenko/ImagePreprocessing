#ifndef BILATERAL_FILTERING_H
#define BILATERAL_FILTERING_H

#include <opencv2/opencv.hpp>

[[nodiscard]]
cv::Mat bilateralFiltering(const cv::Mat &image, const int d = 7, const double sigmaColor = 75.0, const double sigmaSpace = 75.0);
#endif //BILATERAL_FILTERING_H
