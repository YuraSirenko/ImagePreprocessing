#ifndef IO_H
#define IO_H
#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

std::optional<cv::Mat> loadImage(const fs::directory_entry &entry);

void saveImages(const fs::path &editedDir,
                const fs::directory_entry &entry,
                const cv::Mat &edited,
                const cv::Mat &original,
                bool smallCompare);

#endif //IO_H
