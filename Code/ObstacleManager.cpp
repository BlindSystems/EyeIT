#include "ObstacleManager.h"
#include <iostream>
#include "opencv2/opencv.hpp"  
  
   
  int* ObstacleUtils::ObstacleDetector::directionCol(cv::Mat depth)
  {
    int* returnCode=new int[3]{0,0,0};
    
    //int width =depth.cols/4, height=depth.rows/4;
    //cv::Rect left(0,height,width,height*3), right(width*3,height,width,height*3),center(width,height,width*2,height*3);
    
    int width =depth.cols/3, height=depth.rows;
    cv::Rect left(0,0,width,height), right(width*2,0,width,height),center(width,0,width,height);
    
    
    //std::cout<<" depth resolution: width: "<< depth.cols << " height: " << depth.rows << std::endl;
    
    for(int i=0;i<3;i++)
    {
      if(detectCollision(depth,center,i*1000,(i+1)*1000)){
	returnCode[i]|=0b10;
	std::cout<<"collision in center"<<std::endl;
      }
      if(detectCollision(depth,right,i*1000,(i+1)*1000)){
	returnCode[i]|=0b1;
	std::cout<<"collision in right"<<std::endl;
      }
      
      if(detectCollision(depth,left,i*1000,(i+1)*1000)){
	returnCode[i]|=0b100;
      std::cout<<"collision in left"<<std::endl;
	
      }
      std::cout<<returnCode[i]<<std::endl;
    }
      
    return returnCode;
      
  }
  
  bool ObstacleUtils::ObstacleDetector::detectCollision(cv::Mat depth, cv::Rect roi, int startThresh, int endThresh)//,cv::Rect roi,int startThresh, int endThresh)
  {
      /***************************checks if there might be a collision******************************/
      //rect from 0-80 in the height, and 50-220 in the width
      //cv::Rect roi(50,160,220,80);
      //std::cout<<roi.x<<" "<<roi.y<<" "<<roi.width<<" "<<roi.height<<" "<<std::endl;
  //cv::rectangle(depth,roi,cv::Scalar(255,0,0),3);
  //cv::imshow(COLOR_WINDOW_NAME,depth*200);
  //sleep(500);
  //cv::waitKey(0);
      cv::Mat fov(depth(roi));
      cv::Mat m = fov == 0.0;
      cv::Mat thresh=fov<endThresh & fov>startThresh & fov!=0.0;
      //cv::Mat thresh=fov<startThresh &fov>endThresh &fov!=0.0;

      int close_pixels =cv::countNonZero(thresh);
      int falseData = cv::countNonZero(m);
      if((float)close_pixels/((float)roi.width*roi.height - falseData)> percentThresh)
	  return true;

      if((float)falseData/((float)roi.width*roi.height )> percentHoleThresh )
	  return true;
      return false;
  }
  /*bool Obstacle_utils::a()
  {
    return false;
  }*/