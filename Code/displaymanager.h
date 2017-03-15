#ifndef DISPLAYMANAGER_H
#define DISPLAYMANAGER_H

//opencv
#include "opencv2/imgproc/types_c.h"
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include "opencv2/opencv.hpp"

#include "ObstacleManager.h"

class DisplayManager
{
public:

    DisplayManager();
    void createRects(int colorWidth, int colorHight, int depthWidth, int depthHight);
    cv::Mat DisplayCollisions(cv::Mat mat, int *  col,std::string navigation_msg,  bool isDepth);

    cv::Rect color_right, color_left, color_center, depth_right, depth_left, depth_center;

};

#endif // DISPLAYMANAGER_H
