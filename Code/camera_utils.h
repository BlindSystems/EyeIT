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

    enum CameraMode { LIVE_STREAM, PLAYBACK, RECORD};

    camera_utils();
    ~camera_utils();

  // handling all camera initilzation (projection, camera configuration, MW intilization)
  rs::core::status init_camera(rs::object_recognition::or_video_module_impl& impl,
        rs::object_recognition::or_data_interface** or_data, rs::object_recognition::or_configuration_interface** or_configuration);
  // get rs::core::correlated_sample_set* from the camrea (encapsulates all conversion staff)
  rs::core::correlated_sample_set* get_sample_set();
  void copy_color_to_cvmat(cv::Mat& CVColor);
  void copy_depth_to_cvmat(cv::Mat& CVDepth);
  //stop the device
  void stop_camera();
  void setFileIO(const std::string& filename, bool isRecord = false);
  rs::core::pointF32* projectPoints2ColorImage(rs::core::point3dF32 *depth_points, int num = 1);
  rs::device* getDevice(){return m_dev;}
  int getFrameNum(){return m_frame_number;}
  CameraMode getMode(){return m_mode;}
  void setMode(CameraMode mode){m_mode=mode;}
  void setFileName(std::string fileName){m_filename=fileName;}
  rs::core::image_info getColorInfo(){return m_colorInfo;}
  rs::core::image_info getDepthInfo(){return m_depthInfo;}
  void* getColorBuffer(){return m_color_buffer;}
  void* getDepthBuffer(){return m_depth_buffer;}
  void release_images();

private:
  std::shared_ptr<rs::core::context_interface> m_ctx;
  rs::device* m_dev;
  rs::core::correlated_sample_set* m_sample_set;
  rs::core::image_info m_colorInfo;
  rs::core::image_info m_depthInfo;
  void* m_color_buffer;
  void* m_depth_buffer;
  int m_frame_number;

  rs::core::projection_interface* m_proj;
  CameraMode m_mode;

  std::string m_filename;


public:


};

#endif // CAMERA_UTILS_H
