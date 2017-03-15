#include "ObstacleManager.h"
#include <iostream>
#include "opencv2/opencv.hpp"  
  
   


  int* ObstacleUtils::ObstacleDetector::get_all_collisions(cv::Mat depthMat)
  {
      int * all_collisions = new int[3];

      cv::Mat obstacle_mat;
      bool * obstacle_array;
      ushort  col_dir;
      int layer_thickness = 255/(num_of_layers);

      const char MAT_WINDOW_NAME[] = "obstacle mat";
      const char ARRAY_WINDOW_NAME[] = "obstacle array";

      cv::namedWindow(MAT_WINDOW_NAME, CV_WINDOW_NORMAL);
      cv::resizeWindow(MAT_WINDOW_NAME, 480, 270);
      cv::moveWindow(MAT_WINDOW_NAME,1200,500);
      cv::namedWindow(ARRAY_WINDOW_NAME, CV_WINDOW_NORMAL);
      cv::resizeWindow(ARRAY_WINDOW_NAME, 480, 270);
      cv::moveWindow(ARRAY_WINDOW_NAME,1200,800);


      for(int i = 0; i<num_of_layers; i++)
      {

          obstacle_mat = get_obstacle_mat(depthMat, 0,100);
          cv::Mat array = get_obstacle_array(obstacle_mat);

          col_dir = get_obstacle_dir(array, i==0?true:false);

          all_collisions[i] = col_dir;

          if(!i) //show images only for first layer
          {
              cv::imshow(MAT_WINDOW_NAME,obstacle_mat);
              cv::imshow(ARRAY_WINDOW_NAME,array);
          }

      }

      return all_collisions;
  }

  cv::Mat ObstacleUtils::ObstacleDetector::get_obstacle_mat(cv::Mat depthMat, int startThresh, int endThresh)
  {
      cv::Mat thresh = depthMat < endThresh & depthMat >= startThresh & depthMat != 0 /*& depthMat != 1*/;//an obstacle is composed of pixels which their value is in the specific range, not hole (0) and not ground (1)
      //cv::Mat holes = depthMat == 0;
      cv::Mat obstacleMat = cv::Mat::zeros(row_div, col_div, CV_8UC1);

      cv::Rect rect;
      int width = depthMat.cols / col_div, height = depthMat.rows / row_div;;
      rect.width = width;
      rect.height = height;
      int close_pixels_in_rect;
      //int hole_pixels_in_rect;
      int total_pixels_in_rect = width*height;

      for (int i = 0; i < col_div; i++)
      {
          for (int j = row_div / 5; j < row_div; j++)
          {
              rect.x = width*i;
              rect.y = height*j;

              cv::Mat rect_mat(thresh(rect));
              //cv::Mat rect_mat_with_holes(holes(rect));
              close_pixels_in_rect = cv::countNonZero(rect_mat);
              //hole_pixels_in_rect = cv::countNonZero(rect_mat_with_holes);

              if ((float)close_pixels_in_rect / (float)total_pixels_in_rect > thresh_to_block_square /*|| (float)hole_pixels_in_rect / (float)total_pixels_in_rect > thresh_to_block_holes*/)
                  obstacleMat.at<uchar>(j, i) = 255;
          }
      }
      return obstacleMat;
  }
  cv::Mat ObstacleUtils::ObstacleDetector::get_obstacle_array(cv::Mat obstacleMat)
  {
      const int size = obstacleMat.cols;
      cv::Mat obstacleArray = cv::Mat::zeros(1,size,CV_8UC1);//clean from obstacles

      for (int i = 0; i < size; i++)
      {
          int count_blocks = 0;

          for (int j = obstacleMat.rows - 1; j >= 0; j--)
          {
              if (obstacleMat.at<uchar>(j, i) > 0)
                  count_blocks++;
              if ((float)count_blocks/(float)obstacleMat.rows >= thresh_to_block_col)
              {
                  obstacleArray.at<uchar>(0,i) = 255;//blocked col
                  break;
              }
          }


      }
      for (int i = 0; i < size; i++)
          std::cout << obstacleArray.at<uchar>(0,i) << " ";
      std::cout << std::endl;
      return obstacleArray;
  }
ushort ObstacleUtils::ObstacleDetector::get_obstacle_dir(cv::Mat obstacle_array, bool firstLayer)
  {
      ushort blocked_dir = 0;
      ushort left = 0b100;

      const char FILTERED_WINDOW_NAME[] = "filtered array";
      cv::namedWindow(FILTERED_WINDOW_NAME, CV_WINDOW_NORMAL);
      cv::resizeWindow(FILTERED_WINDOW_NAME, 480, 270);
      cv::moveWindow(FILTERED_WINDOW_NAME,650,800);

      const char FINAL_WINDOW_NAME[] = "final array";
      cv::namedWindow(FINAL_WINDOW_NAME, CV_WINDOW_NORMAL);
      cv::resizeWindow(FINAL_WINDOW_NAME, 480, 270);
      cv::moveWindow(FINAL_WINDOW_NAME,100,800);


      int human_width = col_div / 3;
      int offset = 1;
      int k_size = human_width + 2*offset;
      cv::Mat filtered, kernel = (cv::Mat::ones(1,k_size,CV_32F))/255;
      //cv::Mat invarr =  (obstacle_array == 0);
      //invarr = invarr / 255;
      //invarr = cv::Scalar::all(255) - invarr;
      cv::filter2D(obstacle_array,filtered,-1,kernel,cv::Point(-1,-1),0,cv::BORDER_DEFAULT);//summarize every possible human width in the image array
      cv::Mat tot = cv::Mat::ones(1,3,CV_8UC1);
      for (int j = 0 + k_size/2; j < filtered.cols - k_size/2; ++j)
      {
          if(filtered.at<uchar>(0,j) == 0)//choose only the open human width
          {
              int mid = filtered.cols/2;
              if(abs(mid - j) <= offset)//middle part is open
                tot.at<uchar>(0,1) = 0;
              else if(j > mid)//right part is open
                tot.at<uchar>(0,2) = 0;
              else if(j < mid)//left part is open
                tot.at<uchar>(0,0) = 0;
          }
      }

      for (int i = 0; i < tot.cols; i++)
      {

          if(tot.at<uchar>(0,i) != 0)
          {
              ushort shifted = (left >> i);
              blocked_dir |= shifted;
          }
      }
      if(firstLayer)
      {
          cv::imshow(FILTERED_WINDOW_NAME,filtered*25);
          cv::imshow(FINAL_WINDOW_NAME,tot*255);
      }
      std::cout<<"&&&&&&&&&&&&&&&&&&&"<<std::endl;
      std::cout<<"blocking: "<<std::to_string(blocked_dir)<<std::endl;
      std::cout<<"&&&&&&&&&&&&&&&&&&&"<<std::endl;
//      //blocked_dir
//      for (int i = 0; i < 3; i++)
//      {
//          int count_blocked_cols = 0;
//          for (int j = 0; j < cols_in_slice; j++)
//          {
//              if (obstacle_array.at<uchar>(0,i*cols_in_slice + j) == 1)
//                  count_blocked_cols++;
//          }
//          ushort shifted = (left >> i);
//          if ((float)count_blocked_cols / (float)cols_in_slice > thresh_to_block_dir)
//          {
//              blocked_dir |= shifted;
//              std::cout << "i = " << i << "yes!!!" << std::endl;
//          }
//          std::cout << "i: " << i << " shifted left = " << shifted << " blocked_dir: " << blocked_dir << std::endl;
//      }
//      std::cout << "blocked_dir: " << std::bitset<8>(blocked_dir) << std::endl;

      return blocked_dir;
  }






























//=================================================================================================================================================//

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
    cv::Mat fov(depth(roi));
    cv::Mat m = fov == 0.0;
    cv::Mat thresh=fov < endThresh & fov > startThresh & fov!=0.0;
    //cv::Mat thresh=fov<startThresh &fov>endThresh &fov!=0.0;

    int close_pixels =cv::countNonZero(thresh);
    int falseData = cv::countNonZero(m);
    if((float)close_pixels/((float)roi.width*roi.height - falseData)> percentThresh)
    return true;

    if((float)falseData/((float)roi.width*roi.height )> percentHoleThresh )
    return true;
    return false;
}
