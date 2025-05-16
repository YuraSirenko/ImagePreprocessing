#include "helper.h"
#include "computation.h"
#include "io.h"
#include "clock.h"

#include <filesystem>
#include <mpi.h>

void processImagesSequence(const std::string& inputPath,
                           const std::string& outputPath,
                           Mode mode)
{
    Clock clock;

    for (auto& entry : std::filesystem::directory_iterator(inputPath)) {
        if (auto img = loadImage(entry)) {
            cv::Mat result = (mode == Mode::OpenMP)
                             ? Computation::openmp(img.value(), clock)
                             : Computation::sequence(img.value(), clock);
            saveImage(outputPath, entry, result);
        }
    }

    clock.logTime();
}

void processImagesMPI(const std::string& inputPath,
                      const std::string& outputPath,
                      Mode mode)
{
    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::vector<std::filesystem::directory_entry> files;
    for (auto& entry : std::filesystem::directory_iterator(inputPath))
        files.push_back(entry);

    Clock clock;
    Clock q;
    clock.start();

    for (size_t i = 0; i < files.size(); ++i) {
        if (static_cast<int>(i % size) != rank) continue;
        if (auto img = loadImage(files[i])) {
            cv::Mat result = (mode == Mode::OpenMP)
                             ? Computation::openmp(img.value(), q)
                             : Computation::sequence(img.value(), q);
            saveImage(outputPath, files[i], result);
        }
    }
        clock.stop();
        clock.logTime();
}