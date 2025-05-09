#include "edge_enhancement_laplacian.h"

cv::Mat laplacian(const cv::Mat &image, const int ksize, const double alpha, const double beta,
                  const double gamma) {
    cv::Mat laplacian, sharpened;
    Laplacian(image, laplacian, CV_16S, ksize);
    convertScaleAbs(laplacian, laplacian);
    addWeighted(image, alpha, laplacian, beta, gamma, sharpened);
    return sharpened;
}
