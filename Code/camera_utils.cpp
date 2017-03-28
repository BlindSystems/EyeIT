/******************************************************************************** INTEL CORPORATION PROPRIETARY INFORMATION
 * This software is supplied under the terms of a license agreement or nondisclosure agreement with Intel Corporation and may not be copied or disclosed except in
 * accordance with the terms of that agreement Copyright(c) 2016 Intel Corporation. All Rights Reserved.
 *******************************************************************************/

#include "camera_utils.h"
#include "rs_sdk.h"
#include <opencv2/imgproc.hpp>
#include <iostream>
camera_utils::camera_utils() : m_mode(LIVE_STREAM)
{
}

camera_utils::~camera_utils()
{
}

rs::core::status camera_utils::init_camera(rs::object_recognition::or_video_module_impl& impl,
             rs::object_recognition::or_data_interface** or_data, rs::object_recognition::or_configuration_interface** or_configuration)
{
    rs::core::status st;
    m_frame_number=0;

    //create context object
    switch(m_mode) {
        case RECORD:
        m_ctx.reset(new rs::record::context(m_filename.c_str()));
        break;

        case PLAYBACK:
        m_ctx.reset(new rs::playback::context(m_filename.c_str()));
        break;

        default:
        case LIVE_STREAM:
        m_ctx.reset(new rs::core::context);
        break;
    }
    if (m_ctx == nullptr)
        return rs::core::status_process_failed;

    int deviceCount = m_ctx->get_device_count();
    printf("There are %d connected RealSense devices.\n", deviceCount );
    if (deviceCount  == 0)
        return rs::core::status_process_failed;

    //get pointer the the camera
    m_dev = m_ctx->get_device(0);


    rs::core::video_module_interface::supported_module_config cfg;
    if (m_mode == PLAYBACK)
    {
        const int num_streams = 2;
        int width[num_streams], height[num_streams], fps[num_streams];
        rs::format format[num_streams];

        //get pointer the the camera
        m_dev = static_cast<rs::playback::context*>(m_ctx.get())->get_playback_device();

        // get streams details
        m_dev->get_stream_mode(rs::stream::color, 0, width[0], height[0], format[0], fps[0]);
        m_dev->get_stream_mode(rs::stream::depth, 0, width[1], height[1], format[1], fps[1]);

        static_cast<rs::playback::device*> (m_dev)->set_real_time(false);

        // check that the configuration is supported
        bool found_config = false;
        int	config_idx = 0;

//        for(int i = 0; i<6; i++)
//        {
//            if(impl.query_supported_module_config(i , cfg) != rs::core::status_no_error)
//                break;
//            std::cout<<"conf: "<<i<<" color : "<<cfg.image_streams_configs[(int)rs::stream::color].size.width<<" "<<cfg.image_streams_configs[(int)rs::stream::color].size.height<<" depth : "<<cfg.image_streams_configs[(int)rs::stream::depth].size.width<<" "<<cfg.image_streams_configs[(int)rs::stream::depth].size.height<< " fps color: "<<cfg.image_streams_configs[(int)rs::stream::color].frame_rate
//                   <<"fps depth "<<cfg.image_streams_configs[(int)rs::stream::depth].frame_rate<<std::endl;
//         }
        while (impl.query_supported_module_config(config_idx , cfg) == rs::core::status_no_error)
        {
        std::cout<<"conf: "<<config_idx<<" color : "<<cfg.image_streams_configs[(int)rs::stream::color].size.width<<" "<<cfg.image_streams_configs[(int)rs::stream::color].size.height<<" depth : "<<cfg.image_streams_configs[(int)rs::stream::depth].size.width<<" "<<cfg.image_streams_configs[(int)rs::stream::depth].size.height<< " fps color: "<<cfg.image_streams_configs[(int)rs::stream::color].frame_rate
               <<"fps depth "<<cfg.image_streams_configs[(int)rs::stream::depth].frame_rate<<std::endl;
        if (width[0] == cfg.image_streams_configs[(int)rs::stream::color].size.width && height[0] == cfg.image_streams_configs[(int)rs::stream::color].size.height
            && width[1] == cfg.image_streams_configs[(int)rs::stream::depth].size.width && height[1] == cfg.image_streams_configs[(int)rs::stream::depth].size.height
            && fps[0] == cfg.image_streams_configs[(int)rs::stream::color].frame_rate
            && fps[1] == cfg.image_streams_configs[(int)rs::stream::depth].frame_rate )
        {
            found_config = true;
            break;
        }
        config_idx++;
        }
        if (found_config == false)
        {
        return rs::core::status_process_failed;
        }
    }
    else
    {
        //get pointer the the camera
        m_dev = m_ctx->get_device(0);


        //request the first (index 0) supported module config.
        st = impl.query_supported_module_config(0, cfg);
        if (st != rs::core::status_no_error)
        return st;

    }

    //enables streams according to the supported configuration
    m_dev->enable_stream(rs::stream::color, cfg.image_streams_configs[(int)rs::stream::color].size.width,
                        cfg.image_streams_configs[(int)rs::stream::color].size.height,
                        rs::format::rgb8,
                        cfg.image_streams_configs[(int)rs::stream::color].frame_rate);

    m_dev->enable_stream(rs::stream::depth, cfg.image_streams_configs[(int)rs::stream::depth].size.width,
                        cfg.image_streams_configs[(int)rs::stream::depth].size.height,
                        rs::format::z16,
                        cfg.image_streams_configs[(int)rs::stream::depth].frame_rate);


    //handling color image info (for later using)
    m_colorInfo.height = cfg.image_streams_configs[(int)rs::stream::color].size.height;
    m_colorInfo.width = cfg.image_streams_configs[(int)rs::stream::color].size.width;
    m_colorInfo.format = rs::core::pixel_format::rgb8;
    m_colorInfo.pitch = m_colorInfo.width * 3;

    //handling depth image info (for later using)
    m_depthInfo.height = cfg.image_streams_configs[(int)rs::stream::depth].size.height;
    m_depthInfo.width = cfg.image_streams_configs[(int)rs::stream::depth].size.width;
    m_depthInfo.format = rs::core::pixel_format::z16;
    m_depthInfo.pitch = m_depthInfo.width * 2;

    m_dev->start();


    // get the extrisics paramters from the camera
    rs::extrinsics ext  = m_dev->get_extrinsics(rs::stream::depth, rs::stream::color);
    rs::core::extrinsics core_ext;

    //get color intrinsics
    rs::intrinsics colorInt = m_dev->get_stream_intrinsics(rs::stream::color);
    rs::core::intrinsics core_colorInt;

    //get depth intrinsics
    rs::intrinsics depthInt = m_dev->get_stream_intrinsics(rs::stream::depth);
    rs::core::intrinsics core_depthInt;

    // after getting all parameters from the camera we need to set the actual_module_config
    rs::core::video_module_interface::actual_module_config actualConfig;

        //1. copy the extrinsics
        memcpy(&actualConfig.image_streams_configs[(int)rs::stream::color].extrinsics, &ext, sizeof(rs::extrinsics));
        core_ext =  rs::utils::convert_extrinsics(ext);

        //2. copy the color intrinsics
        memcpy(&actualConfig.image_streams_configs[(int)rs::stream::color].intrinsics, &colorInt, sizeof(rs::intrinsics));
        core_colorInt = rs::utils::convert_intrinsics (colorInt);

        //3. copy the depth intrinsics
        memcpy(&actualConfig.image_streams_configs[(int)rs::stream::depth].intrinsics, &depthInt, sizeof(rs::intrinsics));
        core_depthInt = rs::utils::convert_intrinsics(depthInt);




    // handling projection
    m_proj = rs::core::projection_interface::create_instance(&core_colorInt, &core_depthInt, &core_ext);
    actualConfig.projection = m_proj;
    //setting the selected configuration (after projection)
    st=impl.set_module_config(actualConfig);
    if (st != rs::core::status_no_error)
        return st;

    //create or data object
    *or_data = impl.create_output();

    //create or data object
    *or_configuration = impl.create_active_configuration();

    m_sample_set = new rs::core::correlated_sample_set();

    m_sample_set->images[(int)rs::stream::color]=nullptr;
    m_sample_set->images[(int)rs::stream::depth]=nullptr;

    return rs::core::status_no_error;
}

rs::core::correlated_sample_set* camera_utils::get_sample_set()
{
    m_dev->wait_for_frames();

    //get color and depth buffers
    const void* colorBuffer =  m_dev->get_frame_data(rs::stream::color);
    const void* depthBuffer = m_dev->get_frame_data(rs::stream::depth);
    m_color_buffer = const_cast<void*>(colorBuffer);
    m_depth_buffer = const_cast<void*>(depthBuffer);//I added

    // release images from the prevoius frame
    release_images();
    //create images from buffers

    rs::core::image_interface::image_data_with_data_releaser color_container(colorBuffer);
    rs::core::image_interface::image_data_with_data_releaser depth_container(depthBuffer);
    auto colorImg = rs::core::image_interface::create_instance_from_raw_data( &m_colorInfo, color_container, rs::core::stream_type::color, rs::core::image_interface::any,m_frame_number, (uint64_t)m_dev->get_frame_timestamp(rs::stream::color));
    auto depthImg = rs::core::image_interface::create_instance_from_raw_data( &m_depthInfo, depth_container, rs::core::stream_type::depth, rs::core::image_interface::any,m_frame_number, (uint64_t)m_dev->get_frame_timestamp(rs::stream::depth));

    //create sample from both images

    m_sample_set->images[(int)rs::stream::color] = colorImg;
    m_sample_set->images[(int)rs::stream::depth] = depthImg;
    m_frame_number++;

    return m_sample_set;

 }

 void camera_utils::stop_camera()
 {
   m_dev->stop();
   release_images();
   delete m_sample_set;
 }
void camera_utils::copy_color_to_cvmat(cv::Mat& CVColor)
{
    CVColor.create(m_colorInfo.height, m_colorInfo.width, CV_8UC3);
    memcpy(CVColor.data,m_color_buffer, CVColor.elemSize() * CVColor.total());
    cv::cvtColor(CVColor,CVColor,CV_RGB2BGR);
}
void camera_utils::copy_depth_to_cvmat(cv::Mat& CVDepth)
{
    CVDepth.create(m_depthInfo.height, m_depthInfo.width, CV_16UC1);
    memcpy(CVDepth.data,m_depth_buffer, CVDepth.elemSize() * CVDepth.total());
}

void camera_utils::setFileIO(const std::string& filename, bool isRecord)
{
    m_filename = filename;
    m_mode = isRecord ? CameraMode::RECORD : CameraMode::PLAYBACK;
}

void camera_utils::release_images()
{
  if (m_sample_set->images[(int)rs::stream::color])
  {
    m_sample_set->images[(int)rs::stream::color]->release();
    m_sample_set->images[(int)rs::stream::color] = nullptr;
  }

  if (m_sample_set->images[(int)rs::stream::depth])
  {
    m_sample_set->images[(int)rs::stream::depth]->release();
    m_sample_set->images[(int)rs::stream::depth] = nullptr;
  }
}

//projection
rs::core::pointF32* camera_utils::projectPoints2ColorImage(rs::core::point3dF32 *depth_points, int num)
{

   rs::core::pointF32* color_points = new rs::core::pointF32[num];
   for (int var = 0; var < num; ++var)
   {
       std::cout << " num:" << num << std::endl;
       std::cout << depth_points[var].x << ", " << depth_points[var].y << "," << depth_points[var].z;
       std::cout << std::endl;
   }
   rs::core::status st = m_proj->map_depth_to_color(num,depth_points,color_points);
   return color_points;

}
