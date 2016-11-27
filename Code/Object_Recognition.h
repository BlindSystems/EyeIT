  #ifndef OBJECTRECOGNITION_H
  #define OBJECTRECOGNITIO_H 

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
#include "or_video_module_impl.h"
#include "or_data_interface.h"
#include "or_configuration_interface.h"

#include "NavigationUtils.h"

class Object_Recognition
{
public:
  
  Object_Recognition();
  rs::core::status initDevice();
  void startCamera();
  rs::core::status initOR();
  rs::core::status set_rect(int thirdlayer);
  rs::core::status process_sample(rs::core::correlated_sample_set& sample_set);
  std::string get_object_name();

  rs::core::image_info colorInfo,depthInfo;
  rs::object_recognition::or_video_module_impl impl;
  rs::object_recognition::or_data_interface* or_data = nullptr;
  rs::object_recognition::or_configuration_interface* or_configuration = nullptr;
  //rs::core::correlated_sample_set* m_sample_set;
  void* m_color_buffer;
  int m_frame_number;

  rs::object_recognition::recognition_data* recognition_data;
  int array_size;
  
  rs::device * device;
  std::unique_ptr<rs::core::context_interface> ctx;
};

#endif
  