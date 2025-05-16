#ifndef HELPER_H
#define HELPER_H

#include <string>

enum class Mode {
    Sequence,
    OpenMP
};

void processImagesSequence(const std::string &inputPath, const std::string &outputPath, Mode mode);

void processImagesMPI(const std::string &inputPath, const std::string &outputPath, Mode mode);

#endif // HELPER_H