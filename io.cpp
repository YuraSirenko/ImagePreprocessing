#include "io.h"

namespace fs = std::filesystem;

std::optional<cv::Mat> loadImage(const fs::directory_entry &entry) {
    static const std::vector<std::string> supportedExt = {".jpg", ".jpeg", ".png"};
    const auto ext = entry.path().extension().string();
    if (std::find(supportedExt.begin(), supportedExt.end(), ext) == supportedExt.end())
        return std::nullopt;

    cv::Mat img = cv::imread(entry.path().string(), cv::IMREAD_COLOR);
    if (img.empty()) {
        std::cout << "Failed to load: " << entry.path().filename() << "\n";
        return std::nullopt;
    }

    return img;
}

// Writes the edited image to `editedDir` and, if `smallCompare` is true,
// writes the original (prefixed with "orig_") to `origDir`.
void saveImage(const fs::path &editedDir,
               const fs::directory_entry &entry,
               const cv::Mat &edited,
               const cv::Mat &original,
               bool smallCompare)
{
    const auto fileName = entry.path().filename();
    cv::imwrite((editedDir / fileName).string(), edited);

    if (smallCompare) {
        const auto origName = std::string("orig_") + fileName.string();
        cv::imwrite((editedDir / origName).string(), original);
    }
    std::cout << "Processed: " << entry.path().filename() << "\n";
}

cv::Mat mergeImage(const cv::Mat &sharpened, const cv::Mat &filtered) {
    cv::Mat edited;
    cv::addWeighted(sharpened, 0.5, filtered, 0.5, 0.0, edited);
    return edited ;
}