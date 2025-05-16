#include "bilateral_filtering.h"
#include "computation.h"
#include "edge_enhancement_laplacian.h"
#include "io.h"
#include <mpi.h>
#include <omp.h>

Computation::Computation(int threads) : threads_{threads} {
    omp_set_num_threads(threads_);
}

void Computation::setThreads(int threads) {
    threads_ = threads;
}

cv::Mat Computation::sequence(const cv::Mat &image, Clock &clock) {
    clock.start();
    Clock shit = Clock();
    shit.start();

    Clock a = Clock();
    a.start();
    const auto lap = laplacian(image);
    a.logTime("laplacian");

    Clock b = Clock();
    b.start();
    const auto bil = bilateralFiltering(image);
    b.logTime("bilateralFiltering");

    shit.logTime("Total");
    clock.stop();
    return mergeImage(lap, bil);
}

cv::Mat Computation::openmp(const cv::Mat &image, Clock &clock) {
    cv::Mat lap = image, bil = image ;
    clock.start();
    Clock shit = Clock();
    shit.start();
#pragma omp parallel num_threads(2)
    {
#pragma omp single nowait
        {
#pragma omp task shared(lap)
            {
                Clock a = Clock();
                a.start();
                lap = laplacian(lap);
                a.logTime("laplacian");
            }
#pragma omp task shared(bil)
            {
                Clock b = Clock();
                b.start();
                bil = bilateralFiltering(bil);
                b.logTime("bilateralFiltering");
            }
#pragma omp taskwait
        }
    }
    shit.logTime("Total");
    clock.stop();
    return mergeImage(lap, bil);
}

cv::Mat Computation::mpi(const cv::Mat &image, Clock &clock) {

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int rows = image.rows, cols = image.cols, ch = image.channels();
    std::vector<int> counts(size), displs(size), rows_per_proc(size);
    int base = rows / size, rem = rows % size, offset = 0;
    for (int i = 0; i < size; ++i) {
        rows_per_proc[i] = base + (i < rem ? 1 : 0);
        counts[i] = rows_per_proc[i] * cols * ch;
        displs[i] = offset * cols * ch;
        offset += rows_per_proc[i];
    }

    std::vector<uchar> img_data, local_data(counts[rank]);
    if (rank == 0) {
        img_data.assign(image.data, image.data + rows * cols * ch);
    }

    MPI_Scatterv(img_data.data(), counts.data(), displs.data(), MPI_BYTE, local_data.data(), counts[rank], MPI_BYTE, 0,
                 MPI_COMM_WORLD);

    cv::Mat local_img(rows_per_proc[rank], cols, image.type(), local_data.data());
    clock.start();
    cv::Mat lap = laplacian(local_img);
    cv::Mat bil = bilateralFiltering(local_img);
    clock.stop();

    std::vector<uchar> lap_buf(lap.total() * ch), bil_buf(bil.total() * ch);
    std::memcpy(lap_buf.data(), lap.data, lap_buf.size());
    std::memcpy(bil_buf.data(), bil.data, bil_buf.size());

    std::vector<uchar> full_lap, full_bil;
    if (rank == 0) {
        full_lap.resize(rows * cols * ch);
        full_bil.resize(rows * cols * ch);
    }

    MPI_Gatherv(lap_buf.data(), lap_buf.size(), MPI_BYTE, full_lap.data(), counts.data(), displs.data(), MPI_BYTE, 0,
                MPI_COMM_WORLD);
    MPI_Gatherv(bil_buf.data(), bil_buf.size(), MPI_BYTE, full_bil.data(), counts.data(), displs.data(), MPI_BYTE, 0,
                MPI_COMM_WORLD);

    if (rank != 0) {
        return {};
    }

    cv::Mat merged_lap(rows, cols, image.type(), full_lap.data());
    cv::Mat merged_bil(rows, cols, image.type(), full_bil.data());
    return mergeImage(merged_lap, merged_bil);
}