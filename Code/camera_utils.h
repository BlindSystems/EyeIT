#ifndef CAMERA_UTILS_H
#define CAMERA_UTILS_H



/******************************************************************************** INTEL CORPORATION PROPRIETARY INFORMATION
 * This software is supplied under the terms of a license agreement or nondisclosure agreement with Intel Corporation and may not be copied or disclosed except in
 * accordance with the terms of that agreement Copyright(c) 2016 Intel Corporation. All Rights Reserved.
 *******************************************************************************/

#pragma once

#include <librealsense/rs.hpp>
#include "or_data_interface.h"
#include "or_configuration_interface.h"
#include "or_video_module_impl.h"
#include <opencv2/core.hpp>
#include <memory>


// Forward declarations
namespace rs {
    namespace core {
    class context_interface;
    class correlated_sample_set;
    }
    class device;
}

class camera_utils
{
public:
    camera_utils();
    ~camera_utils();

  // handling all camera initilzation (projection, camera configuration, MW intilization)
  rs::core::status init_camera(rs::core::image_info& colorInfo, rs::core::image_info& depthInfo,rs::object_recognition::or_video_module_impl& impl,
        rs::object_recognition::or_data_interface** or_data, rs::object_recognition::or_configuration_interface** or_configuration);
  // get rs::core::correlated_sample_set* from the camrea (encapsulates all conversion staff)
  rs::core::correlated_sample_set* get_sample_set(rs::core::image_info& colorInfo,rs::core::image_info& depthInfo);
  void copy_color_to_cvmat(cv::Mat& CVColor);
  //stop the device
  void stop_camera();
  int get_frame_number();
  void setFileIO(const std::string& filename, bool isRecord = false);

//protected:
  std::shared_ptr<rs::core::context_interface> m_ctx;
  rs::device* m_dev;
  rs::core::correlated_sample_set* m_sample_set;
  rs::core::image_info m_colorInfo;
  rs::core::image_info m_depthInfo;
  void* m_color_buffer;
  void* m_depth_buffer;
  int m_frame_number;

  enum CameraMode { LIVE_STREAM, PLAYBACK, RECORD};
  CameraMode m_mode;
  std::string m_filename;
  void release_images();
};

#endif // CAMERA_UTILS_H
