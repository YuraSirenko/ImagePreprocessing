#ifndef MAIN_H
#define MAIN_H

#include <iostream>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>

#include <iostream>
#include <filesystem>

inline const std::string PATH_TO_DATASETS = "C:/Coding/semester4/P/rozrah/datasets";

inline const std::string KAGGLE_TEST = PATH_TO_DATASETS + "/kaggle/test";
inline const std::string PREPROCESSED_TEST = PATH_TO_DATASETS + "/preprocessed/test";

inline const std::string KAGGLE_TRAIN = PATH_TO_DATASETS + "/kaggle/train";
inline const std::string PREPROCESSED_TRAIN = PATH_TO_DATASETS + "/preprocessed/train";

inline const std::string KAGGLE_VALID = PATH_TO_DATASETS + "/kaggle/valid";
inline const std::string PREPROCESSED_VALID = PATH_TO_DATASETS + "/preprocessed/valid";

inline const std::string KAGGLE_HUNDRED = PATH_TO_DATASETS + "/kaggle/AHundred";
inline const std::string PREPROCESSED_HUNDRED = PATH_TO_DATASETS + "/preprocessed/AHundred";

inline const std::string IMAGES = "/images";

inline const std::string IMAGES_4 = "/images4";

inline const std::string IMAGES_4_COMPARE = "/images4compare";
inline const std::string IMAGES_40_COMPARE = "/images40compare";


#endif //MAIN_H
