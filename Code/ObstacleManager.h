 #ifndef OBSTACLEMANAGER_H
 #define OBSTACLEMANAGER_H 
 
 #include "opencv2/opencv.hpp"
 #include <bitset>
 
namespace ObstacleUtils
{
  enum Obstacle{CENTER=0b010, RIGHT=0b001,LEFT=0b100, NONE=0b000, LEFT_CENTER=0b110, RIGHT_CENTER=0b011, LEFT_RIGHT=0b101, ALL=0b111};
  const float  percentThresh = 0.3;
  const float percentHoleThresh = 0.7;



    
  class ObstacleDetector
  {
    
    public:

      int row_div = 20;
      int col_div = 30;
      //float thresh_to_block_holes = 0.8;
      float thresh_to_block_square = 0.05;
      float thresh_to_block_col = 0.1;
      float thresh_to_block_dir = 0.2;
      int num_of_layers = 3;

      
      //ObstacleDetector(){}
    bool detectCollision(cv::Mat depth,cv::Rect roi, int startThresh, int endThresh);
    int* directionCol(cv::Mat depth);

    int* get_all_collisions(cv::Mat depthMat);
    cv::Mat get_obstacle_mat(cv::Mat depthMat, int startThresh, int endThresh);
    cv::Mat get_obstacle_array(cv::Mat obstacleMat);
    ushort get_obstacle_dir(cv::Mat obstacle_array, bool firstLayer = false);

      
  };
}
#endif
  
