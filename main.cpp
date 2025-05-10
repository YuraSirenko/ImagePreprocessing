#include "main.h"

#ifdef SMALL_COMPARE
static constexpr bool smallCompare = true;
#else
static constexpr bool smallCompare = false;
#endif

#include "edge_enhancement_laplacian.h"
#include "bilateral_filtering.h"
#include "io.h"

using namespace std;
namespace fs = std::filesystem;

int main() {
    const std::string inputPath = KAGGLE_TEST + IMAGES;
    const std::string outputPath = PREPROCESSED_TEST + IMAGES_4_COMPARE;

    int processed = 0;
    for (const auto &entry: fs::directory_iterator(inputPath)) {
        if (smallCompare) {
            if (processed == 4) {
                break;
            }
        }

        auto image = loadImage(entry);
        if (!image) continue;

        cv::Mat sharpened = laplacian(image.value(), 3, 0.8, 0.2, 0);
        cv::Mat filtered = bilateralFiltering(image.value());

        cv::Mat edited = mergeImage(sharpened, filtered);

        saveImage(outputPath, entry, edited, image.value(), smallCompare);

        processed++;
    }

    return 0;
}
