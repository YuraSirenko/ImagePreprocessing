#ifndef COMPUTATION_H
#define COMPUTATION_H

#include <opencv2/core/mat.hpp>
#include "clock.h"

class Computation {
public:
    explicit Computation(int threads = 1);

    [[nodiscard]]
    static cv::Mat sequence(const cv::Mat &image, Clock &clock);

    [[nodiscard]]
    static cv::Mat openmp(const cv::Mat &image, Clock &clock);

    [[nodiscard]]    [[deprecated]]
    static cv::Mat mpi(const cv::Mat &image, Clock &clock);

    void setThreads(int threads);

private:
    int threads_;
};

#endif // COMPUTATION_H