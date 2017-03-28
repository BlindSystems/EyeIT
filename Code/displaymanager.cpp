#include "displaymanager.h"

DisplayManager::DisplayManager()
{

}

cv::Mat DisplayManager::DisplayCollisions(cv::Mat mat, int * col,std::string navigation_msg, bool isDepth)
{
    int i;//erase
    if(isDepth)
    {
        cv::putText(mat,navigation_msg, cv::Point(depth_center.x+30,30),2,1.0,cv::Scalar(0,255,0),1.5);//write navigation descritption


        cv::rectangle(mat,depth_left,cv::Scalar(255,0,0),6);//draw left rect
        if((col[0] & ObstacleUtils::Obstacle::LEFT)!=0)
          //cv::putText(mat,"BLOCKED!", cv::Point(300,100),2,1.0,cv::Scalar(255,255,255));//draw right rect
          cv::putText(mat,"BLOCKED!", cv::Point(depth_left.x+30,100),2,1.0,cv::Scalar(0,0,255),1.5);

        cv::rectangle(mat,depth_right,cv::Scalar(255,0,0),6);
        if((col[0] & ObstacleUtils::Obstacle::RIGHT)!=0)
          //cv::putText(mat,"BLOCKED!", cv::Point(1500,100),2,1.0,cv::Scalar(255,255,255));
            cv::putText(mat,"BLOCKED!", cv::Point(depth_right.x+30,100),2,1.0,cv::Scalar(0,0,255),1.5);

        cv::rectangle(mat,depth_center,cv::Scalar(255,0,0),6);//draw center rect
        if((col[0] & ObstacleUtils::Obstacle::CENTER)!=0)
          //cv::putText(mat,"BLOCKED!", cv::Point( 1000,100),2,1.0,cv::Scalar(255,255,255));
            cv::putText(mat,"BLOCKED!", cv::Point(depth_center.x+30,100),2,1.0,cv::Scalar(0,0,255),1.5);

    }
    else
    {
        cv::putText(mat,navigation_msg, cv::Point(color_center.x+160,80),2,2.0,cv::Scalar(0,255,0),4);//write navigation descritption


        cv::rectangle(mat,color_left,cv::Scalar(255,0,0),6);//draw left rect
        if((col[0] & ObstacleUtils::Obstacle::LEFT)!=0)
          cv::putText(mat,"BLOCKED!", cv::Point(color_left.x+160,230),2,2.0,cv::Scalar(0,0,255),3);//draw right rect

        cv::rectangle(mat,color_right,cv::Scalar(255,0,0),6);
        if((col[0] & ObstacleUtils::Obstacle::RIGHT)!=0)
          cv::putText(mat,"BLOCKED!", cv::Point(color_right.x+160,230),2,2.0,cv::Scalar(0,0,255),3);

        cv::rectangle(mat,color_center,cv::Scalar(255,0,0),6);//draw center rect
        if((col[0] & ObstacleUtils::Obstacle::CENTER)!=0)
         cv::putText(mat,"BLOCKED!", cv::Point(color_center.x+160,230),2,2.0,cv::Scalar(0,0,255),3);

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

void DisplayManager::drawRects(cv::Mat &color,rs::core::pointF32* color_points, int num)
{
    for(int i = 0; i < num; i+=2)
    {
        cv::rectangle(color,cv::Point(color_points[i].x,color_points[i].y),cv::Point(color_points[i+1].x,color_points[i+1].y),cv::Scalar(0,0,255),2);
        cv::circle(color,cv::Point(color_points[i].x,color_points[i].y),10,cv::Scalar(0,255,0),5);
        cv::circle(color,cv::Point(color_points[i+1].x,color_points[i+1].y),10,cv::Scalar(0,255,0),5);
    }

}

