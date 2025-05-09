#ifndef EDGE_ENHANCEMENT_LAPLACIAN_H
#define EDGE_ENHANCEMENT_LAPLACIAN_H

#include <iostream>
#include <filesystem>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

[[nodiscard]]
cv::Mat laplacian(const cv::Mat &image, const int ksize = 3, const double alpha = 1.5, const double beta = -0.5,
                  const double gamma = 0);

#endif //EDGE_ENHANCEMENT_LAPLACIAN_H
