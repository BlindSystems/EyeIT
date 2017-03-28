#ifndef PROCESSINGMANAGER_H
#define PROCESSINGMANAGER_H

//opencv
#include "opencv2/imgproc/types_c.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"

#include "rs_sdk.h"

class ProcessingManager
{
public:
    ProcessingManager();
    cv::Mat createVDisparity(cv::Mat image, int depth_width);
    cv::Mat createGroundMap(cv::Mat vDisparity, cv::Mat depthMat,int value=0);
    cv::Mat removeClosePixels(cv::Mat, int thresh = 0, int newVal = 255);
    cv::Mat removeEdges(cv::Mat src);
    rs::core::point3dF32* findConnectedComponents(cv::Mat img, cv::Mat originDepth, cv::Mat &ccm, int* pointsNum);
    cv::Mat erodeImage(cv::Mat src,int k_size = 5,cv::MorphShapes = cv::MORPH_RECT);
    cv::Mat dilateImage(cv::Mat src,int k_size = 5,cv::MorphShapes = cv::MORPH_RECT);
    cv::Mat m_blurImage(cv::Mat src,int k_size = 3,int time=1);
    cv::Mat g_blurImage(cv::Mat src,int k_size = 3,int time=1);
};

#endif // PROCESSINGMANAGER_H
