#ifndef PROCESSINGMANAGER_H
#define PROCESSINGMANAGER_H

//opencv
#include "opencv2/imgproc/types_c.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"


class ProcessingManager
{
public:
    ProcessingManager();
    cv::Mat createVDisparity(cv::Mat image, int depth_width);
    cv::Mat createGroundMap(cv::Mat vDisparity, cv::Mat depthMat);
};

#endif // PROCESSINGMANAGER_H
