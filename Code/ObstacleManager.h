  #ifndef OBSTACLEMANAGER_H
  #define OBSTACLEMANAGER_H 

  #include <sys/types.h>
  #include <sys/stat.h>
  #include <string>
  #include <fstream>
  #include <iostream>
  #include <unistd.h>
  #include <thread>

  //====MRAA includes
  #include "mraa.hpp"
  #include <csignal>  //Library from the C/++ standard libraries to allow for clean exits.
  #include <cstdlib>  //
  #include <unistd.h> //
  #include <iostream>
  //====

  #include "opencv2/imgproc/types_c.h"
  #include "opencv2/opencv.hpp"

  #include <librealsense/rs.hpp>
  #include <signal.h>
  #include "rs_sdk.h"
 // #include "or_configuration_interface.h"
 // #include "or_data_interface.h"
 // #include "or_interface.h"
//#include "or_video_module_impl.h"
#include "or_data_interface.h"
#include "or_configuration_interface.h"


class Obstacle_utils
{
  
  public:
    
    Obstacle_utils();
    bool detectCollision(cv::Mat depth,cv::Rect roi, int startThresh, int endThresh);
    int* directionCol(cv::Mat depth);

    
};

#endif
  