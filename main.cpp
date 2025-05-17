#include "main.h"

#include <mpi.h>

#include "clock.h"
#include "computation.h"
#include "helper.h"
#include "io.h"

#include <omp.h>
#include <string>

using namespace std;
namespace fs = std::filesystem;

int main(int argc, char **argv) {
    MPI_Init(&argc, &argv);

    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    if (world_rank == 0) {
        std::cout << "Running on " << world_size << " MPI process(es)\n";
    }

#ifdef _OPENMP
    if (world_rank == 0) {
        std::cout << "OpenMP max threads: " << omp_get_max_threads() << "\n";
    }
#endif

    const std::string inputPath = KAGGLE_HUNDRED + IMAGES;
    const std::string outputPath = PREPROCESSED_HUNDRED + IMAGES;

    bool useMPI = false;
    Mode subMode = Mode::OpenMP;

    if (useMPI) {
        processImagesMPI(inputPath, outputPath, subMode);
    } else {
        processImagesSequence(inputPath, outputPath, subMode);
    }
    MPI_Finalize();
    return 0;
}