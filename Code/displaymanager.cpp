#include "displaymanager.h"

DisplayManager::DisplayManager()
{

}

cv::Mat DisplayManager::DisplayCollisions(cv::Mat mat, int * col, bool isDepth)
{
    if(isDepth)
    {
        cv::rectangle(mat,depth_left,cv::Scalar(255,0,0),6);//draw left rect
        if((col[0] & ObstacleUtils::Obstacle::LEFT)!=0)
          cv::putText(mat,"BLOCKED!", cv::Point(300,100),2,1.0,cv::Scalar(255,255,255));//draw right rect

        cv::rectangle(mat,depth_right,cv::Scalar(255,0,0),6);
        if((col[0] & ObstacleUtils::Obstacle::RIGHT)!=0)
          cv::putText(mat,"BLOCKED!", cv::Point(1500,100),2,1.0,cv::Scalar(255,255,255));

        cv::rectangle(mat,depth_center,cv::Scalar(255,0,0),6);//draw center rect
        if((col[0] & ObstacleUtils::Obstacle::CENTER)!=0)
          cv::putText(mat,"BLOCKED!", cv::Point( 1000,100),2,1.0,cv::Scalar(255,255,255));

//        cv::rectangle(mat,rec_left_rgb,cv::Scalar(255,0,0),4);
//        cv::rectangle(mat,rec_right_rgb,cv::Scalar(255,0,0),4);
//        cv::rectangle(mat,rec_center_rgb,cv::Scalar(255,0,0),4);
    }
    else
    {
        cv::rectangle(mat,color_left,cv::Scalar(255,0,0),6);//draw left rect
        if((col[0] & ObstacleUtils::Obstacle::LEFT)!=0)
          cv::putText(mat,"BLOCKED!", cv::Point(300,100),2,1.0,cv::Scalar(0,255,255));//draw right rect

        cv::rectangle(mat,color_right,cv::Scalar(255,0,0),6);
        if((col[0] & ObstacleUtils::Obstacle::RIGHT)!=0)
          cv::putText(mat,"BLOCKED!", cv::Point(1500,100),2,1.0,cv::Scalar(0,255,255));

        cv::rectangle(mat,color_center,cv::Scalar(255,0,0),6);//draw center rect
        if((col[0] & ObstacleUtils::Obstacle::CENTER)!=0)
          cv::putText(mat,"BLOCKED!", cv::Point( 1000,100),2,1.0,cv::Scalar(0,255,255));

//        cv::rectangle(mat,rec_left_rgb,cv::Scalar(255,0,0),4);
//        cv::rectangle(mat,rec_right_rgb,cv::Scalar(255,0,0),4);
//        cv::rectangle(mat,rec_center_rgb,cv::Scalar(255,0,0),4);
    }
    return mat;
}

void DisplayManager::createRects(int colorWidth, int colorHight, int depthWidth, int depthHight)
{
    colorWidth = colorWidth/3;
    colorHight = colorHight/4;
    depthWidth = depthWidth/3;
    depthHight = depthHight/4;

    DisplayManager::depth_left = cv::Rect(0,depthHight,depthWidth,depthHight*3);
    DisplayManager::depth_right = cv::Rect(depthWidth*2,depthHight,depthWidth,depthHight*3);
    DisplayManager::depth_center = cv::Rect(depthWidth,depthHight,depthWidth,depthHight*3);

    DisplayManager::color_left = cv::Rect(0,colorHight,colorWidth,colorHight*3);
    DisplayManager::color_right = cv::Rect(colorWidth*2,colorHight,colorWidth,colorHight*3);
    DisplayManager::color_center = cv::Rect(colorWidth,colorHight,colorWidth,colorHight*3);
}

